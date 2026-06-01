#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

#include "point.h"

double calcularDistancia(const Ponto& p1, const Ponto& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                     (p1.y - p2.y) * (p1.y - p2.y) + 
                     (p1.z - p2.z) * (p1.z - p2.z));
}

void merge(std::vector<Ponto>& P, int inicio, int meio, int fim, char eixo) {
    std::vector<Ponto> temp(fim - inicio + 1);
    int i = inicio, j = meio + 1, k = 0;

    while (i <= meio && j <= fim) {
        bool menorOuIgual = (eixo == 'x') ? (P[i].x <= P[j].x) : (P[i].y <= P[j].y);
        
        if (menorOuIgual) temp[k++] = P[i++];
        else temp[k++] = P[j++];
    }
    while (i <= meio) temp[k++] = P[i++];
    while (j <= fim) temp[k++] = P[j++];

    for (i = inicio, k = 0; i <= fim; ++i, ++k) {
        P[i] = temp[k];
    }
}

void mergeSort(std::vector<Ponto>& P, int inicio, int fim, char eixo) {
    if (inicio >= fim) return;
    
    int meio = inicio + (fim - inicio) / 2;
    mergeSort(P, inicio, meio, eixo);
    mergeSort(P, meio + 1, fim, eixo);
    merge(P, inicio, meio, fim, eixo);
}

// força bruta local para pequenos subconjuntos (n <= 3)
double forcaBrutaLocal(std::vector<Ponto>& P, int inicio, int fim, Ponto& cp1, Ponto& cp2) {
    double min_dist = DBL_MAX;
    for (int i = inicio; i < fim; ++i) {
        for (int j = i + 1; j <= fim; ++j) {
            double d = calcularDistancia(P[i], P[j]);
            if (d < min_dist) {
                min_dist = d;
                cp1 = P[i];
                cp2 = P[j];
            }
        }
    }
    mergeSort(P, inicio, fim, 'y');
    return min_dist;
}

double buscarForcaBruta(const std::vector<Ponto>& P, Ponto& cp1, Ponto& cp2) {
    if (P.empty()) return DBL_MAX;
    std::vector<Ponto> copia_P = P;
    return forcaBrutaLocal(copia_P, 0, copia_P.size() - 1, cp1, cp2);
}

double executarDivisaoEConquista(std::vector<Ponto>& P, int inicio, int fim, Ponto& cp1, Ponto& cp2) {
    if (fim - inicio <= 3) {
        return forcaBrutaLocal(P, inicio, fim, cp1, cp2);
    }

    int meio = inicio + (fim - inicio) / 2;
    Ponto pontoMedio = P[meio]; 
    Ponto cp1_esq, cp2_esq, cp1_dir, cp2_dir;
    double res_esq = executarDivisaoEConquista(P, inicio, meio, cp1_esq, cp2_esq);
    double res_dir = executarDivisaoEConquista(P, meio + 1, fim, cp1_dir, cp2_dir);
    double min_atual;

    if (res_esq < res_dir) {
        min_atual = res_esq;
        cp1 = cp1_esq;
        cp2 = cp2_esq;
    } else {
        min_atual = res_dir;
        cp1 = cp1_dir;
        cp2 = cp2_dir;
    }

    merge(P, inicio, meio, fim, 'y');

    // strip que delimita X
    std::vector<Ponto> faixa;
    faixa.reserve(fim - inicio + 1); 
    for (int i = inicio; i <= fim; i++) {
        if (std::abs(P[i].x - pontoMedio.x) < min_atual) {
            faixa.push_back(P[i]);
        }
    }

    // strip que delimita Y e Z
    for (size_t i = 0; i < faixa.size(); ++i) {
        for (size_t j = i + 1; j < faixa.size() && (faixa[j].y - faixa[i].y) < min_atual; ++j) {
            if (std::abs(faixa[i].z - faixa[j].z) >= min_atual) continue;

            double d = calcularDistancia(faixa[i], faixa[j]);
            if (d < min_atual) {
                min_atual = d;
                cp1 = faixa[i]; 
                cp2 = faixa[j]; 
            }
        }
    }

    return min_atual;
}

double buscarParMaisProximo(std::vector<Ponto>& P, Ponto& sensor1, Ponto& sensor2) {
    if (P.size() < 2) return DBL_MAX;

    mergeSort(P, 0, P.size() - 1, 'x');
    return executarDivisaoEConquista(P, 0, P.size() - 1, sensor1, sensor2);
}