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

<<<<<<< Updated upstream
# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target
TARGET = $(BIN_DIR)/birthday_animation

# Create necessary directories
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/*.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
=======
# Source files (todos os arquivos agora fazem parte do mesmo programa)
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/animation.c $(SRCDIR)/balloon.c $(SRCDIR)/star.c $(SRCDIR)/messageInterface.c

# Object files
OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/animation.o $(BUILDDIR)/balloon.o $(BUILDDIR)/star.o $(BUILDDIR)/messageInterface.o

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
>>>>>>> Stashed changes
clean:
	rm -rf $(BUILDDIR)/*.o

<<<<<<< Updated upstream
# Run the program
run: $(TARGET)
	$(TARGET)

.PHONY: all clean run
=======
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
>>>>>>> Stashed changes
