/**
@file modele-amf.c
@brief contains the C code about the modele of the app
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include <gtk/gtk.h>
#include "modele-amf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"

Modele_t *creer_modele(void){

	Modele_t *m = malloc(sizeof(Modele_t));
	if(m == NULL)
		return NULL;
	m->gtkMode = 0;
	m->libSepMode = 0;
	m->libComMode = 0;
	m->checkFileMode = 0;
	m->tlib = 0;
	m->openAppMode = 0;
	m->compressedMode = 0;
	m->lib = NULL;
	m->customCflagsMode = 0;
	m->childMode = 0;

	return m;
}

void destroy_modele(Modele_t *m){
	
	assert(m != NULL);

	if(m->lib != NULL){
		for(int i = 0; i < m->tlib; i++)
			free(m->lib[i]);
		free(m->lib);
	}
	free(m);
}

void active_mode(Modele_t *m, int mode){

	assert(m != NULL && mode > 0 && mode <= N_MODE);

	switch(mode){

		case 1:

			m->gtkMode++;
			if(m->gtkMode == 2)
				m->gtkMode = 0;
			break;

		case 2:

			m->libSepMode++;
			if(m->libSepMode == 2)
				m->libSepMode = 0;
			break;

		case 3:

			m->libComMode++;
			if(m->libComMode == 2)
				m->libComMode = 0;
			break;

		case 4:

			m->checkFileMode++;
			if(m->checkFileMode == 2)
				m->checkFileMode = 0;
			break;

		case 5:

			m->openAppMode++;
			if(m->openAppMode == 2)
				m->openAppMode = 0;
			break;

		case 6:

			m->compressedMode++;
			if(m->compressedMode == 2)
				m->compressedMode = 0;
			break;

		case 7:

			m->customCflagsMode++;
			if(m->customCflagsMode == 2)
				m->customCflagsMode = 0;
			break;

		case 8:

			m->childMode++;
			if(m->childMode == 2)
				m->childMode = 0;
			break;

		default:
			fprintf(stderr, "ERROR\n");
			break;
	}
}

/**
@fn static char **create_str(unsigned int n)
@brief create a dynamic matrix of string
@param n the number of string
@post new matrix of string 
@return a double char pointer 
*/
static char **create_str(unsigned int n);

static char **create_str(unsigned int n){

	if(!n)
		return NULL;
	char **str = malloc(sizeof(char *)*n);
	if(!str)
		return NULL;
	for(int i = 0; i < n; i++){
		str[i] = malloc(sizeof(char)*(MAXC+1));
		if(!str[i])
			return NULL;
	}

	return str;
}

/**
@fn static void make_file(Modele_t *m)
@brief create a Makefile
@param m the modele of the app
@pre m != NULL
@post Makefile created
*/
static void make_file(Modele_t *m);

static void make_file(Modele_t *m){

	assert(m != NULL);

	FILE *makefile = fopen("Makefile", "w");
	if(!makefile){
		fprintf(stderr, "ERROR\n");
		return;
	}

	fprintf(makefile, "CC=gcc\nLD=gcc\n");
	if(m->customCflagsMode)
		fprintf(makefile, "CFLAGS=%s\n", m->cflags);
	else
		fprintf(makefile, "CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes\n");
	if(m->gtkMode) 
		fprintf(makefile, "GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`\n");
	fprintf(makefile, "OBJ= ");
	for(int i = 0; i < m->tlib; i++)
		fprintf(makefile, "%s.o ", m->lib[i]);
	fprintf(makefile, "\n");
	fprintf(makefile, "HEAD= ");
	for(int i = 0; i < m->tlib; i++)
		fprintf(makefile, "%s.h ", m->lib[i]);
	fprintf(makefile, "\n");
	fprintf(makefile, "CODE= ");
	for(int i = 0; i < m->tlib; i++)
		fprintf(makefile, "%s.c ", m->lib[i]);
	fprintf(makefile, "\n");

	fprintf(makefile, "EXE=%s\n\nall:$(EXE)\n\n", m->exe);
	fprintf(makefile, "%s: ", m->exe);
	if(m->libSepMode || m->libComMode)
		fprintf(makefile, "lib ");
	fprintf(makefile, "%s.o ", m->main );
	fprintf(makefile, "$(OBJ) ");
	fprintf(makefile, "\n");
	fprintf(makefile, "\t@$(LD) -o %s %s.o ", m->exe, m->main);

	if(m->libSepMode){
		fprintf(makefile, "-L. ");
		for(int i = 0; i < m->tlib; i++)
			fprintf(makefile, "-l%s ", m->lib[i]);
	}
	else if(m->libComMode){
		fprintf(makefile, "-L. -lmulti ");
	}
	else{
		fprintf(makefile, "$(OBJ) ");
	}

	if(m->gtkMode)
		fprintf(makefile, "$(GTKFLAGS)");
	fprintf(makefile, "\n\t@echo compilation success");
	fprintf(makefile, "\n\n");
	fprintf(makefile, "%s.o:%s.c\n", m->main, m->main);
	fprintf(makefile, "\t@$(CC) -c %s.c -o %s.o $(CFLAGS) ", m->main, m->main);
	if(m->gtkMode)
		fprintf(makefile, "$(GTKFLAGS)");
	fprintf(makefile, "\n\n");

	if(!m->libComMode && !m->libSepMode){
		for(int i = 0; i < m->tlib; i++){
			fprintf(makefile, "%s.o: %s.h %s.c\n", m->lib[i], m->lib[i], m->lib[i]);
			fprintf(makefile, "\t@$(CC) -c %s.c -o %s.o $(CFLAGS) ", m->lib[i], m->lib[i]);
			if(m->gtkMode)
				fprintf(makefile, "$(GTKFLAGS)");
			fprintf(makefile, "\n\n");
		}
	}
	else{
		fprintf(makefile, "lib: \n");
		if(m->libSepMode){
			for(int i = 0; i < m->tlib; i++){
				fprintf(makefile, "\t@$(CC) -c %s.c -o %s.o $(GTKFLAGS)\n", m->lib[i], m->lib[i]);
				fprintf(makefile, "\t@ar ruv lib%s.a %s.o\n", m->lib[i], m->lib[i]);
				fprintf(makefile, "\t@ranlib lib%s.a\n\n", m->lib[i]);
			}
			fprintf(makefile, "\n\n");;
		}else if(m->libComMode){
			for(int i = 0; i < m->tlib; i++)
				fprintf(makefile, "\t@$(CC) -c %s.c -o %s.o $(GTKFLAGS)\n", m->lib[i], m->lib[i]);
			fprintf(makefile, "\t@ar ruv libmulti.a ");
			fprintf(makefile, "$(OBJ) ");
			fprintf(makefile, "\n\t@ranlib libmulti.a\n\n");
			fprintf(makefile, "\n\n");
		}
	}

	if(m->childMode){
		fprintf(makefile, ".PHONY: ");
		for(int i = 0; i < strlen(m->child); i++){
			if(m->child[i] != ';')
				fprintf(makefile, "%c", m->child[i]);
			else
				fprintf(makefile, " ");
		}
		fprintf(makefile, "\n\n");
		
		unsigned int nchild = 1;
		int savePos = 0;
		int savePos2 = 0;
		for(int i = 0; i < strlen(m->child)-1; i++)
			if(m->child[i] == ';')
				nchild++;
		if(strlen(m->child)-1 != ';'){
			m->child[strlen(m->child)] = ';';
			m->child[strlen(m->child)+1] = '\0';
		}

		for(int i = 0; i < nchild; i++){
			int j;
			if(i == 0)
				savePos = savePos2;
			else
				savePos = ++savePos2;
			for(j = savePos; m->child[j] != ';'; j++){
				fprintf(makefile, "%c", m->child[j]);
			}
			savePos2 = j;
			fprintf(makefile, ":\n\t@(cd ");
			for(j = savePos; m->child[j] != ';'; j++){
				fprintf(makefile, "%c", m->child[j]);
			}
			fprintf(makefile, " ;MAKE)\n");
		}
	}

	if(m->openAppMode){
		fprintf(makefile, "open:\n");
		#ifdef __APPLE__
		fprintf(makefile, "\t@open -a %s ", m->app);
		#else
		fprintf(makefile, "\t@%s ", m->app);
		#endif
		fprintf(makefile, "$(HEAD) $(CODE) ");
		
		fprintf(makefile, "%s.c ", m->main);
		#ifdef __linux__
		fprintf(makefile, "&\n");
		#endif
		fprintf(makefile, "\n\n");
	}

	if(m->compressedMode){
		fprintf(makefile, "tar:\n");
		fprintf(makefile, "\t@tar -czf %s.tar.gz ", m->exe);
		
		fprintf(makefile, "$(HEAD) $(CODE) ");

		fprintf(makefile, "%s.c Makefile\n", m->main);
		fprintf(makefile, "\n\n");
	}
	fprintf(makefile, "clean:\n");
	fprintf(makefile, "\t@rm -f *.o\n\t@rm -f %s", m->exe);

	fprintf(makefile, "\n\n\n\n");
	fprintf(makefile, "### gtk version -> gtk+2\n");
	#ifdef __APPLE__
	fprintf(makefile, "### to install gtk with Homebrew [https://brew.sh/index_fr]\n");
	fprintf(makefile, "### -> (brew install gtk+)\n");
	#else 
	fprintf(makefile, "### to install gtk\n");
	fprintf(makefile, "### -> (apt-get install gtk+2)\n");
	#endif
	fprintf(makefile, "### made with auto-makefile ");
	#ifdef __APPLE__
	fprintf(makefile, "mac edition\n");
	#else
	fprintf(makefile, "linux edition\n");
	#endif
	fprintf(makefile, "### autor Arthur Detrembleur (Appliaction company)\n");
	

	
	fclose(makefile);
}

/**
@fn static int exist_files(Modele_t *m)
@brief indicates if the libs exist
@param m the modele of the app
@pre m != NULL
@post libs exist or not
@return 1 succes   0 not exist
*/
static int exist_files(Modele_t *m);

static int exist_files(Modele_t *m){

	assert(m != NULL);

	long k = strlen(m->main);
	m->main[k] = '.';
	m->main[k+1] = 'c';
	m->main[k+2] = '\0';
	FILE *fcheck = fopen(m->main, "r");
	if(!fcheck)
		return 0;
	m->main[k] = '\0';
	fclose(fcheck);
	for(int i = 0; i < m->tlib; i++){
		long j = strlen(m->lib[i]);
		m->lib[i][j] = '.';
		m->lib[i][j+1] = 'c';
		m->lib[i][j+2] = '\0';
		fcheck = fopen(m->lib[i], "r");
		if(!fcheck)
			return 0;
		m->lib[i][j] = '\0';
		fclose(fcheck);
	}
	return 1;
}



int run(Modele_t *m, GtkWidget *entryExeName, GtkWidget *entryMainName, List *entryLibName, GtkWidget *entryApp){

	assert(m != NULL && entryExeName != NULL && entryMainName != NULL && entryApp != NULL);

	strcpy(m->exe, (char *) gtk_entry_get_text(GTK_ENTRY(entryExeName)));
	strcpy(m->main, (char *) gtk_entry_get_text(GTK_ENTRY(entryMainName)));
	m->tlib = length_list(entryLibName);
	m->lib = create_str(m->tlib);
	for(int i = length_list(entryLibName)-1; i >= 0; i--)
		strcpy(m->lib[i],  (char *) gtk_entry_get_text(GTK_ENTRY(get_element(entryLibName, i))));

	if(m->checkFileMode && !exist_files(m)){
		return 0;
	}
	if(m->openAppMode){
		strcpy(m->app, (char *) gtk_entry_get_text(GTK_ENTRY(entryApp)));
	}
	
	make_file(m);

	return 1;

}


void make_rapport(Modele_t *m){

	assert(m != NULL);

	FILE *frapport = fopen("rapport.txt", "w");
	if(!frapport)
		return;
	fprintf(frapport, "RAPPORT AUTO-MAKEFILE\n\n");
	fprintf(frapport, "exe -> %s\n", m->exe);
	fprintf(frapport, "main -> %s\n", m->main);
	fprintf(frapport, "%d lib(s)\n", m->tlib);
	for(int i = 0; i < m->tlib; i++)
		fprintf(frapport, "lib%d -> %s\n", i+1, m->lib[i]);
	fprintf(frapport, "gtk mode -> %d\n", m->gtkMode);
	fprintf(frapport, "sep. libs -> %d\n", m->libSepMode);
	fprintf(frapport, "com. lib -> %d\n", m->libComMode);
	fprintf(frapport, "check files mode -> %d\n", m->checkFileMode);
	fprintf(frapport, "compress mode -> %d\n", m->compressedMode);
	fprintf(frapport, "custom CFLAGS mode -> %d\n", m->customCflagsMode);
	if(m->customCflagsMode)
		fprintf(frapport, "CFLAGS -> %s\n", m->cflags);
	fprintf(frapport, "child mode -> %d\n", m->childMode);
	if(m->childMode)
		fprintf(frapport, "child(ren) directories -> %s\n", m->child);
	fprintf(frapport, "open app mode -> %d\n", m->openAppMode);
	if(m->openAppMode)
		fprintf(frapport, "App -> %s\n", m->app);
	fprintf(frapport, "\nEND RAPPORT");
	fclose(frapport);
}








