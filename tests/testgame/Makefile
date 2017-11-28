NAME = gametest

SOURCES = $(wildcard *.c)

OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

CC = gcc

#LIBS = -Wl,-Bstatic -Wl,--start-group -lbackfire -lSDL2main -lSDL2 -lGLEW -Wl,--end-group -Wl,-Bdynamic -lGL -lm
LIBS = -lbackfire -lSDL2_image -lSDL2main -lSDL2 -lGLEW -lGL -lm

#COMPILE_FLAGS = -g -Wall -O2 -s -o
COMPILE_FLAGS = -g -Wall -o

all: $(OBJECTS)
	$(CC) $^ $(COMPILE_FLAGS) $(NAME) $(LIBS)

clean:
	rm -f $(OBJECTS) $(COMPILENAME)
