# DataForge ETL Engine - Makefile (C++)

# Compilador e flags para C++
CXX = g++
# <--- MUDANÇA 1: Adicionado -I$(INCDIR)
CXXFLAGS = -Wall -Wextra -std=c++17 -g -O2 -pedantic -I$(INCDIR)
# <--- MUDANÇA 3: Apenas para consistência, usaremos LDFLAGS na linkagem
LDFLAGS =

# Diretórios
SRCDIR = src
INCDIR = include
BUILDDIR = build
TESTDIR = tests

# Arquivos fonte (agora .cpp!)
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/dataforge

# Regra principal
all: $(TARGET)

# Compilar o programa principal
# <--- MUDANÇA 3: Adicionado $(LDFLAGS) no final
$(TARGET): $(OBJECTS)
	@echo "Linkando $(TARGET)"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "DataForge (C++) compilado com sucesso!"

# Compilar arquivos objeto (.cpp)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compilando $< (C++)"
	@mkdir -p $(dir $@) # Esta linha já cria os subdiretórios necessários!
	$(CXX) $(CXXFLAGS) -c $< -o $@

# <--- MUDANÇA 2: A regra explícita para criar o diretório de build foi removida por ser redundante.

# Executar o programa
run: $(TARGET)
	@echo "Executando DataForge (C++)..."
	@./$(TARGET)

# Compilação com debug
debug: CXXFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Limpeza
clean:
	@echo "Limpando arquivos de build..."
	# <--- MUDANÇA 3: rm -rf $(BUILDDIR) é mais completo.
	@rm -rf $(BUILDDIR)
	@echo "Limpeza concluída!"

# Rebuild completo
rebuild: clean all

# Verificar compilador C++
check:
	@echo "Verificando ambiente C++..."
	@$(CXX) --version
	@echo "C++ configurado e pronto!"

# Mostrar ajuda
help:
	@echo "DataForge ETL (C++) - Comandos Disponíveis:"
	@echo "  make all      - Compilar o projeto"
	@echo "  make run      - Compilar e executar"
	@echo "  make debug    - Compilar com símbolos de debug"
	@echo "  make clean    - Limpar arquivos compilados"
	@echo "  make rebuild  - Limpar e recompilar tudo"
	@echo "  make check    - Verificar compilador C++"
	@echo "  make help     - Mostrar esta ajuda"

.PHONY: all run debug clean rebuild check help