#ifndef POINT_H
#define POINT_H

#include <vector>

struct Ponto {
    int id; 
    double x, y;
};

// prototipos
double buscarParMaisProximo(std::vector<Ponto>& P, Ponto& sensor1, Ponto& sensor2);

#endif
