/**
@file util-gtk.c
@author Arthur Detrembleur (Appliaction [DaveTilheim])
@version 1.0
*/
#include <gtk/gtk.h>
#include <stdarg.h>
#include <assert.h>
#include "util-gtk.h"

void fill_box(GtkWidget *box, int Nwg, ...){

	assert(box != NULL && Nwg > 0);

	va_list list_;
	va_start(list_, Nwg);

	for(int i = 0; i < Nwg; i++)
		gtk_box_pack_start(GTK_BOX(box), va_arg(list_, GtkWidget*), TRUE, TRUE, 0);

	va_end(list_);

}

GtkWidget *create_window_with_title(char *title){

	GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	
	return window;
}
