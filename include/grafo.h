#pragma once
#include <vector>
#include <utility>

class Grafo
{
    // Atributos e métodos do grafo
public:

    Grafo(std::vector<std::vector<int>>&& matriz) : _matriz_adj(std::move(matriz))
    {
        graus(); // Calcula os graus dos vértices ao inicializar o grafo
    }

    Grafo() = default;

    void setMatrix(std::vector<std::vector<int>>&& matriz);

    const std::vector<std::vector<int>>& getMatrix() const;

    bool temEuleriano();

    Grafo circuitoEuleriano();

    std::vector<int> getGraus() const;

    bool eConexo(bool ignorarIsolados = false);

    std::vector<int> getCircuitoEuler();

    bool validaEuleriano();

private:

    void graus();

    std::vector<std::vector<int>> _matriz_adj; // Matriz de adjacência para representar o grafo

    std::vector<int> _graus; //Vetor de graus dos vértices do grafo
};