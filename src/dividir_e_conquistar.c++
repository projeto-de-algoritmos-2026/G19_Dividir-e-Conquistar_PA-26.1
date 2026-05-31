#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

// Estrutura que representa a localização geográfica de um sensor IoT
struct Ponto {
    int id; 
    double x, y;
};

bool compararX(const Ponto& a, const Ponto& b) {
    return a.x < b.x;
}

bool compararY(const Ponto& a, const Ponto& b) {
    return a.y < b.y;
}

double calcularDistancia(const Ponto& p1, const Ponto& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
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