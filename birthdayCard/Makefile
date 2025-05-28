# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
INCLUDES = -Iinclude
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin
INCLUDEDIR = include

# Source files (todos os arquivos agora fazem parte do mesmo programa)
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/animation.c $(SRCDIR)/balloon.c $(SRCDIR)/star.c $(SRCDIR)/messageInterface.c $(SRCDIR)/messageLoader.c

# Object files
OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/animation.o $(BUILDDIR)/balloon.o $(BUILDDIR)/star.o $(BUILDDIR)/messageInterface.o $(BUILDDIR)/messageLoader.o

# Executable
EXECUTABLE = $(BINDIR)/birthday_animation

# Default target
all: $(EXECUTABLE)

# Build the main executable
$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if they don't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean up
clean:
	rm -rf $(BUILDDIR)/*.o

clean-all:
	rm -rf $(BUILDDIR) $(BINDIR)

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Install dependencies (example for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install libraylib-dev

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: $(EXECUTABLE)

# Help
help:
	@echo "Targets disponíveis:"
	@echo "  all          - Compila o programa completo (padrão)"
	@echo "  clean        - Remove arquivos objeto"
	@echo "  clean-all    - Remove diretórios build e bin"
	@echo "  run          - Executa o programa"
	@echo "  debug        - Compila com símbolos de debug"
	@echo "  install-deps - Instala dependências (Ubuntu/Debian)"

# Phony targets
.PHONY: all clean clean-all run install-deps debug help
