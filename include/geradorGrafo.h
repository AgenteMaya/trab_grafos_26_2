#include <random>

class GeradorGrafo
{
public:

    GeradorGrafo& instanciarGeradorGrafo(unsigned seed, double probabilidade);

    std::vector<std::vector<int>> gerarGrafo();

    GeradorGrafo(const GeradorGrafo&) = delete;
    GeradorGrafo& operator=(const GeradorGrafo&) = delete;
    GeradorGrafo(GeradorGrafo&&) = delete;

private:

    GeradorGrafo(unsigned seed, double probabilidade);
    std::mt19937 geradorSorteio;
    double probabilidade;
    inline static std::unique_ptr<GeradorGrafo> instance = nullptr;
};