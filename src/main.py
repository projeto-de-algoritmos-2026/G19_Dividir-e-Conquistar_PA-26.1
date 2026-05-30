import random

try:
    import matplotlib.pyplot as plt
    VISUALIZACAO_DISPONIVEL = True
except ImportError:
    VISUALIZACAO_DISPONIVEL = False

def gerar_sensores_mock(qtd_sensores):
    sensores = []
    for i in range(qtd_sensores):
        x = random.uniform(0, 1000)
        y = random.uniform(0, 500)
        z = random.uniform(0, 200)
        estresse = random.uniform(0, 100)
        
        sensores.append((x, y, z, estresse, f"SENSOR_{i}"))
        
    return sensores

def filtrar_sensores_criticos(sensores, limiar=80):
    return [s for s in sensores if s[3] >= limiar]

def exibir_problema(sensores_criticos):
    print(f"Total de sensores críticos detectados: {len(sensores_criticos)}")
    # print(f"coordenadas mockadas: {sensores_criticos[:2]}") 

    print("-> Chamada pendente: Algoritmo par_mais_proximo_3d.\n")

    if not VISUALIZACAO_DISPONIVEL:
        print("Aviso: plt não disponível.")
        return

    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')

    xs  =  [s[0] for s in sensores_criticos]
    ys = [s[1] for s in sensores_criticos]
    zs = [s[2] for s in sensores_criticos]
    
    ax.scatter(xs, ys, zs, c='r', marker='o', s=20, label='Sensor em Alerta')
    
    ax.set_title("Monitoramento de Integridade Estrutural")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.legend()
    
    plt.show()

if __name__ == "__main__":
    print("=== iniciando sistema ===")
    
    random.seed(15) 
    
    todos_sensores = gerar_sensores_mock(1000)
    
    limiar_critico = 95
    sensores_em_alerta = filtrar_sensores_criticos(todos_sensores, limiar=limiar_critico)
    
    exibir_problema(sensores_em_alerta)
