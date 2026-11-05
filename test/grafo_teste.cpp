#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "grafo.h"

#define SEED 1492

DOCTEST_TEST_CASE("Teste contador de graus") {
    std::vector<std::vector<int>> matriz = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    Grafo grafo(std::move(matriz));

    std::vector<int> graus_esperados = {2, 3, 3, 2};

    CHECK(grafo.getGraus() == graus_esperados);

    std::vector<std::vector<int>> matriz2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    grafo.setMatrix(std::move(matriz2));

    std::vector<int> graus_esperados2 = {1, 2, 1};

    CHECK(grafo.getGraus() == graus_esperados2);

}

DOCTEST_TEST_CASE("Teste de conectividade") {

    Grafo grafo{};
    std::vector<std::vector<int>> matriz_conexa = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    grafo.setMatrix(std::move(matriz_conexa));
    CHECK(grafo.eConexo() == true);

    std::vector<std::vector<int>> matriz_desconexa = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };

    grafo.setMatrix(std::move(matriz_desconexa));
    CHECK(grafo.eConexo() == false);

    std::vector<std::vector<int>> matriz3 = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };

    grafo.setMatrix(std::move(matriz3));
    CHECK(grafo.eConexo() == false);
    CHECK(grafo.eConexo(true) == true);

    std::vector<std::vector<int>> matriz_vazia = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    grafo.setMatrix(std::move(matriz_vazia));
    CHECK(grafo.eConexo() == false);

    std::vector<std::vector<int>> matriz_dim_zero = {};
    grafo.setMatrix(std::move(matriz_dim_zero));
    CHECK(grafo.eConexo() == false);
}       

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("success", true);      // mostra testes que passaram
    context.setOption("reporters", "console"); // saída padrão
    // context.setOption("no-breaks", true); // não para no primeiro erro

    context.applyCommandLine(argc, argv);    // aceita também flags via terminal
    int res = context.run();                 // roda os testes

    return res;
}