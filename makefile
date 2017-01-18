SILNIK=engine.c
NAGLOWEK=header.h
GRA=main.c

all: gra engine.o graphics.o clean engine.o graphics.o

gra: main.c engine.o graphics.o
	gcc main.c engine.o graphics.o -o gra -lncurses

engine.o: header.h engine.h engine.c
	gcc -c engine.c -o engine.o -lncurses

graphics.o: header.h graphics.h graphics.c
	gcc -c graphics.c -o graphics.o -lncurses

clean:
	@rm -f engine.o graphics.o
	@echo "Usunieto engine.o graphics.o"

.PHONY: all clean
