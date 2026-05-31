#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "point.h"

using namespace std;

int main() {
    // otimizacao agressiva de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Ponto> sensores;
    sensores.reserve(n);

    for (int i = 0; i < n; i++) {
        Ponto p;
        cin >> p.id >> p.x >> p.y;
        sensores.push_back(p);
    }

    Ponto s1, s2;

    // medicao de tempo - inicio
    auto t_inicio = chrono::high_resolution_clock::now();

    double dist_minima = buscarParMaisProximo(sensores, s1, s2);

    // medicao de tempo - fim
    auto t_fim = chrono::high_resolution_clock::now();
    double duracao = chrono::duration<double, milli>(t_fim - t_inicio).count();

    // saida formatada esperada pelo orchestrator.py
    cout << fixed << setprecision(4);
    cout << "MIN_DIST=" << dist_minima << "\n";
    cout << "P1_ID=" << s1.id << " X=" << s1.x << " Y=" << s1.y << "\n";
    cout << "P2_ID=" << s2.id << " X=" << s2.x << " Y=" << s2.y << "\n";
    cout << "TIME_MS=" << duracao << "\n";

    return 0;
}
