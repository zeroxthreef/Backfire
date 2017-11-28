ENGINE_CLIENT_LIB = libbackfire.a
ENGINE_SERVER_LIB = libbackfireDS.a

ENGINE_CLIENT_SOURCES = $(wildcard src/client/*.c)
ENGINE_SERVER_SOURCES = $(wildcard src/server/*.c)

ENGINE_CLIENT_OBJECTS = $(addsuffix .o, $(basename $(ENGINE_CLIENT_SOURCES)))
ENGINE_SERVER_OBJECTS = $(addsuffix .o, $(basename $(ENGINE_SERVER_SOURCES)))

#ENGINE_CLIENT_OBJECTS = $(wildcard *.o)

CC = gcc
AR = ar

#ENGINE_CLIENT_LIBS = -lSDL2 -lm -lpthread -lGLEW -lGL
ENGINE_CLIENT_LIBS = -Wl,-Bstatic -lSDL2main -lSDL2 -lSDL2_image -lm -lpthread -lGLEW -Wl,-Bdynamic -lGL
ENGINE_SERVER_LIBS = -Wl,-Bstatic -lSDL2main -lSDL2 -lm -lpthread

ENGINE_HEADER_DIR = include

#COMPILE_FLAGS = -g -Wall -O2 -s -c
COMPILE_FLAGS = -g -Wall -c

.PHONY: all client server clean_client clean_server install

all: client server

clean: clean_client clean_server

client: client_preparedir $(ENGINE_CLIENT_OBJECTS)
	$(AR) rcs $(ENGINE_CLIENT_LIB) $(ENGINE_CLIENT_OBJECTS)
	mv $(ENGINE_CLIENT_LIB) bin/backfire/client

client_preparedir:
	sdl-config --static-libs
	mkdir -p bin/backfire
	mkdir -p bin/backfire/client

$(ENGINE_CLIENT_OBJECTS): src/client/%.o : src/client/%.c
	$(CC) $(COMPILE_FLAGS) $< -I$(ENGINE_HEADER_DIR) $(ENGINE_CLIENT_LIBS) -o $@


server: server_preparedir $(ENGINE_SERVER_OBJECTS)
	sdl-config --static-libs
	$(AR) rcs $(ENGINE_SERVER_LIB) $(ENGINE_SERVER_OBJECTS)
	mv $(ENGINE_SERVER_LIB) bin/backfire/server

server_preparedir:
	mkdir -p bin/backfire
	mkdir -p bin/backfire/server

$(ENGINE_SERVER_OBJECTS): src/server/%.o : src/server/%.c
	$(CC) $(COMPILE_FLAGS) $< -I$(ENGINE_HEADER_DIR) $(ENGINE_SERVER_LIBS) -o $@

clean_client:
	rm -f $(ENGINE_CLIENT_OBJECTS) $(ENGINE_CLIENT_LIB) $(ENGINE_CLIENT_LIB)

clean_server:
	rm -f $(ENGINE_SERVER_OBJECTS) $(ENGINE_SERVER_LIB) $(ENGINE_SERVER_LIB)

install:
	cp -r include/client /usr/local/include/
	cp -r include/server /usr/local/include/
	#cp -r bin/backfire/ /usr/local/lib/backfire/
	cp bin/backfire/client/$(ENGINE_CLIENT_LIB) /usr/local/lib/
	cp bin/backfire/server/$(ENGINE_SERVER_LIB) /usr/local/lib/
