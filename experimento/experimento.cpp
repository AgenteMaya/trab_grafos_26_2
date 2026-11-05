#include "grafo.h"
#include "geradorGrafo.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>

#define SEED 1492
#define PROBABILIDADE 0.30
#define NUM_VERTICES 10
#define NUM_GRAFOS 1000


void experimento2()
{
    std::cout << "\n========== EXPERIMENTO 2 ==========\n\n";

    GeradorGrafo gerador(SEED, PROBABILIDADE);
    Grafo grafo;

    unsigned qtdEulerianos = 0;

    // Iniciar cronometro
    auto inicio = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < NUM_GRAFOS; ++i)
    {
        grafo.setMatrix(gerador.gerarGrafo(NUM_VERTICES));

        if (grafo.temEuleriano())
            ++qtdEulerianos;
    }

    // Encerrar cronometro
    auto fim = std::chrono::steady_clock::now();

    // Calcular o tempo total em segundos
    std::chrono::duration<double> tempoTotal = fim - inicio;

    // Calcular a proporcao de grafos Eulerianos
    double proporcao =
        static_cast<double>(qtdEulerianos) / NUM_GRAFOS;

    std::cout << "Numero de vertices: " << NUM_VERTICES << '\n';
    std::cout << "Probabilidade: " << PROBABILIDADE << '\n';
    std::cout << "Seed: " << SEED << "\n\n";

    std::cout << "Total de grafos gerados: "
              << NUM_GRAFOS << '\n';

    std::cout << "Quantidade de grafos Eulerianos: "
              << qtdEulerianos << '\n';

    std::cout << "Quantidade de grafos nao Eulerianos: "
              << NUM_GRAFOS - qtdEulerianos << '\n';

    std::cout << std::fixed << std::setprecision(4);

    std::cout << "Proporcao de grafos Eulerianos: "
              << proporcao << '\n';

    std::cout << "Percentual de grafos Eulerianos: "
              << proporcao * 100.0 << "%\n";

    std::cout << "Tempo total de execucao: "
              << tempoTotal.count() << " segundos\n";

    std::cout << "\n========== FIM DO EXPERIMENTO 2 ==========\n";
}

void experimento1()
{
    std::cout << "========== EXPERIMENTO 1 ==========\n\n";

    Grafo grafo;
    GeradorGrafo gerador(SEED, PROBABILIDADE);
    unsigned long long qtdIteracoes{0};

    std::cout << "Numero de vertices: " << NUM_VERTICES << '\n';
    std::cout << "Probabilidade: " << PROBABILIDADE << '\n';
    std::cout << "Seed: " << SEED << "\n\n";

    // Gerar grafos ate encontrar um Euleriano
    do
    {
        grafo.setMatrix(gerador.gerarGrafo(NUM_VERTICES));
        ++qtdIteracoes;

    } while (!grafo.temEuleriano());

    std::cout << "========== GRAFO ENCONTRADO ==========\n\n";

    const auto& matriz = grafo.getMatrix();
    auto graus = grafo.getGraus();

    // 1. Apresentar a matriz de adjacencia
    std::cout << "1. MATRIZ DE ADJACENCIA\n\n";

    std::cout << "    ";
    for (unsigned j = 0; j < matriz.size(); ++j)
        std::cout << std::setw(3) << j;

    std::cout << '\n';

    for (unsigned i = 0; i < matriz.size(); ++i)
    {
        std::cout << std::setw(3) << i << " ";

        for (unsigned j = 0; j < matriz[i].size(); ++j)
            std::cout << std::setw(3) << matriz[i][j];

        std::cout << '\n';
    }

    // 1. Apresentar as arestas
    std::cout << "\n2. ARESTAS DO GRAFO\n\n";

    unsigned qtdArestas = 0;

    for (unsigned i = 0; i < matriz.size(); ++i)
    {
        for (unsigned j = i + 1; j < matriz[i].size(); ++j)
        {
            if (matriz[i][j] == 1)
            {
                std::cout << "(" << i << ", " << j << ")\n";
                ++qtdArestas;
            }
        }
    }

    std::cout << "\nTotal de arestas: " << qtdArestas << '\n';
    std::cout << "Maximo de arestas possiveis: 45\n";

    // 2. Grau de cada vertice
    std::cout << "\n3. GRAU DOS VERTICES\n\n";

    for (unsigned i = 0; i < graus.size(); ++i)
    {
        std::cout << "Vertice " << i
                  << ": grau " << graus[i] << '\n';
    }

    // 3. Conectividade dos vertices de grau nao nulo
    std::cout << "\n4. CONECTIVIDADE\n\n";

    bool conexo = grafo.eConexo(true);

    std::cout << "Vertices de grau nao nulo pertencem "
              << "a mesma componente conexa? "
              << (conexo ? "SIM" : "NAO") << '\n';

    // 4. Verificar existencia de circuito Euleriano
    std::cout << "\n5. EXISTENCIA DE CIRCUITO EULERIANO\n\n";

    bool euleriano = grafo.temEuleriano();

    std::cout << "O grafo possui circuito Euleriano? "
              << (euleriano ? "SIM" : "NAO") << '\n';

    // 5 e 6. Encontrar e apresentar o circuito
    std::cout << "\n6. CIRCUITO EULERIANO ENCONTRADO\n\n";

    std::vector<int> circuito = grafo.getCircuitoEuler();

    if (!circuito.empty())
    {
        for (unsigned i = 0; i < circuito.size(); ++i)
        {
            std::cout << circuito[i];

            if (i + 1 < circuito.size())
                std::cout << " -> ";
        }

        std::cout << '\n';
    }
    else
    {
        std::cout << "Nenhum circuito encontrado.\n";
    }

    // 7. Validacao automatica
    std::cout << "\n7. VALIDACAO DO CIRCUITO\n\n";

    bool valido = grafo.validaEuleriano();

    std::cout << "Circuito validado automaticamente? "
              << (valido ? "SIM" : "NAO") << '\n';

    std::cout << "Quantidade de arestas do circuito: "
              << (circuito.empty() ? 0 : circuito.size() - 1)
              << '\n';

    std::cout << "Quantidade de arestas do grafo: "
              << qtdArestas << '\n';

    // 8. Quantidade de grafos gerados
    std::cout << "\n8. QUANTIDADE DE TENTATIVAS\n\n";

    std::cout << "Total de grafos gerados: "
              << qtdIteracoes << '\n';

    std::cout << "\n========== FIM DO EXPERIMENTO 1 ==========\n";
}


int main()
{
    experimento1();
    experimento2();

    return 0;
}
