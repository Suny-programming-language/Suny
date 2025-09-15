CC = gcc
SRC = $(wildcard ./src/*.c)
OUT = ./suny$(EXT)
DEBUG = ./dsuny$(EXT)
LIB = ./libSuny.a

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

all:
	@echo Compiling...
	@$(CC) $(SRC) -o $(OUT)
	@$(CC) $(SRC) -DDEBUG -o $(DEBUG)
	@$(CC) -c $(SRC)
	@ar rcs $(LIB) *.o
	@$(RM) *.o
	@echo Done.
