
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iexterno

OBJ_DIR = build/obj
BIN_DIR = build/bin

# Arquivos de implementação
OBJ = $(OBJ_DIR)/geradorGrafo.o $(OBJ_DIR)/grafo.o

# Testes
TEST_GERADOR = $(BIN_DIR)/testeGeradorGrafo
TEST_GRAFO = $(BIN_DIR)/grafo_teste

# Experimento
EXEC_EXPERIMENTO = $(BIN_DIR)/experimento

.PHONY: all test experimento clean

all: $(TEST_GRAFO) $(TEST_GERADOR)

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

# Compilar o experimento
$(EXEC_EXPERIMENTO): experimento/experimento.cpp $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Executar os testes
test: all
	./$(TEST_GRAFO)
	./$(TEST_GERADOR)

# Executar o experimento
experimento: $(EXEC_EXPERIMENTO)
	./$(EXEC_EXPERIMENTO)

# Limpar arquivos compilados
clean:
	rm -rf build
