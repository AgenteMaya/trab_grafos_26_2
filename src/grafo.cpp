#include "grafo.h"
#include <numeric>
#include <queue>
#include <set>
#include <algorithm>

#include <iostream>

void Grafo::setMatrix(std::vector<std::vector<int>>&& matriz) 
{
    _matriz_adj = std::move(matriz);
    graus(); // Atualiza os graus dos vértices após definir a matriz
}

const std::vector<std::vector<int>>& Grafo::getMatrix() const
{
    return _matriz_adj;
}

void Grafo::graus()
{
    _graus.clear();
    for(const auto& linha : _matriz_adj)
    {
        auto result = std::accumulate(linha.begin(), linha.end(), 0);
        _graus.push_back(result);
    }
}

bool Grafo::eEuleriano()
{
    return true; 
}

std::vector<int> Grafo::getGraus() const
{
    return _graus;
}



bool Grafo::eConexo(bool ignorarIsolados)
{
    std::queue<int> visitados;
    std::set<int> conectados;

    if (std::all_of(_graus.begin(), _graus.end(),[](int grau) { return grau == 0; }))
    {
        if (_matriz_adj.size() == 1)
            return true;
        return false;
    }

    auto it = std::max_element(_graus.begin(), _graus.end());
    int indice = std::distance(_graus.begin(), it);

    conectados.insert(indice);
    visitados.push(indice); // Começa a partir do vértice com maior grau

    while(!visitados.empty())
    {
        auto vertice = visitados.front();
        visitados.pop();
        for (unsigned j = 0; j < _matriz_adj[vertice].size(); j++)
        {
            if (_matriz_adj[vertice][j] == 1 && conectados.count(j) == 0)
            {
                visitados.push(j);
                conectados.insert(j);
            }
        }

    }

    unsigned qtd_isolados = 0;

    if(ignorarIsolados)
        qtd_isolados =  std::count(_graus.begin(), _graus.end(), 0);
    
    if (conectados.size() == _matriz_adj.size() - qtd_isolados)
    {
        return true; // Todos os vértices foram visitados
    }
    return false; 
}



