CC = gcc
SRC = $(wildcard ./src/*.c)

OUT = ./suny$(EXT)
DEBUG = ./dsuny$(EXT)
LIB = ./libSuny.a
DLL = ./Suny.dll
IMPLIB = ./libSuny.dll.a

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

all: exe lib dll

exe:
	@echo Compiling EXE...
	@$(CC) $(SRC) -o $(OUT)
	@$(CC) $(SRC) -DDEBUG -o $(DEBUG)
	@echo Done EXE.

lib:
	@echo Compiling Static Library...
	@$(CC) -c $(SRC)
	@ar rcs $(LIB) *.o
	@$(RM) *.o
	@echo Done LIB.

dll:
	@echo Compiling DLL...
	@$(CC) -shared $(SRC) -o $(DLL) \
		-Wl,--out-implib=$(IMPLIB)
	@echo Done DLL.

clean:
	@echo Cleaning...
	@$(RM) *.o
	@$(RM) $(OUT)
	@$(RM) $(DEBUG)
	@$(RM) $(LIB)
	@$(RM) $(DLL)
	@$(RM) $(IMPLIB)
	@echo Done.
