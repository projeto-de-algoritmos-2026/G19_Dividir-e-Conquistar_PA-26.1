import random
import subprocess
import os
import sys

try:
    import matplotlib.pyplot as plt
    VISUALIZACAO = True
except ImportError:
    VISUALIZACAO = False

def compilar_motor_cpp():
    try:
        resultado = subprocess.run(["make"], capture_output=True, text=True, cwd=os.path.dirname(__file__))
        if resultado.returncode == 0:
            return True
    except FileNotFoundError:
        pass
    
    # caso seja windows, rodar sem precisar do make
    bin_name = "engine.exe" if sys.platform == "win32" else "engine"
    comando = ["g++", "-std=c++17", "-O3", "-ffast-math", "-march=native", "-Wall", "-pthread",
               "-o", bin_name, "main.cpp", "dividir_e_conquistar.cpp"]
    try:
        resultado = subprocess.run(comando, capture_output=True, text=True, cwd=os.path.dirname(__file__))
        return resultado.returncode == 0
    except FileNotFoundError:
        return False

def gerar_sensores_mock(qtd_sensores):
    sensores = []
    
    qtd_cluster = int(qtd_sensores * 0.20)
    qtd_uniforme = qtd_sensores - qtd_cluster
    
    fissura_x, fissura_y, fissura_z = 500.0, 100.0, 50.0
    
    for i in range(qtd_uniforme):
        x = random.uniform(0, 1000) 
        y = random.uniform(0, 200)  
        z = random.uniform(0, 100)
        sensores.append((i, x, y, z))
        
    for i in range(qtd_uniforme, qtd_sensores):
        x = random.gauss(fissura_x, 15.0)
        y = random.gauss(fissura_y, 15.0)
        z = random.gauss(fissura_z, 15.0)
        sensores.append((i, x, y, z))
        
    random.shuffle(sensores)
    return sensores

def formatar_entrada_cpp(sensores):
    linhas = [str(len(sensores))]
    for s in sensores:
        linhas.append(f"{s[0]} {s[1]:.4f} {s[2]:.4f} {s[3]:.4f}")
    return "\n".join(linhas) + "\n"

def invocar_motor_binario(dados_entrada):
    bin_name = "engine.exe" if sys.platform == "win32" else "engine"
    exec_path = os.path.join(os.path.dirname(__file__), bin_name)
    
    if not os.path.exists(exec_path):
        # Fallback de busca no formato Unix se rodar como .exe falhar
        if sys.platform != "win32" and os.path.exists(os.path.join(os.path.dirname(__file__), "engine")):
            exec_path = os.path.join(os.path.dirname(__file__), "engine")
        else:
            return None
    try:
        proc = subprocess.run([exec_path], input=dados_entrada.encode('utf-8'), capture_output=True)
        saida = proc.stdout.decode('utf-8')
        if proc.returncode != 0:
            return None
        return saida
    except Exception:
        return None

def extrair_resultados(saida_texto):
    resultado = {}
    if not saida_texto: return resultado
    
    for linha in saida_texto.strip().split('\n'):
        partes = linha.split()
        if not partes: continue
        
        if linha.startswith("MIN_DIST="):
            resultado["distancia"] = float(linha.split("=")[1])
        elif linha.startswith("TIME_BF_MS="):
            resultado["tempo_bf"] = float(linha.split("=")[1])
        elif linha.startswith("TIME_DC_MS="):
            resultado["tempo_dc"] = float(linha.split("=")[1])
        elif linha.startswith("P1_ID="):
            p1_x = float([p for p in partes if p.startswith("X=")][0].split("=")[1])
            p1_y = float([p for p in partes if p.startswith("Y=")][0].split("=")[1])
            p1_z = float([p for p in partes if p.startswith("Z=")][0].split("=")[1])
            resultado["p1"] = (p1_x, p1_y, p1_z)
        elif linha.startswith("P2_ID="):
            p2_x = float([p for p in partes if p.startswith("X=")][0].split("=")[1])
            p2_y = float([p for p in partes if p.startswith("Y=")][0].split("=")[1])
            p2_z = float([p for p in partes if p.startswith("Z=")][0].split("=")[1])
            resultado["p2"] = (p2_x, p2_y, p2_z)
            
    return resultado

def plotar_resultados_completos(sensores, res, tempos_bf, tempos_dc, ns):
    if not VISUALIZACAO:
        return
        
    fig = plt.figure(figsize=(16, 7))
    
    ax1 = fig.add_subplot(121, projection='3d')
    xs = [s[1] for s in sensores]
    ys = [s[2] for s in sensores]
    zs = [s[3] for s in sensores]
    
    ax1.scatter(xs, zs, ys, c='blue', s=5, alpha=0.3, label='Sensores IoT')
    
    if "p1" in res and "p2" in res:
        p1, p2 = res["p1"], res["p2"]
        ax1.scatter([p1[0], p2[0]], [p1[2], p2[2]], [p1[1], p2[1]], color='red', s=50, label='Par Crítico', zorder=5)
        ax1.plot([p1[0], p2[0]], [p1[2], p2[2]], [p1[1], p2[1]], color='red', linestyle='--', linewidth=2)
        ax1.set_title(f"Barragem 3D (Zonas de Estresse Gaussiano)\nDistância: {res['distancia']:.4f}m")
        
    ax1.set_xlabel("X (m)")
    ax1.set_ylabel("Z (m)")
    ax1.set_zlabel("Y (m)")
    ax1.legend()
    
    ax2 = fig.add_subplot(122)
    ax2.plot(ns, tempos_bf, marker='o', color='red', label='Força Bruta O(n²)', linewidth=2)
    ax2.plot(ns, tempos_dc, marker='s', color='green', label='Dividir e Conquistar O(n log n)', linewidth=2)
    ax2.set_title("Benchmark de Complexidade C++ (O3)")
    ax2.set_xlabel("Número de Sensores (N)")
    ax2.set_ylabel("Tempo de Execução (ms)")
    ax2.grid(True, linestyle='--', alpha=0.7)
    ax2.legend()
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    random.seed(15) 
    
    tamanhos_n = [1000, 5000, 10000, 20000, 50000]
    tempos_bf = []
    tempos_dc = []
    
    ultima_saida_valida = None
    ultimos_sensores = None
    
    if compilar_motor_cpp():
        for n in tamanhos_n:
            print(f"Testando N={n}...")
            sensores_teste = gerar_sensores_mock(n)
            dados_stdin = formatar_entrada_cpp(sensores_teste)
            
            saida_cpp = invocar_motor_binario(dados_stdin)
            if saida_cpp:
                res_parseado = extrair_resultados(saida_cpp)
                tempos_bf.append(res_parseado.get("tempo_bf", 0))
                tempos_dc.append(res_parseado.get("tempo_dc", 0))
                
                ultima_saida_valida = res_parseado
                ultimos_sensores = sensores_teste
        
        if ultima_saida_valida:
            plotar_resultados_completos(ultimos_sensores, ultima_saida_valida, tempos_bf, tempos_dc, tamanhos_n)
