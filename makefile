CC = gcc
SRC = $(wildcard ./src/*.c)
OUT = ./bin/suny
DEBUG = ./bin/dsuny
LIB = ./bin/libSuny.a

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

all:
	@echo Compiling...
	@$(CC) $(SRC) -o $(OUT) $(EXT)
	@$(CC) $(SRC) -DDEBUG -o $(DEBUG) $(EXT)
	@$(CC) -c $(SRC)
	@ar rcs $(LIB) *.o
	@$(RM) *.o
	@echo Done.

