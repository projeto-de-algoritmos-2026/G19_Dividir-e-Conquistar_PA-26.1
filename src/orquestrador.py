import random
import subprocess
import os

try:
    import matplotlib.pyplot as plt
    VISUALIZACAO = True
except ImportError:
    VISUALIZACAO = False

def compilar_motor_cpp():
    comando = ["g++", "-std=c++17", "-O3", "-ffast-math", "-march=native", "-Wall", 
               "-o", "engine.exe", "main.cpp", "dividir_e_conquistar.c++"]
    
    try:
        resultado = subprocess.run(comando, capture_output=True, text=True, cwd=os.path.dirname(__file__))
        if resultado.returncode != 0:
            print("erro de compilacao:")
            print(resultado.stderr)
            return False
        return True
    except FileNotFoundError:
        print("aviso: g++ nao encontrado no PATH.")
        return False

def gerar_sensores_mock(qtd_sensores):
    sensores  =  []
    for i in range(qtd_sensores):
        x = random.uniform(0, 1000) 
        y = random.uniform(0, 200)  
        sensores.append((i, x, y))
    return sensores

def formatar_entrada_cpp(sensores):
    linhas = [str(len(sensores))]
    for s in sensores:
        linhas.append(f"{s[0]} {s[1]:.4f} {s[2]:.4f}")
    return "\n".join(linhas) + "\n"

def invocar_motor_binario(dados_entrada):
    exec_path = os.path.join(os.path.dirname(__file__), "engine.exe")
    
    if not os.path.exists(exec_path):
        return None
        
    try:
        proc = subprocess.run([exec_path], input=dados_entrada.encode('utf-8'), capture_output=True)
        saida = proc.stdout.decode('utf-8')
        if proc.returncode != 0:
            print(proc.stderr.decode('utf-8'))
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
        elif linha.startswith("TIME_MS="):
            resultado["tempo"] = float(linha.split("=")[1])
        elif linha.startswith("P1_ID="):
            p1_x = float([p for p in partes if p.startswith("X=")][0].split("=")[1])
            p1_y = float([p for p in partes if p.startswith("Y=")][0].split("=")[1])
            resultado["p1"] = (p1_x, p1_y)
        elif linha.startswith("P2_ID="):
            p2_x = float([p for p in partes if p.startswith("X=")][0].split("=")[1])
            p2_y = float([p for p in partes if p.startswith("Y=")][0].split("=")[1])
            resultado["p2"]  = (p2_x, p2_y)
            
    return resultado

def plotar_resultados(sensores, res):
    if not VISUALIZACAO:
        return
        
    xs = [s[1] for s in sensores]
    ys = [s[2] for s in sensores]
    
    plt.figure(figsize=(12, 6))
    plt.scatter(xs, ys, color='blue', s=5, alpha=0.5, label='Sensores IoT')
    
    if "p1" in res and "p2" in res:
        p1, p2 = res["p1"], res["p2"]
        plt.scatter([p1[0], p2[0]], [p1[1], p2[1]], color='red', s=50, label='Par Crítico', zorder=5)
        plt.plot([p1[0], p2[0]], [p1[1], p2[1]], color='red', linestyle='--', linewidth=2)
        
        titulo = f"Distância: {res['distancia']:.4f}m (Tempo de resolucao: {res['tempo']:.2f}ms)"
    else:
        titulo = "Sensores da Estrutura"
        
    plt.title(titulo)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.legend()
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    random.seed(15) 
    # print("carregando mock...")
    
    n_sensores = 10000 
    sensores_teste = gerar_sensores_mock(n_sensores)
    dados_stdin = formatar_entrada_cpp(sensores_teste)
    
    if compilar_motor_cpp():
        saida_cpp = invocar_motor_binario(dados_stdin)
        
        if saida_cpp:
            res_parseado = extrair_resultados(saida_cpp)
            plotar_resultados(sensores_teste, res_parseado)
