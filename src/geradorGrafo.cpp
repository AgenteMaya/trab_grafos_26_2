#include "include/geradorGrafo.h"

GeradorGrafo::GeradorGrafo(unsigned seed, double probabilidade) : geradorSorteio(seed), probabilidade(probabilidade)
{}

GeradorGrafo& GeradorGrafo::instanciarGeradorGrafo(unsigned seed, double probabilidade)
{
    if (instance == nullptr)
    {
        instance = std::unique_ptr<GeradorGrafo>(new GeradorGrafo(seed, probabilidade));
    }
    return *instance;
}


std::vector<std::vector<int>> Geradorgrafo::gerarGrafo(int numVertices, int numArestas)
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for(unsigned i = 0; i < numVertices; ++i)
        {
            for(unsigned j = 0; j < numVertices; ++j)
            {
                if(i < j && dist(geradorSorteio) < probabilidade)
                {
                    matriz_adj[i][j] = 1;
                }
                else
                {
                    matriz_adj[i][j] = 0;
                }
            }
        }
}