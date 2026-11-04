# trab_grafos_26_2
Trabalho de G2 da aluna Mayara Ramos Damazio para a disciplina INF1631 - Estruturas Discretas


Uso do Makefile:

make	Compila os dois executáveis de teste
make test	Compila o necessário e executa os testes
make clean	Apaga a pasta build/
make -B	Força a recompilação


Comando	Função
TEST_CASE("nome")	Cria um caso de teste
CHECK(condicao)	Verifica uma condição e continua mesmo se falhar
REQUIRE(condicao)	Verifica uma condição e interrompe o teste se falhar
SUBCASE("nome")	Divide um teste em cenários diferentes
CHECK_THROWS_AS(expr, tipo)	Verifica se uma expressão lança a exceção esperada
doctest::Approx(valor)	Compara números decimais com tolerância