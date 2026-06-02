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

O projeto faz o monitoramento em tempo real de estruturas como pontes e barragens usando o algoritmo do **Par de Pontos Mais Próximos**. A ideia é rodar essa análise geométrica para flagrar o ponto exato de maior estresse físico e prever rupturas na estrutura antes que aconteça um desastre.

### Mapeamento dos Sensores no plano 3D
O sistema recebe dados onde cada sensor IoT instalado no concreto vira um ponto com coordenadas (X, Y, Z). O objetivo do algoritmo é varrer esses pontos e encontrar quais são os dois sensores que estão mais próximos um do outro, já que a aproximação deles indica uma deformação ou compressão crítica na estrutura.

### Divisão Espacial e Ganho de Desempenho
Fazer essa busca comparando cada sensor com todos os outros (Força Bruta) gera um custo de $O(n²)$, o que trava o sistema se tivermos milhares de sensores rodando ao mesmo tempo.  Para resolver isso, foi aplicado um algoritmo de **Dividir e Conquistar** para derrubar o tempo de execução para $O(n \log n)$.


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