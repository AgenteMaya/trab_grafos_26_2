#include <std::vector>


class Grafo
{
    // Atributos e métodos do grafo
public:

    void setMatrix(std::vector<std::vector<int>>&& matriz)

    const std::vector<std::vector<int>>& getMatrix() const

    unsigned graus();

    bool temEuleriano();

    Grafo circuitoEuleriano();

    bool eEuleriano();
    

private:
    std::vector<std::vector<int>> matriz_adj; // Lista de adjacência para representar o grafo
}