# Variáveis
CC = gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces
INCLUDE = -I./include
RAYLIB_PATH = /usr/local/include
RAYLIB_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Arquivos fonte e objetos
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Criar diretórios se não existirem
DIRS = $(OBJ_DIR) $(BIN_DIR)

# Nome do executável
EXEC = $(BIN_DIR)/feliz_aniversario

# Arquivos fonte e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão
all: directories $(EXEC)

# Criar diretórios
directories:
	mkdir -p $(DIRS)

# Compilar o executável
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(RAYLIB_LIBS)

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

# Regra para reconstruir tudo
rebuild: clean all

# Executar o programa
run: all
	$(EXEC)

.PHONY: all clean rebuild run directories