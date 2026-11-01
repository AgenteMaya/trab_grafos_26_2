#pragma once

#include <random>
#include <vector>
#include <memory>

class GeradorGrafo
{
public:

    GeradorGrafo(unsigned seed, double probabilidade);

    std::vector<std::vector<int>> gerarGrafo(unsigned numVertices);

    GeradorGrafo(const GeradorGrafo&) = delete;
    GeradorGrafo& operator=(const GeradorGrafo&) = delete;
    GeradorGrafo(GeradorGrafo&&) = delete;

    void setProbabilidade(double probabilidade);

    double getProbabilidade() const;

private:
    std::mt19937 _geradorSorteio;
    double _probabilidade;
};