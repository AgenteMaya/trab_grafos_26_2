#include <random>
#include <vector>
#include <memory>

class GeradorGrafo
{
public:

    static GeradorGrafo& instanciarGeradorGrafo(unsigned seed, double probabilidade);

    std::vector<std::vector<int>> gerarGrafo(int numVertices);

    GeradorGrafo(const GeradorGrafo&) = delete;
    GeradorGrafo& operator=(const GeradorGrafo&) = delete;
    GeradorGrafo(GeradorGrafo&&) = delete;

private:

    GeradorGrafo(unsigned seed, double probabilidade);
    std::mt19937 _geradorSorteio;
    double _probabilidade;
    inline static std::unique_ptr<GeradorGrafo> instance = nullptr;
};