CC = gcc
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
OUT = suny
DEBUG = dsuny
LIB = libSuny.a

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

all: $(OUT)$(EXT) $(DEBUG)$(EXT) $(LIB)

bin: $(OUT)$(EXT)

debug: $(DEBUG)$(EXT)

lib: $(LIB)

$(OUT)$(EXT): $(SRC)
	@echo Building release exe...
	@$(CC) $(SRC) -o $@

$(DEBUG)$(EXT): $(SRC)
	@echo Building debug exe...
	@$(CC) -DDEBUG $(SRC) -o $@

$(LIB): $(OBJ)
	@echo Building static library...
	ar rcs $(LIB) $(OBJ)

./src/%.o: ./src/%.c ./src/Suny.h
	$(CC) -c $< -o $@

clean:
	del /Q .\src\*.o

