#include "grafo.h"
#include <numeric>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

#include <iostream>
#include <vector>

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

bool Grafo::temEuleriano()
{
    if (_matriz_adj.empty())
        return true;

    if (std::any_of(_graus.cbegin(), _graus.cend(), [](int i) { return i % 2 != 0; }) || !eConexo(true))
        return false;

    return true; 
}

std::vector<int> Grafo::getCircuitoEuler()
{
    std::vector<int> circuito;
    if (_matriz_adj.empty() || !temEuleriano())
        return circuito;

    auto it = std::max_element(_graus.begin(), _graus.end());
    int indAtual = std::distance(_graus.begin(), it);

    auto matriz = _matriz_adj;
    std::stack<int> pilha;

    pilha.push(indAtual);

    while(1)
    {
        auto proxIt = std::find(matriz[indAtual].begin(), matriz[indAtual].end(), 1);
        if (proxIt == matriz[indAtual].end())
        {
            while(!pilha.empty())
            {
                proxIt = std::find(matriz[pilha.top()].begin(), matriz[pilha.top()].end(), 1);
                if( proxIt == matriz[pilha.top()].end())
                {
                    circuito.push_back(pilha.top());
                    pilha.pop();
                    
                }
                else
                {
                    indAtual = pilha.top();
                    break;
                }
            } 
            if(pilha.empty())
            {
                std::reverse(circuito.begin(), circuito.end());
                return circuito;
            }
        }
        
        int indiceProx = std::distance(matriz[indAtual].begin(), proxIt);

        matriz[indAtual][indiceProx] = 0;
        matriz[indiceProx][indAtual] = 0;

        indAtual = indiceProx;   
        pilha.push(indAtual);

    }
    return circuito;
}

bool Grafo::validaEuleriano()
{
    auto matriz = _matriz_adj;
    auto circuito = getCircuitoEuler();
    int ind1, ind2;

    if (circuito.empty())
        return false;

    for (unsigned i = 0; i + 1 < circuito.size(); i++)
    {
        ind1 = circuito[i];
        ind2 = circuito[i+1];

        if (matriz[ind1][ind2] != 1 )
            return false;
        matriz[ind1][ind2] = -1;
        matriz[ind2][ind1] = -1;
    }

    for(unsigned i = 0; i < matriz.size(); i++)
    {
        for (unsigned j = 0; j < matriz[i].size(); ++j) {
                if(matriz[i][j] != 0 && matriz[i][j] != -1)
                    return false;
        }
    }

    if(circuito[0] != circuito[circuito.size() -1])
    return false;
        
    return true;
}

