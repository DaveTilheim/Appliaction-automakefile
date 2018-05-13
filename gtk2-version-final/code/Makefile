CC=gcc
LD=gcc
CFLAGS= 
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
EXE=auto-makefile

all:$(EXE)

auto-makefile: main.o controleur.o vue.o modele.o list.o 
	@$(LD) -o auto-makefile main.o controleur.o vue.o modele.o list.o $(GTKFLAGS)
	@echo compilation success

main.o:main.c
	@$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

controleur.o: controleur.h controleur.c
	@$(CC) -c controleur.c -o controleur.o $(CFLAGS) $(GTKFLAGS)

vue.o: vue.h vue.c
	@$(CC) -c vue.c -o vue.o $(CFLAGS) $(GTKFLAGS)

modele.o: modele.h modele.c
	@$(CC) -c modele.c -o modele.o $(CFLAGS) $(GTKFLAGS)

list.o: list.h list.c
	@$(CC) -c list.c -o list.o $(CFLAGS) $(GTKFLAGS)

open:
	@open -a SublimeText controleur.c controleur.h vue.c vue.h modele.c modele.h list.c list.h main.c 

tar:
	@tar -czf auto-makefile.tar.gz controleur.c controleur.h vue.c vue.h modele.c modele.h list.c list.h main.c Makefile


clean:
	@rm -f *.o
	@rm -f auto-makefile



### gtk version -> gtk+2
### to install gtk with Homebrew [https://brew.sh/index_fr]
### -> (brew install gtk+)
### made with auto-makefile mac edition
### autor Arthur Detrembleur (Appliaction company)
