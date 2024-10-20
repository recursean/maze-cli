# Compiler 
CC = cc
# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = maze.c maze_gen.c stack.c ncurses_funcs.c
# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)
# Link with external libraries
LIBS = -lncurses   

# Default target
all: maze

# Rule to build the final executable
maze: $(OBJS)
	$(CC) $(CFLAGS) -o maze $(OBJS) $(LIBS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f maze $(OBJS)

# Phony targets
.PHONY: all clean