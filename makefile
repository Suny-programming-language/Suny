all:
	@ gcc ./src/main.c \
	./src/slexer.c \
	./src/sparser.c \
	./src/sast.c \
	./src/stool.c \
	./src/serror.c \
	./src/stok.c \
	./src/sframe.c \
	./src/sobj.c \
	./src/svm.c \
	./src/sbuff.c \
	./src/scode.c \
	./src/scompile.c \
	./src/suny.c \
	-o ./bin/suny
