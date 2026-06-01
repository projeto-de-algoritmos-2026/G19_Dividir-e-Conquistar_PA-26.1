# SHM IoT - Monitoramento Estrutural com Dividir e Conquistar

O objetivo desse projeto é simular o monitoramento em tempo real de infraestruturas críticas, como pontes ou barragens, identificando rapidamente quais são os dois sensores que apresentam zonas de estresse mais próximas geograficamente para prever rupturas. 

A ideia central é resolver o problema do par de sensores mais próximo usando o algoritmo de Dividir e Conquistar, provando na prática o ganho de desempenho em relação a uma Força Bruta simples.

## Arquitetura

O sistema foi montado dividindo as responsabilidades entre um gerador de dados dinâmico e um motor de cálculo de alta performance.

1. Camada de Orquestração
Escrita em Python 3. É responsável por simular as nuvens de dados dos sensores, além de chamar a execução do backend C++, coletar as métricas de tempo e gerar os gráficos 3D da estrutura e a curva de complexidade no final.

2. Motor C++
Aqui é onde o cálculo pesado acontece de verdade. O núcleo foi feito em C++17 puro, sem depender de pacotes externos, para garantirmos a implementação manual do conceito matemático. O motor usa entrada e saída de dados otimizada e tira proveito de chamadas assíncronas para dividir a carga de cálculo em threads no processador.

## O Algoritmo

Para conseguir rodar dezenas de milhares de coordenadas 3D em frações de segundo, o executável roda o Dividir e Conquistar entregando a complexidade O(n log n). 

A Força Bruta O(n²) também está lá, mas ela foi isolada e serve apenas como caso base para recursões pequenas e para rodar o benchmark comparativo. Isso permite provar empiricamente que a abordagem matemática superior escala infinitamente melhor que os loops aninhados.

Na prática, a engine corta os pontos no meio, joga metades grandes em threads separadas, calcula os pares de cada lado, e por fim resolve a área de intersecção no meio, devolvendo os dados pro orquestrador plotar o resultado.

---

## Como Executar

O projeto foi projetado para rodar primariamente em ambientes Unix/Linux devido à utilização nativa da biblioteca de multi-threading (`-pthread`). 

**Pré-requisitos Críticos:**
A compilação do motor C++ exige que o pacote `g++` (GCC) e o `make` estejam disponíveis no seu sistema, juntamente com a dependência visual no Python. Se você estiver usando Windows, é **altamente recomendável** rodar o projeto através do **WSL** (Windows Subsystem for Linux) para evitar problemas de portabilidade com o compilador.

### Passo a Passo no Linux / WSL (Recomendado)

1. Abra o terminal na raiz do projeto e instale o compilador e a dependência do Python:
```bash
sudo apt update
sudo apt install g++ make python3-matplotlib -y
```

2. Execute o orquestrador. Ele se encarregará de compilar o binário silenciosamente e invocar o benchmark:
```bash
python3 src/orquestrador.py
```

### Passo a Passo no Windows (Nativo)

Se não for possível utilizar o WSL, você deverá configurar o ambiente Windows manualmente:
1. Instale o [MinGW-w64](https://www.mingw-w64.org/) e certifique-se de adicionar a pasta `bin` nas Variáveis de Ambiente (`PATH`) do Windows para que o comando `g++` seja reconhecido.
2. Instale o pacote gráfico via pip:
```cmd
pip install matplotlib
```
3. Execute o script via PowerShell ou CMD:
```cmd
python src/orquestrador.py
```

---

## Histórico de Versões
| Versão | Descrição | Autor(es) | Data | Revisor(es) |
|--------|-----------|-----------|------|-------------|
| 1.0 | Criação e edição da README | [Artur Mendonça Arruda](https://github.com/ArtyMend07) | 31/05/2026 | - |