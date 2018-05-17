CC=gcc
LD=gcc
CFLAGS= 
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
OBJ= util-gtk.o window-amf.o controleur-amf.o vue-amf.o modele-amf.o appliaction-apps.o editor-amf.o list.o 

HEAD= util-gtk.h window-amf.h controleur-amf.h vue-amf.h modele-amf.h appliaction-apps.h editor-amf.h list.h 

CODE= util-gtk.c window-amf.c controleur-amf.c vue-amf.c modele-amf.c appliaction-apps.c editor-amf.c list.c 

EXE=auto-makefile

all:$(EXE)

auto-makefile: main-amf.o $(OBJ) 
	@$(LD) -o auto-makefile main-amf.o $(OBJ) $(GTKFLAGS)
	@echo compilation success

main-amf.o:main-amf.c
	@$(CC) -c main-amf.c -o main-amf.o $(CFLAGS) $(GTKFLAGS)

util-gtk.o: util-gtk.h util-gtk.c
	@$(CC) -c util-gtk.c -o util-gtk.o $(CFLAGS) $(GTKFLAGS)

window-amf.o: window-amf.h window-amf.c
	@$(CC) -c window-amf.c -o window-amf.o $(CFLAGS) $(GTKFLAGS)

controleur-amf.o: controleur-amf.h controleur-amf.c
	@$(CC) -c controleur-amf.c -o controleur-amf.o $(CFLAGS) $(GTKFLAGS)

vue-amf.o: vue-amf.h vue-amf.c
	@$(CC) -c vue-amf.c -o vue-amf.o $(CFLAGS) $(GTKFLAGS)

modele-amf.o: modele-amf.h modele-amf.c
	@$(CC) -c modele-amf.c -o modele-amf.o $(CFLAGS) $(GTKFLAGS)

appliaction-apps.o: appliaction-apps.h appliaction-apps.c
	@$(CC) -c appliaction-apps.c -o appliaction-apps.o $(CFLAGS) $(GTKFLAGS)

editor-amf.o: editor-amf.h editor-amf.c
	@$(CC) -c editor-amf.c -o editor-amf.o $(CFLAGS) $(GTKFLAGS)

list.o: list.h list.c
	@$(CC) -c list.c -o list.o $(CFLAGS) $(GTKFLAGS)

open:
	@open -a SublimeText $(HEAD) $(CODE) main-amf.c 

tar:
	@tar -czf auto-makefile.tar.gz $(HEAD) $(CODE) main-amf.c Makefile


clean:
	@rm -f *.o
	@rm -f auto-makefile



### gtk version -> gtk+2
### to install gtk with Homebrew [https://brew.sh/index_fr]
### -> (brew install gtk+)
### made with auto-makefile mac edition
### autor Arthur Detrembleur (Appliaction company)
