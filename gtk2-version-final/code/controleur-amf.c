/**
@file controleur-amf.c
@brief contains the C code about the controleur of the app
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "modele-amf.h"
#include "vue-amf.h"
#include "controleur-amf.h"
#include "list.h"
#include "util-gtk.h"



Controleur_t *creer_controleur(Vue_t *v, Modele_t *m){

	assert(v != NULL && m != NULL);

	Controleur_t *c = malloc(sizeof(Controleur_t));
	if(c == NULL)
		return NULL;
	c->m = m;
	c->v = v;
	c->spinButtonNLib = gtk_hscale_new_with_range(0.0, MAX_LIB, 1.0);
    gtk_scale_set_draw_value(GTK_SCALE(c->spinButtonNLib), TRUE);
	c->entryExeName = gtk_entry_new_with_max_length(20);
	c->entryLibName = empty_list();
	c->entryMainName = gtk_entry_new_with_max_length(20);
	c->checkButtonGtkMode = gtk_check_button_new_with_label("Gtk+2");
	c->checkButtonLibSeparateMode = gtk_check_button_new_with_label("Separates libs");
	c->checkButtonLibCommuneMode = gtk_check_button_new_with_label("Commune lib");
	c->checkButtonCheckFileMode = gtk_check_button_new_with_label("Check files");
	c->checkButtonOpenWithApp = gtk_check_button_new_with_label("Open with app");
	c->entryOpenApp = gtk_entry_new_with_max_length(20);
	c->buttonConfirm = gtk_button_new_with_label("MAKE");
	c->checkButtonCompressed = gtk_check_button_new_with_label("Compress project");
	c->checkButtonCustomCflagsMode = gtk_check_button_new_with_label("Custom CFLAGS");
	c->entryCflags = gtk_entry_new_with_max_length(MAXC_CFLAGS);
	c->checkButtonChildMode = gtk_check_button_new_with_label("Children");
	c->entryChild = gtk_entry_new_with_max_length(MAXC_CHILD);
	c->buttonRapport = gtk_button_new_with_label("create rapport");
	gtk_widget_set_sensitive(c->buttonRapport, FALSE);
	c->checkButtonGpp = gtk_check_button_new_with_label("g++ compiler (default gcc)");
	c->checkButtonGtk3 = gtk_check_button_new_with_label("Gtk+3");

	return c;
}

void destroy_controleur(Controleur_t *c){

	assert(c != NULL);

	c->entryLibName = remove_list(c->entryLibName);
	free(c);
}

void spin_add_library_entry(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);

	Controleur_t *c = (Controleur_t *) pData;

	const int nLib = (int) gtk_range_get_value(GTK_RANGE(widget));

	while(nLib < length_list(c->entryLibName)){
		c->entryLibName = remove_first_element(c->entryLibName);
		spin_sub_library_label(c->v);
		spin_sub_library_hbox(c->v);
	}
	while(nLib > length_list(c->entryLibName)){
		c->entryLibName = add_first(c->entryLibName, gtk_entry_new_with_max_length(20));
		spin_add_library_label(c->v);
		spin_add_library_hbox(c->v);
		GtkWidget *tmpBox = (GtkWidget *) get_element(c->v->boxLib, 0);
		GtkWidget *tmpLabel = (GtkWidget *) get_element(c->v->labelEntryNameLib, 0);
		GtkWidget *tmpEntry = (GtkWidget *) get_element(c->entryLibName, 0);
		fill_box(tmpBox, 2, tmpLabel, tmpEntry);
		box_in_window_and_show(c->v);
	}
	if(c->m->openAppMode)
		gtk_widget_show(c->entryOpenApp);
	else
		gtk_widget_hide(c->entryOpenApp);

	if(c->m->customCflagsMode)
		gtk_widget_show(c->entryCflags);
	else
		gtk_widget_hide(c->entryCflags);

	if(c->m->childMode)
		gtk_widget_show(c->entryChild);
	else
		gtk_widget_hide(c->entryChild);
	

}



void destroy_fenetre(GtkWidget *widget, gpointer pData){

	gtk_main_quit();
}

/**
@fn static int check_entry_space(char *entryText)
@brief check spaces in an entry
@param entryText a text of an entry
@pre entryText != NULL
@post spaces verified
@return 1 no spaces   0 spaces detected
*/
static int check_entry_space(char *entryText);

static int check_entry_space(char *entryText){

	assert(entryText != NULL);

	if(!strlen(entryText))
		return 0;

	for(int i = 0; i < strlen(entryText); i++)
		if(entryText[i] == ' ')
			return 0;

	return 1;
}

/**
@fn static int check_entry_empty(Controleur_t *c)
@brief check if an entry is empty
@param c the controleur of the app
@pre c != NULL
@post entry verified
@return 1 empty entry   0 not empty entry
*/
static int check_entry_empty(Controleur_t *c);

static int check_entry_empty(Controleur_t *c){

	assert(c != NULL);

	if(!check_entry_space((char *)gtk_entry_get_text(GTK_ENTRY(c->entryExeName))))
		return 1;
	if(!check_entry_space((char *)gtk_entry_get_text(GTK_ENTRY(c->entryMainName))))
		return 1;
	if(!strlen((char *)gtk_entry_get_text(GTK_ENTRY(c->entryOpenApp))) && c->m->openAppMode)
		return 1;
	if(!strlen((char *)gtk_entry_get_text(GTK_ENTRY(c->entryCflags))) && c->m->customCflagsMode)
		return 1;
	if(!check_entry_space((char *)gtk_entry_get_text(GTK_ENTRY(c->entryChild))) && c->m->childMode)
		return 1;
	for(int i = 0; i < length_list(c->entryLibName); i++)
		if(!check_entry_space((char *)gtk_entry_get_text(GTK_ENTRY((GtkWidget *)get_element(c->entryLibName, i)))))
			return 1;
	return 0;
}

void create_rapport(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);

	Controleur_t *c =(Controleur_t *) pData;
	make_rapport(c->m);
	gtk_label_set_text(GTK_LABEL(c->v->labelWarning), g_locale_to_utf8("<b>[rapport created]</b>", -1, NULL, NULL, NULL));
	gtk_label_set_use_markup(GTK_LABEL(c->v->labelWarning), TRUE);
	gtk_widget_set_sensitive(c->buttonRapport, FALSE);
}

void make_makefile(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);

	Controleur_t *c = (Controleur_t *) pData;
	if(check_entry_empty(c)){
		gtk_label_set_text(GTK_LABEL(c->v->labelWarning), g_locale_to_utf8("<b>[empty entry or '.' or spaces detected]</b>", -1, NULL, NULL, NULL));
		gtk_label_set_use_markup(GTK_LABEL(c->v->labelWarning), TRUE);
		return;
	}

	if(c->m->openAppMode)
		strcpy(c->m->app, (char *) gtk_entry_get_text(GTK_ENTRY(c->entryOpenApp)));
	if(c->m->customCflagsMode)
		strcpy(c->m->cflags, (char *) gtk_entry_get_text(GTK_ENTRY(c->entryCflags)));
	if(c->m->childMode)
		strcpy(c->m->child, (char *) gtk_entry_get_text(GTK_ENTRY(c->entryChild)));
	
	if(!run(c->m, c->entryExeName, c->entryMainName, c->entryLibName, c->entryOpenApp)){
		gtk_label_set_text(GTK_LABEL(c->v->labelWarning), g_locale_to_utf8("<b>[file not found]</b>", -1, NULL, NULL, NULL));
		gtk_label_set_use_markup(GTK_LABEL(c->v->labelWarning), TRUE);
		return;
	}

	gtk_label_set_text(GTK_LABEL(c->v->labelWarning), g_locale_to_utf8("<b> [makefile created on the current directory] </b>", -1, NULL, NULL, NULL));
	gtk_label_set_use_markup(GTK_LABEL(c->v->labelWarning), TRUE); 
	gtk_widget_set_sensitive(c->buttonRapport, TRUE);
}

void gtk_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 1);
	if(c->m->gtkMode)
		gtk_widget_set_sensitive(c->checkButtonGtk3, FALSE);
	else
		gtk_widget_set_sensitive(c->checkButtonGtk3, TRUE);
}

void libs_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	
	active_mode(c->m, 2);
	if(c->m->libSepMode)
		gtk_widget_set_sensitive(c->checkButtonLibCommuneMode, FALSE);
	else
		gtk_widget_set_sensitive(c->checkButtonLibCommuneMode, TRUE);
}

void libc_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 3);
	if(c->m->libComMode)
		gtk_widget_set_sensitive(c->checkButtonLibSeparateMode, FALSE);
	else
		gtk_widget_set_sensitive(c->checkButtonLibSeparateMode, TRUE);
}

void checkf_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 4);
}

void open_app_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 5);
	if(c->m->openAppMode)
		gtk_widget_show(c->entryOpenApp);
	else
		gtk_widget_hide(c->entryOpenApp);
}

void compressed_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 6);
}

void custom_cflags_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 7);
	if(c->m->customCflagsMode)
		gtk_widget_show(c->entryCflags);
	else
		gtk_widget_hide(c->entryCflags);
}

void child_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);
	
	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 8);
	if(c->m->childMode)
		gtk_widget_show(c->entryChild);
	else
		gtk_widget_hide(c->entryChild);
}

void gtk3_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);

	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 9);
	if(c->m->gtk3Mode)
		gtk_widget_set_sensitive(c->checkButtonGtkMode, FALSE);
	else
		gtk_widget_set_sensitive(c->checkButtonGtkMode, TRUE);
}

void gpp_mode(GtkWidget *widget, gpointer pData){

	assert(pData != NULL);

	Controleur_t *c = (Controleur_t *) pData;
	active_mode(c->m, 10);
}


