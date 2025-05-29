# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
# Add quiet flag to suppress command output during build
MAKEFLAGS += --silent

# Platform-specific settings
PLATFORM ?= LINUX

ifeq ($(PLATFORM), LINUX)
    INCLUDES = -Iinclude
    # Updated library linking order and names for better compatibility
    LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL
    # Try static linking, but allow fallback to dynamic
    LDFLAGS = -static-libgcc
endif

ifeq ($(PLATFORM), WINDOWS)
    CC = x86_64-w64-mingw32-gcc
    INCLUDES = -Iinclude
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    LDFLAGS = -static-libgcc -static-libstdc++
endif

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
	@echo "Linking executable..."
	@$(CC) $(OBJECTS) -o $@ $(LIBS) $(LDFLAGS)
	@echo "Build completed successfully!"

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if they don't exist
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Clean up
clean:
	@echo "Cleaning object files..."
	@rm -rf $(BUILDDIR)/*.o

clean-all:
	@echo "Cleaning all build artifacts..."
	@rm -rf $(BUILDDIR) $(BINDIR)

# Run the program (suppress terminal output)
run: $(EXECUTABLE)
	@echo "Running birthday animation..."
	@./$(EXECUTABLE) > /dev/null 2>&1

# Run the program with visible output (for debugging)
run-verbose: $(EXECUTABLE)
	@echo "Running birthday animation (verbose mode)..."
	@./$(EXECUTABLE)

# Install dependencies (example for Ubuntu/Debian)
install-deps:
	@echo "Installing dependencies..."
	@sudo apt-get update > /dev/null 2>&1
	@sudo apt-get install -y libraylib-dev > /dev/null 2>&1
	@echo "Dependencies installed successfully!"

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: LDFLAGS = -static-libgcc
debug: $(EXECUTABLE)
	@echo "Debug build completed!"

# Release build with optimizations and static linking
release: CFLAGS += -O3 -DNDEBUG
release: LDFLAGS += -s
release: $(EXECUTABLE)
	@echo "Release build completed!"

# Cross-compile for Windows
windows:
	@echo "Building for Windows..."
	@$(MAKE) PLATFORM=WINDOWS --silent
	@echo "Windows build completed!"

# Build with musl for maximum compatibility (if available)
musl:
	@echo "Building with musl-gcc for maximum compatibility..."
	@$(MAKE) CC=musl-gcc LDFLAGS="-static" --silent || echo "musl-gcc not available, use regular build"

# Alternative static build
static-alt:
	@echo "Building alternative static version..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE) \
		-Wl,-Bstatic $(LIBS) -Wl,-Bdynamic -static-libgcc
	@echo "Alternative static build completed!"

# Debug library linking
debug-libs:
	@echo "Checking available libraries..."
	@pkg-config --libs raylib || echo "raylib not found via pkg-config"
	@ldconfig -p | grep -E "(GL|raylib)" || echo "OpenGL/raylib libraries not found"
	@echo "Attempting simple link test..."
	@$(CC) -o test_link $(SOURCES) $(INCLUDES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor || echo "Link test failed"
	@rm -f test_link

# Help
help:
	@echo "Targets disponíveis:"
	@echo "  all          - Compila o programa completo (padrão)"
	@echo "  clean        - Remove arquivos objeto"
	@echo "  clean-all    - Remove diretórios build e bin"
	@echo "  run          - Executa o programa (sem saída no terminal)"
	@echo "  run-verbose  - Executa o programa (com saída no terminal)"
	@echo "  debug        - Compila com símbolos de debug"
	@echo "  release      - Compila versão otimizada para distribuição"
	@echo "  windows      - Cross-compila para Windows"
	@echo "  install-deps - Instala dependências (Ubuntu/Debian)"

# Phony targets
.PHONY: all clean clean-all run run-verbose install-deps debug release windows help