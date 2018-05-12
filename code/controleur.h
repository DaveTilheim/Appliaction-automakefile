#ifndef __CONTROLEUR__
#define __CONTROLEUR__

#include <gtk/gtk.h>
#include "modele.h"
#include "vue.h"

typedef struct{

	Vue_t *v;
	Modele_t *m;
	GtkWidget *spinButtonNLib;
	GtkWidget *entryExeName;
	List *entryLibName;
	GtkWidget *entryMainName;
	GtkWidget *checkButtonGtkMode;
	GtkWidget *checkButtonLibSeparateMode;
	GtkWidget *checkButtonLibCommuneMode;
	GtkWidget *checkButtonCheckFileMode;
	GtkWidget *checkButtonOpenWithApp;
	GtkWidget *entryOpenApp;
	GtkWidget *buttonConfirm;
	GtkWidget *checkButtonCompressed;
	GtkWidget *checkButtonCustomCflagsMode;
	GtkWidget *entryCflags;

}Controleur_t;

Controleur_t *creer_controleur(Vue_t *v, Modele_t *m);

void destroy_controleur(Controleur_t *c);

void destroy_fenetre(GtkWidget *widget, gpointer pData);

void spin_add_library_entry(GtkWidget *widget, gpointer pData);

void make_makefile(GtkWidget *widget, gpointer pData);

void gtk_mode(GtkWidget *widget, gpointer pData);

void libs_mode(GtkWidget *widget, gpointer pData);

void libc_mode(GtkWidget *widget, gpointer pData);

void checkf_mode(GtkWidget *widget, gpointer pData);

void open_app_mode(GtkWidget *widget, gpointer pData);

void compressed_mode(GtkWidget *widget, gpointer pData);

void custom_cflags_mode(GtkWidget *widget, gpointer pData);






#endif
