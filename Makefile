CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

# --- CAMINHOS ---
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/dataforge
SRCDIR = src

# Adiciona o diretório de include principal nas flags do compilador
CXXFLAGS += -I$(INCDIR)
CXXFLAGS += -I$(SRCDIR) # caminho para o diretorio biblioteca json
CXXFLAGS += -I$(SERIALIZER_DIR)/include

# --- DEPENDÊNCIA (SUBMÓDULO) ---
SERIALIZER_DIR = vendor/fast-serializer
# Adiciona o include da biblioteca nas flags do compilador
CXXFLAGS += -I$(SERIALIZER_DIR)/include

# --- ARQUIVOS FONTE ---
ENGINE_SRCS = $(shell find $(SRCDIR) -name '*.cpp')
SERIALIZER_SRCS = $(shell find $(SERIALIZER_DIR)/src -name '*.cpp' ! -name 'main.cpp')

# Mapeia fontes para arquivos objeto
ENGINE_OBJS = $(ENGINE_SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
SERIALIZER_OBJS = $(SERIALIZER_SRCS:$(SERIALIZER_DIR)/src/%.cpp=$(BUILDDIR)/lib/%.o)
OBJECTS = $(ENGINE_OBJS) $(SERIALIZER_OBJS)

# --- REGRAS DE COMPILAÇÃO ---
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linkando executável final $@"
	$(CXX) $(OBJECTS) -o $@

# Regra para compilar fontes do motor
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar fontes da biblioteca
$(BUILDDIR)/lib/%.o: $(SERIALIZER_DIR)/src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += -DDEBUG -g3
debug: all

clean:
	@echo "Limpando o projeto..."
	@rm -rf $(BUILDDIR)

.PHONY: all debug clean