# Compiler
CC = gcc

# Debug and optimization flags
ifdef DEBUG
    MODE = -g
else
    MODE = -O3
endif

# Compiler flags
CFLAGS = $(MODE) -fdiagnostics-color=always -Wall 

# Libraries for OpenGL
LIBS = -lGL -lGLU -lglut -lm

# Target executable
TARGET = visual

# Source and header files
SRCS = main.c graph.c visualization.c stack.c
HEADERS = visualization.h graph.h stack.h

# Object files
OBJS = $(SRCS:.c=.o)

# Default build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Rule for creating object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean
