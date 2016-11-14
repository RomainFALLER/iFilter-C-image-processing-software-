CFLAGS = -Wall
CLIBS = -lglut -lGL -lGLU  -lm -lX11 -lpthread

all: iFilter iFilter.o  fct_affichage.o 

iFilter: iFilter.o fct_affichage.o libisentlib.a filtres.o compression.o
	gcc $(CFLAGS) iFilter.o fct_affichage.o filtres.o compression.o BmpLib.o ESLib.o ErreurLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o libisentlib.a -o iFilter  $(CLIBS)
	
fct_affichage.o:	fct_affichage.c mes_fonctions.h
	gcc $(CFLAGS) -c fct_affichage.c	

iFilter.o: iFilter.c mes_fonctions.h
	 gcc $(CFLAGS) -c iFilter.c

filtres.o: filtres.c GfxLib.h mes_fonctions.h ESLib.h
	gcc -Wall -O2 -c filtres.c

compression.o: compression.c GfxLib.h ESLib.h mes_fonctions.h
	gcc -Wall -O2 -c compression.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c mes_fonctions.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c

ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c

TortueLib.o: TortueLib.c TortueLib.h GfxLib.h
	gcc -Wall -O2 -c TortueLib.c

VectorLib.o: VectorLib.c VectorLib.h
	gcc -Wall -O2 -c VectorLib.c -msse3

WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc -Wall -O2 -c WavLib.c -Wno-unused-result

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

deepclean: clean
	rm -f iFilter libisentlib.a

clean:
	rm -f iFilter
	rm -f *.o
