
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iexterno

OBJ_DIR = build/obj
BIN_DIR = build/bin

# Arquivos de implementação
OBJ = $(OBJ_DIR)/geradorGrafo.o $(OBJ_DIR)/grafo.o

# Testes
TEST_GERADOR = $(BIN_DIR)/testeGeradorGrafo
TEST_GRAFO = $(BIN_DIR)/grafo_teste

.PHONY: all test clean

all: $(TEST_GERADOR)

# Criar diretórios
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Compilar implementações
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Teste do gerador
$(TEST_GERADOR): test/testeGeradorGrafo.cpp $(OBJ_DIR)/geradorGrafo.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Teste do grafo
$(TEST_GRAFO): test/grafo_teste.cpp $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Executar os testes
test: all
	./$(TEST_GERADOR)

# Limpar arquivos compilados
clean:
	rm -rf build
