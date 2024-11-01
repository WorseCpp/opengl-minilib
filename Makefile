.PHONY: all, save, clean

SRC_DIR = ./src/

_CPPFILES = main.cpp FragmentShader.cpp VertexShader.cpp ShaderProgram.cpp Vertices.cpp glCommon.cpp Camera.cpp InputFocusHandlers.cpp EBO.cpp MemAlloc.cpp

_CFILES = glad.c

# Update CPPFILES to include SRC_DIR
CPPFILES = $(addprefix $(SRC_DIR), $(_CPPFILES:.cpp=.o))
CFILES = $(addprefix $(SRC_DIR), $(_CFILES:.c=.o))

OBJFILES = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

CUSTOM_SETTINGS = -Wall -O3

INC=-I../include/glm -I../include/ -I./inc/

# CC stands for C Compiler
CCPP = g++

CC = gcc

LIB = -lglfw -lGL

all: $(OBJFILES)

	$(CCPP) -o test $(OBJFILES) $(LIB)

%.o: %.cpp
	$(CCPP) $(CUSTOM_SETTINGS) $(INC) -c $^ -o $@

%.o: %.c
	$(CC) $(CUSTOM_SETTINGS) $(INC) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)/*.o
	rm -f test

save:
	git add ./
	git commit -m "Makefile autosave"
	git push
