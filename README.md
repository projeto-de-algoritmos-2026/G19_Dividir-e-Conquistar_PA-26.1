# SHM_IoT_Monitoramento_Estrutural

Número da Lista: 19  
Conteúdo da Disciplina: Dividir e Conquistar

---

## Alunos

| Matrícula | Aluno |
|-----------|--------|
| 231033737 | Artur Mendonça Arruda |
| 231035464 | Lucas Mendonça Arruda |

---

## Sobre

O projeto consiste no monitoramento em tempo real de infraestruturas críticas, como pontes ou barragens, identificando rapidamente quais são os dois sensores que apresentam zonas de estresse mais próximas geograficamente para prever rupturas mecânicas catastróficas.
Nesse modelo, cada nó tridimensional representa um sensor de telemetria IoT com coordenadas (X, Y, Z) instalados ao longo da estrutura de concreto.
A partir dessa nuvem de dados massiva, o algoritmo de Dividir e Conquistar é aplicado para quebrar a complexidade de tempo de loops aninhados tradicionais de O(n²) para O(n log n), dividindo o espaço tridimensional de forma geométrica através de um plano mediano.
Ao segmentar o espaço em sub-regiões menores e delegar o cálculo de forma assíncrona, o motor consegue filtrar e analisar com alta eficiência a faixa de fronteira (strip), calculando o par crítico de estresse iminente. O sistema também implementa a Força Bruta isolada, que serve como caso base para subproblemas pequenos e como base comparativa empírica para gerar curvas reais de benchmark de desempenho.

## Vídeo

[Link Vídeo]()

## Screenshots

![Visão Macro da Estrutura]()

Ao executar o programa, o orquestrador exibe inicialmente a visualização macro tridimensional da barragem contendo todos os sensores IoT plotados no espaço.

Os pontos azuis representam a telemetria estocástica gerada e as áreas concentradas simulam as fissuras gaussianas de estresse mecânico.

![Visão Micro da Fissura]()

Em seguida, o sistema isola a região em zoom na "Visão Micro".

Nessa etapa, o gráfico foca em um raio delimitado ao redor das coordenadas críticas encontradas pelo algoritmo.

O par de sensores geometricamente mais próximo é destacado em vermelho com uma linha tracejada, evidenciando o ponto exato de estresse eminente.

![Interface de Benchmark]()

A interface final apresenta o gráfico de benchmark de complexidade computacional, contrastando o tempo de execução em milissegundos da Força Bruta O(n²) contra o Dividir e Conquistar O(n log n) para diferentes volumes de dados (N).

## Instalação

Linguagem: Python, C++17  
Biblioteca: Matplotlib 

Pré-requisitos:
- Python 3.x
- Compilador GCC (`g++`) e `make` (Ambiente Unix/WSL recomendado)
- pip

```bash
sudo apt update
sudo apt install g++ make python3-matplotlib -y
```

Caso deseje utilizar um ambiente virtual:

```bash
python3 -m venv venv
source venv/bin/activate
venv\Scripts\activate
pip3 install matplotlib
```

## Uso

Após instalar as dependências, execute o script:

```bash
python3 src/orquestrador.py
```

## Histórico de Versões
| Versão | Descrição | Autor(es) | Data | Revisor(es) |
|--------|-----------|-----------|------|-------------|
| 1.0 | Criação e edição da README | [Artur Mendonça Arruda](https://github.com/ArtyMend07) | 31/05/2026 | - |
| 2.0 | Mudando arquitetura da README | [Lucas Mendonça Arruda](https://github.com/lucasarruda9) | 01/06/2026 | - |