#include <gtk/gtk.h>
#include "modele.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	
	if(m->lib != NULL){
		for(int i = 0; i < m->tlib; i++)
			free(m->lib[i]);
		free(m->lib);
	}
	free(m);
}

void active_mode(Modele_t *m, int mode){

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
	}
}

static char **create_str(int n){

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

static void make_file(Modele_t *m){

	FILE *makefile = fopen("Makefile", "w");
	if(!makefile)
		abort();

	fprintf(makefile, "CC=gcc\nLD=gcc\n");
	if(m->customCflagsMode)
		fprintf(makefile, "CFLAGS=%s\n", m->cflags);
	else
		fprintf(makefile, "CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes\n");
	if(m->gtkMode) 
		fprintf(makefile, "GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`\n");
	fprintf(makefile, "EXE=%s\n\nall:$(EXE)\n\n", m->exe);
	fprintf(makefile, "%s: ", m->exe);
	if(m->libSepMode || m->libComMode)
		fprintf(makefile, "lib ");
	fprintf(makefile, "%s.o ", m->main );
	for(int i = 0; i < m->tlib; i++)
		fprintf(makefile, "%s.o ", m->lib[i]);
	fprintf(makefile, "\n");
	fprintf(makefile, "\t$(LD) -o %s %s.o ", m->exe, m->main);

	if(m->libSepMode){
		fprintf(makefile, "-L. ");
		for(int i = 0; i < m->tlib; i++)
			fprintf(makefile, "-l%s ", m->lib[i]);
	}
	else if(m->libComMode){
		fprintf(makefile, "-L. -lmulti ");
	}
	else{
		for(int i = 0; i < m->tlib; i++)
			fprintf(makefile, "%s.o ", m->lib[i]);
	}

	if(m->gtkMode)
		fprintf(makefile, "$(GTKFLAGS)");
	fprintf(makefile, "\n\n");
	fprintf(makefile, "%s.o:%s.c\n", m->main, m->main);
	fprintf(makefile, "\t$(CC) -c %s.c -o %s.o $(CFLAGS) ", m->main, m->main);
	if(m->gtkMode)
		fprintf(makefile, "$(GTKFLAGS)");
	fprintf(makefile, "\n\n");

	if(!m->libComMode && !m->libSepMode){
		for(int i = 0; i < m->tlib; i++){
			fprintf(makefile, "%s.o: %s.h %s.c\n", m->lib[i], m->lib[i], m->lib[i]);
			fprintf(makefile, "\t$(CC) -c %s.c -o %s.o $(CFLAGS) ", m->lib[i], m->lib[i]);
			if(m->gtkMode)
				fprintf(makefile, "$(GTKFLAGS)");
			fprintf(makefile, "\n\n");
		}
	}
	else{
		fprintf(makefile, "lib: \n");
		if(m->libSepMode){
			for(int i = 0; i < m->tlib; i++){
				fprintf(makefile, "\t$(CC) -c %s.c -o %s.o $(GTKFLAGS)\n", m->lib[i], m->lib[i]);
				fprintf(makefile, "\tar ruv lib%s.a %s.o\n", m->lib[i], m->lib[i]);
				fprintf(makefile, "\tranlib lib%s.a\n\n", m->lib[i]);
			}
			fprintf(makefile, "\n\n");;
		}else if(m->libComMode){
			for(int i = 0; i < m->tlib; i++)
				fprintf(makefile, "\t$(CC) -c %s.c -o %s.o $(GTKFLAGS)\n", m->lib[i], m->lib[i]);
			fprintf(makefile, "\tar ruv libmulti.a ");
			for(int i = 0; i < m->tlib; i++)
				fprintf(makefile, "%s.o ", m->lib[i]);
			fprintf(makefile, "\n\tranlib libmulti.a\n\n");
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
			fprintf(makefile, ":\n\t(cd ");
			for(j = savePos; m->child[j] != ';'; j++){
				fprintf(makefile, "%c", m->child[j]);
			}
			fprintf(makefile, " ;MAKE)\n");

			
		}
	}

	if(m->openAppMode){
		fprintf(makefile, "open:\n");
		#ifdef __APPLE__
		fprintf(makefile, "\topen -a %s ", m->app);
		#else
		fprintf(makefile, "\t%s ", m->app);
		#endif
		for(int i = 0; i < m->tlib; i++){
			fprintf(makefile, "%s.c %s.h ", m->lib[i], m->lib[i]);
		}
		fprintf(makefile, "%s.c ", m->main);
		#ifdef __linux__
		fprintf(makefile, "&\n");
		#endif
		fprintf(makefile, "\n\n");
	}

	if(m->compressedMode){
		fprintf(makefile, "tar:\n");
		fprintf(makefile, "\ttar -czf %s.tar.gz ", m->exe);
		
		for(int i = 0; i < m->tlib; i++)
			fprintf(makefile, "%s.c %s.h ", m->lib[i], m->lib[i]);

		fprintf(makefile, "%s.c Makefile\n", m->main);
		fprintf(makefile, "\n\n");
	}
	fprintf(makefile, "clean:\n");
	fprintf(makefile, "\trm -f *.o\n\trm -f %s", m->exe);

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

static int exist_files(Modele_t *m){

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









