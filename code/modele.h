#ifndef __MODELE__
#define __MODELE__

#define MAX_NEW_F 3
#define MAXC 20
#include "list.h"

#define MAX_LIB 15
#define MIN_LIB 0
#define MAXC_CFLAGS 50
#define MAXC_CHILD 51
#define N_MODE 8

typedef struct{

	char exe[MAXC+1];
	char main[MAXC+1];
	char **lib;
	int tlib;
	int gtkMode;
	int libSepMode;
	int libComMode;
	int checkFileMode;
	int openAppMode;
	char app[MAXC+1];
	int compressedMode;
	int customCflagsMode;
	char cflags[MAXC_CFLAGS+1];
	int childMode;
	char child[MAXC_CHILD+1];


}Modele_t;

Modele_t *creer_modele(void);

void destroy_modele(Modele_t *m);

void active_mode(Modele_t *m, int mode);

int run(Modele_t *m, GtkWidget *entryExeName, GtkWidget *entryMainName, List *entryLibName, GtkWidget *entryApp);

void make_rapport(Modele_t *m);


#endif
