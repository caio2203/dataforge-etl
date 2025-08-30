# Makefile para o DataForge ETL Engine (Versão Refatorada e Robusta)

# ==========================================================
#  1. VARIÁVEIS DE PROJETO
# ==========================================================
CXX = g++
TARGET = build/dataforge

# Diretórios
SRCDIR = src
INCDIR = include
BUILDDIR = build
SERIALIZER_DIR = vendor/fast-serializer

# ==========================================================
#  2. FLAGS DE COMPILAÇÃO E LINKAGEM
# ==========================================================
# -g para debug, -O2 para otimização, -Wall e -Wextra para todos os avisos.
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

# Adiciona todos os diretórios de include necessários.
CXXFLAGS += -I$(INCDIR)
CXXFLAGS += -I$(SERIALIZER_DIR)/include

# Flags para o linkador. -pthread é essencial para std::thread.
LDFLAGS = -pthread

# ==========================================================
#  3. BUSCA DE ARQUIVOS FONTE
# ==========================================================
# Fontes do nosso motor (encontra todos os .cpp em src/ e subpastas)
ENGINE_SRCS = $(shell find $(SRCDIR) -name '*.cpp')

# Fontes da nossa biblioteca (excluindo o main.cpp de teste dela)
SERIALIZER_SRCS = $(shell find $(SERIALIZER_DIR)/src -name '*.cpp' ! -name 'main.cpp')

# Mapeia todos os fontes para arquivos objeto
ENGINE_OBJS = $(ENGINE_SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
SERIALIZER_OBJS = $(SERIALIZER_SRCS:$(SERIALIZER_DIR)/src/%.cpp=$(BUILDDIR)/lib/%.o)
OBJECTS = $(ENGINE_OBJS) $(SERIALIZER_OBJS)

# ==========================================================
#  4. REGRAS DE COMPILAÇÃO
# ==========================================================

# Regra principal, default quando 'make' é chamado.
all: $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJECTS)
	@echo "Linkando executável final: $@"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Regra para compilar os fontes do motor
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compilando motor: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar os fontes da biblioteca do submódulo
$(BUILDDIR)/lib/%.o: $(SERIALIZER_DIR)/src/%.cpp
	@mkdir -p $(@D)
	@echo "Compilando lib: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar com flags de debug extras
debug: CXXFLAGS += -DDEBUG -g3
debug: all

# Regra para limpar o projeto
clean:
	@echo "Limpando o projeto..."
	@rm -rf $(BUILDDIR)

# Declara alvos que não são arquivos
.PHONY: all debug clean