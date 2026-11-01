#include "geradorGrafo.h"

#include <stdexcept>

void validaProbabilidade(double probabilidade)
{
    if (probabilidade < 0.0 || probabilidade > 1.0)
    {
        throw std::invalid_argument("Probabilidade inválida, deve estar entre 0 e 1.");
    }
}

GeradorGrafo::GeradorGrafo(unsigned seed, double probabilidade) : _geradorSorteio(seed)
{
    validaProbabilidade(probabilidade);
    _probabilidade = probabilidade;
}

std::vector<std::vector<int>> GeradorGrafo::gerarGrafo(unsigned numVertices)
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

void GeradorGrafo::setProbabilidade(double probabilidade)
{
    validaProbabilidade(probabilidade);
    _probabilidade = probabilidade;
}

double GeradorGrafo::getProbabilidade() const
{
    return _probabilidade;
}