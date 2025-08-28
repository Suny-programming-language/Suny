all:
	@ gcc ./src/main.c \
	./src/slexer.c \
	./src/sparser.c \
	./src/sast.c \
	./src/stool.c \
	./src/serror.c \
	./src/sstr.c \
	./src/stok.c \
	./src/slabel.c \
	./src/sbuiltin.c \
	./src/seval.c \
	./src/sinitialize.c \
	./src/sfunc.c \
	./src/stype.c \
	./src/sframe.c \
	./src/sobj.c \
	./src/svm.c \
	./src/sbuff.c \
	./src/scode.c \
	./src/scompile.c \
	./src/suny.c \
	-o suny


