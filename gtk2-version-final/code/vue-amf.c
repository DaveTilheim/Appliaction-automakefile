/**
@file vue-amf.c
@brief contains the C code about the vue of the app
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "vue-amf.h"
#include "modele-amf.h"
#include "controleur-amf.h"
#include "list.h"
#include "util-gtk.h"


Vue_t *creer_vue(Modele_t *m){

	assert(m != NULL);

	Vue_t *v = malloc(sizeof(Vue_t));
	if(v == NULL)
		return NULL;

	v->m = m;
	v->labelEntryExeName = gtk_label_new("Exe name: ");
	v->labelEntryNLib = gtk_label_new("Number of library: ");
	v->labelEntryNameLib = empty_list();
	v->labelEntryMainName = gtk_label_new("Main name: ");
	for(int i = 0; i < N_BOX_WIDGET; i++)
		v->boxWidget[i] = gtk_vbox_new(FALSE, 5);
	v->boxLib = empty_list();
	v->labelWarning = gtk_label_new("no error");
	gtk_label_set_text(GTK_LABEL(v->labelWarning), g_locale_to_utf8("<b>no error</b>", -1, NULL, NULL, NULL));
	gtk_label_set_use_markup(GTK_LABEL(v->labelWarning), TRUE);
	v->hboxWidget = gtk_hbox_new(FALSE, 0);
	v->vboxWidget = gtk_vbox_new(FALSE , 13);

	return v;
}

void destroy_vue(Vue_t *v){

	assert(v != NULL);

	v->labelEntryNameLib = remove_list(v->labelEntryNameLib);
	v->boxLib = remove_list(v->boxLib);
	free(v);
}

void spin_add_library_hbox(Vue_t *v){

	assert(v != NULL);
	
	v->boxLib = add_first(v->boxLib, gtk_vbox_new(FALSE, 5));
}

void spin_sub_library_hbox(Vue_t *v){

	assert(v != NULL);
	
	gtk_container_remove(GTK_CONTAINER(v->boxWidget[2]), (GtkWidget *) get_element(v->boxLib, 0));
	v->boxLib = remove_first_element(v->boxLib);
}

void spin_add_library_label(Vue_t *v){
	
	assert(v != NULL);
	
	v->labelEntryNameLib = add_first(v->labelEntryNameLib, gtk_label_new("Lib name: "));
}

void spin_sub_library_label(Vue_t *v){
	
	assert(v != NULL);
	
	v->labelEntryNameLib = remove_first_element(v->labelEntryNameLib);
}



void box_in_window_and_show(Vue_t *v){
	
	assert(v != NULL);
	
	fill_box(v->boxWidget[2], 1, (GtkWidget *) get_element(v->boxLib, 0));
	gtk_widget_show_all(v->window);
}



