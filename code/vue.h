#ifndef __VUE__
#define __VUE__

#include <gtk/gtk.h>
#include "modele.h"

#define N_BOX_WIDGET 7

typedef struct{

	Modele_t *m;
	GtkWidget *window;
	GtkWidget *boxAll;
	GtkWidget *hboxWidget;
	GtkWidget *vboxWidget;
	GtkWidget *boxWidget[N_BOX_WIDGET];
	List *boxLib;
	GtkWidget *labelEntryExeName;
	GtkWidget *labelEntryNLib;
	List *labelEntryNameLib;
	GtkWidget *labelEntryMainName;
	GtkWidget *labelWarning;

}Vue_t;


Vue_t *creer_vue(Modele_t *m);

void destroy_vue(Vue_t *v);

void spin_add_library_hbox(Vue_t *v);

void spin_sub_library_hbox(Vue_t *v);

void spin_add_library_label(Vue_t *v);

void spin_sub_library_label(Vue_t *v);

void box_in_window_and_show(Vue_t *v);


#endif
