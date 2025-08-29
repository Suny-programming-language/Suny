CC = gcc
SRC = $(wildcard ./src/*.c)
OUT = suny
DEBUG = dsuny

all:
	@echo Compiling...
	@$(CC) $(SRC) -o $(OUT)
	@$(CC) $(SRC) -DDEBUG -o $(DEBUG)
	@echo Done.