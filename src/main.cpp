#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "point.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Ponto> sensores;
    sensores.reserve(n);

    for (int i = 0; i < n; i++) {
        Ponto p;
        cin >> p.id >> p.x >> p.y >> p.z;
        sensores.push_back(p);
    }

    Ponto s1_bf, s2_bf;
    auto t_inicio_bf = chrono::high_resolution_clock::now();
    double dist_bf = buscarForcaBruta(sensores, s1_bf, s2_bf);
    auto t_fim_bf = chrono::high_resolution_clock::now();
    double duracao_bf = chrono::duration<double, milli>(t_fim_bf - t_inicio_bf).count();

    Ponto s1_dc, s2_dc;
    auto t_inicio_dc = chrono::high_resolution_clock::now();
    double dist_dc = buscarParMaisProximo(sensores, s1_dc, s2_dc);
    auto t_fim_dc = chrono::high_resolution_clock::now();
    double duracao_dc = chrono::duration<double, milli>(t_fim_dc - t_inicio_dc).count();

    cout << fixed << setprecision(4);
    cout << "MIN_DIST=" << dist_dc << "\n";
    cout << "P1_ID=" << s1_dc.id << " X=" << s1_dc.x << " Y=" << s1_dc.y << " Z=" << s1_dc.z << "\n";
    cout << "P2_ID=" << s2_dc.id << " X=" << s2_dc.x << " Y=" << s2_dc.y << " Z=" << s2_dc.z << "\n";
    cout << "TIME_BF_MS=" << duracao_bf << "\n";
    cout << "TIME_DC_MS=" << duracao_dc << "\n";

    return 0;
}
