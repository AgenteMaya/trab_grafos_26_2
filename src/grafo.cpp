#include "grafo.h"

void Grafo::setMatrix(std::vector<std::vector<int>>&& matriz)
{
    _matriz_adj = matriz;
}

const std::vector<std::vector<int>>& Grafo::getMatrix() const
{
    return _matriz_adj;
}

unsigned Grafo::graus()
{
    return 0;
}

bool Grafo::eEuleriano()
{
    return true; 
}

