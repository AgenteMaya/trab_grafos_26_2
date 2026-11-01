#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "geradorGrafo.h"

#define SEED 1492

DOCTEST_TEST_CASE("Teste de geração de grafo com probabilidade inválida") {
    CHECK_THROWS_WITH_AS(
        GeradorGrafo(SEED, 1.5),
        "Probabilidade inválida, deve estar entre 0 e 1.",
        std::invalid_argument
    );

    CHECK_THROWS_WITH_AS(
        GeradorGrafo(SEED, -0.5),
        "Probabilidade inválida, deve estar entre 0 e 1.",
        std::invalid_argument
    );    
}

DOCTEST_TEST_CASE("Teste de geração de grafo com probabilidade válida") {
    auto gerador = GeradorGrafo(SEED, 0.5);
    CHECK(gerador.getProbabilidade() == 0.5);        
}


DOCTEST_TEST_CASE("Teste de mudança de probabilidade"){
    auto gerador = GeradorGrafo(SEED, 0.5);
    CHECK(gerador.getProbabilidade() == 0.5);        

    gerador.setProbabilidade(0.8);
    CHECK(gerador.getProbabilidade() == 0.8);

    CHECK_THROWS_WITH_AS(
        gerador.setProbabilidade(1.5),
        "Probabilidade inválida, deve estar entre 0 e 1.",
        std::invalid_argument
    );

    CHECK_THROWS_WITH_AS(
        gerador.setProbabilidade(-0.5),
        "Probabilidade inválida, deve estar entre 0 e 1.",
        std::invalid_argument
    );
}

    
DOCTEST_TEST_CASE("Teste da matriz de adjacência") {
    auto gerador = GeradorGrafo(SEED, 0.5);
    CHECK(gerador.getProbabilidade() == 0.5);        
    auto matriz = gerador.gerarGrafo(5);
    CHECK(matriz.size() == 5);

    for (unsigned i = 0; i < matriz.size(); ++i) {
        CHECK(matriz[i].size() == 5); // Deve ser quadrada
        for (unsigned j = 0; j < matriz[i].size(); ++j) {
            CHECK((matriz[i][j] == 0 || matriz[i][j] == 1));
            if (i == j) {
                CHECK(matriz[i][j] == 0); // Não deve haver laços
            } else {
                CHECK(matriz[i][j] == matriz[j][i]); // Deve ser simétrica
            }
        }
    }
}

DOCTEST_TEST_CASE("Teste de geração de grafo com diferentes probabilidades") {
    auto gerador1 = GeradorGrafo(SEED, 0.1);
    auto matriz1 = gerador1.gerarGrafo(10);

    auto gerador2 = GeradorGrafo(SEED, 0.9);
    auto matriz2 = gerador2.gerarGrafo(10);

    // Com probabilidade maior, esperamos mais arestas
    unsigned count1 = 0;
    unsigned count2 = 0;

    for (unsigned i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < 10; ++j) {
            if (matriz1[i][j] == 1) count1++;
            if (matriz2[i][j] == 1) count2++;
        }
    }

    CHECK(count2 > count1); // Deve haver mais arestas no segundo grafo
}

DOCTEST_TEST_CASE("Teste de geração de grafo com 0 e 1 vértices") {
    auto gerador = GeradorGrafo(SEED, 0.5);

    auto matriz0 = gerador.gerarGrafo(0);
    CHECK(matriz0.empty()); // Deve retornar uma matriz vazia

    auto matriz1 = gerador.gerarGrafo(1);
    CHECK(matriz1.size() == 1);
    CHECK(matriz1[0].size() == 1);
    CHECK(matriz1[0][0] == 0); // Não deve haver laços
}

DOCTEST_TEST_CASE("Teste de geração de grafo com probabilidade e seed iguais") {
    auto gerador1 = GeradorGrafo(SEED, 0.5);
    auto gerador2 = GeradorGrafo(SEED, 0.5);

    auto matriz1 = gerador1.gerarGrafo(5);
    auto matriz2 = gerador2.gerarGrafo(5);

    CHECK(matriz1 == matriz2); // Matrizes devem ser iguais    

    matriz1 = gerador1.gerarGrafo(5);
    matriz2 = gerador2.gerarGrafo(5);

    CHECK(matriz1 == matriz2); // Matrizes devem ser iguais    
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