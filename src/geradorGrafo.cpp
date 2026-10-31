#include "include/geradorGrafo.h"

GeradorGrafo::GeradorGrafo(unsigned seed, double probabilidade) : _geradorSorteio(seed), _probabilidade(probabilidade)
{}

GeradorGrafo& GeradorGrafo::instanciarGeradorGrafo(unsigned seed, double probabilidade)
{
    if (instance == nullptr)
    {
        instance = std::unique_ptr<GeradorGrafo>(new GeradorGrafo(seed, probabilidade));
    }
    return *instance;
}


std::vector<std::vector<int>> GeradorGrafo::gerarGrafo(int numVertices)
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<std::vector<int>> matriz_adj(numVertices, std::vector<int>(numVertices, 0));
    for(unsigned i = 0; i < numVertices; ++i)
    {
        for(unsigned j = 0; j < numVertices; ++j)
        {
            if(i < j && dist(_geradorSorteio) < _probabilidade)
            {
                matriz_adj[i][j] = 1;
                matriz_adj[j][i] = 1;
            }                
        }
    }
    return matriz_adj;
}