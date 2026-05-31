#ifndef POINT_H
#define POINT_H

#include <vector>

struct Ponto {
    int id; 
    double x, y, z;
};

// prototipos
double buscarParMaisProximo(std::vector<Ponto>& P, Ponto& sensor1, Ponto& sensor2);
double buscarForcaBruta(const std::vector<Ponto>& P, Ponto& cp1, Ponto& cp2);

#endif
