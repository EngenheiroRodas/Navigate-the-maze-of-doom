# Compiler
CC = gcc

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
TARGET = graph_visualizer

# Source files
SRCS = main.c graph.c visualization.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
