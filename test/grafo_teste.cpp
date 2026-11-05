#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "grafo.h"

#define SEED 1492

DOCTEST_TEST_CASE("Teste contador de graus") 
{
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

DOCTEST_TEST_CASE("Teste de conectividade") 
{
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

DOCTEST_TEST_CASE("Teste de circuito euleriano")
{
    Grafo grafo{};
    std::vector<std::vector<int>> matriz_dim_zero = {};
    grafo.setMatrix(std::move(matriz_dim_zero));
    CHECK(grafo.temEuleriano() == true);

    std::vector<std::vector<int>> matriz_vazia = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_vazia));
    CHECK(grafo.temEuleriano() == false);

    std::vector<std::vector<int>> matriz_com_impar = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_com_impar));
    CHECK(grafo.temEuleriano() == false);

    std::vector<std::vector<int>> matriz_c4 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_c4));
    CHECK(grafo.temEuleriano() == true);

    std::vector<std::vector<int>> matriz_p4 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_p4));
    CHECK(grafo.temEuleriano() == false);

    std::vector<std::vector<int>> matriz_desconexa = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_desconexa));
    CHECK(grafo.temEuleriano() == false);

    std::vector<std::vector<int>> matriz_isolado = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_isolado));
    CHECK(grafo.temEuleriano() == true);

}

DOCTEST_TEST_CASE("Teste de construcao do circuito Euleriano")
{
    Grafo grafo{};

    std::vector<std::vector<int>> matriz_dim_zero = {};
    grafo.setMatrix(std::move(matriz_dim_zero));
    CHECK(grafo.getCircuitoEuler().empty());

    std::vector<std::vector<int>> matriz_vazia = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_vazia));
    CHECK(grafo.getCircuitoEuler().empty());

    std::vector<std::vector<int>> matriz_p4 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_p4));
    CHECK(grafo.getCircuitoEuler().empty());

    std::vector<std::vector<int>> matriz_c4 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_c4));

    std::vector<int> circuito_c4 = grafo.getCircuitoEuler();
    CHECK(circuito_c4 == std::vector<int>{0, 1, 2, 3, 0});

    std::vector<std::vector<int>> matriz_desconexa = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_desconexa));
    CHECK(grafo.getCircuitoEuler().empty());

    std::vector<std::vector<int>> matriz_isolado = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_isolado));

    std::vector<int> circuito_isolado = grafo.getCircuitoEuler();

    REQUIRE(circuito_isolado.size() == 4);
    CHECK(circuito_isolado.front() == circuito_isolado.back());
    CHECK(std::find(circuito_isolado.begin(), circuito_isolado.end(), 3)
          == circuito_isolado.end());

    std::vector<std::vector<int>> matriz_dois_ciclos = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_dois_ciclos));

    std::vector<int> circuito_dois_ciclos = grafo.getCircuitoEuler();

    REQUIRE(circuito_dois_ciclos.size() == 7);
    CHECK(circuito_dois_ciclos.front() == circuito_dois_ciclos.back());
}

DOCTEST_TEST_CASE("Teste de validacao do circuito Euleriano")
{
    Grafo grafo{};

    // Matriz de dimensão zero
    std::vector<std::vector<int>> matriz_dim_zero = {};
    grafo.setMatrix(std::move(matriz_dim_zero));
    CHECK(grafo.validaEuleriano() == false);

    // Grafo sem arestas
    std::vector<std::vector<int>> matriz_vazia = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_vazia));
    CHECK(grafo.validaEuleriano() == false);

    // Grafo com graus ímpares
    std::vector<std::vector<int>> matriz_com_impar = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_com_impar));
    CHECK(grafo.validaEuleriano() == false);

    // Ciclo C4
    std::vector<std::vector<int>> matriz_c4 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_c4));
    CHECK(grafo.validaEuleriano() == true);

    // Caminho P4
    std::vector<std::vector<int>> matriz_p4 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_p4));
    CHECK(grafo.validaEuleriano() == false);

    // Duas componentes cíclicas desconexas
    std::vector<std::vector<int>> matriz_desconexa = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_desconexa));
    CHECK(grafo.validaEuleriano() == false);

    // Ciclo com vértice isolado
    std::vector<std::vector<int>> matriz_isolado = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    grafo.setMatrix(std::move(matriz_isolado));
    CHECK(grafo.validaEuleriano() == true);

    // Dois ciclos compartilhando um vértice
    std::vector<std::vector<int>> matriz_dois_ciclos = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    grafo.setMatrix(std::move(matriz_dois_ciclos));
    CHECK(grafo.validaEuleriano() == true);
}

int main(int argc, char** argv) 
{
    doctest::Context context;
    context.setOption("success", true);      // mostra testes que passaram
    context.setOption("reporters", "console"); // saída padrão
    // context.setOption("no-breaks", true); // não para no primeiro erro

    context.applyCommandLine(argc, argv);    // aceita também flags via terminal
    int res = context.run();                 // roda os testes

    return res;
}