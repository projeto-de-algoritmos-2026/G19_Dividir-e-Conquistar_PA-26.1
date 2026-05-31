#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <future>

using namespace std;

#include "point.h"

const int LIMIAR_THREAD = 5000;

bool compararX(const Ponto& a, const Ponto& b) {
    return a.x < b.x;
}

bool compararY(const Ponto& a, const Ponto& b) {
    return a.y < b.y;
}

double calcularDistancia(const Ponto& p1, const Ponto& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y) + 
                (p1.z - p2.z) * (p1.z - p2.z));
}

// força bruta local para pequenos subconjuntos de sensores (n <= 3)
double forcaBrutaLocal(const vector<Ponto>& P, int inicio, int fim, Ponto& cp1, Ponto& cp2) {
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
    return min_dist;
}

// exporta forca bruta para a main fazer benchmark
double buscarForcaBruta(const vector<Ponto>& P, Ponto& cp1, Ponto& cp2) {
    return forcaBrutaLocal(P, 0, P.size(), cp1, cp2);
}

// varredura linear na faixa de fronteira entre as duas sub-regiões
double processarFaixaFronteira(vector<Ponto>& faixa, double d_min, Ponto& cp1, Ponto& cp2) {
    double min_dist = d_min;

    // Ordena os sensores da faixa verticalmente pelo eixo Y 
    sort(faixa.begin(), faixa.end(), compararY);

    // loop limitado a no máximo 7 comparações por elemento 
    for (size_t i = 0; i < faixa.size(); ++i) {
        for (size_t j = i + 1; j < faixa.size() && (faixa[j].y - faixa[i].y) < min_dist; ++j) {
            double d = calcularDistancia(faixa[i], faixa[j]);
            if (d < min_dist) {
                min_dist = d;
                cp1 = faixa[i];
                cp2 = faixa[j];
            }
        }
    }
    return min_dist;
}

// execucao recursiva do algoritmo principal
double executarDivisaoEConquista(const vector<Ponto>& Px, int inicio, int fim, Ponto& cp1, Ponto& cp2) {
    if (fim - inicio <= 3) {
        return forcaBrutaLocal(Px, inicio, fim, cp1, cp2);
    }

    int meio = inicio + (fim - inicio) / 2;
    Ponto pontoMedio = Px[meio];

    Ponto cp1_esq, cp2_esq, cp1_dir, cp2_dir;

    double dl, dr;
    if (fim - inicio > LIMIAR_THREAD) {
        auto future_esq = async(launch::async, executarDivisaoEConquista, ref(Px), inicio, meio, ref(cp1_esq), ref(cp2_esq));
        dr = executarDivisaoEConquista(Px, meio + 1, fim, cp1_dir, cp2_dir);
        dl = future_esq.get();
    } else {
        dl = executarDivisaoEConquista(Px, inicio, meio, cp1_esq, cp2_esq);
        dr = executarDivisaoEConquista(Px, meio + 1, fim, cp1_dir, cp2_dir);
    }

    double d;
    if (dl < dr) {
        d = dl;
        cp1 = cp1_esq;
        cp2 = cp2_esq;
    } else {
        d = dr;
        cp1 = cp1_dir;
        cp2 = cp2_dir;
    }

    // varredura da interseccao central
    vector<Ponto> faixa;
    faixa.reserve(fim - inicio + 1); 
    for (int i = inicio; i <= fim; i++) {
        if (abs(Px[i].x - pontoMedio.x) < d) {
            faixa.push_back(Px[i]);
        }
    }

    return min(d, processarFaixaFronteira(faixa, d, cp1, cp2));
}

// ponto de entrada
double buscarParMaisProximo(vector<Ponto>& P, Ponto& sensor1, Ponto& sensor2) {
    sort(P.begin(), P.end(), compararX);
    return executarDivisaoEConquista(P, 0, P.size() - 1, sensor1, sensor2);
}