/**
@file util-gtk.c
@author Arthur Detrembleur (Appliaction [DaveTilheim])
@version 1.0
*/
#include <gtk/gtk.h>
#include <stdarg.h>
#include <assert.h>

void fill_box(GtkWidget *box, int Nwg, ...){

	assert(box != NULL && Nwg > 0);

	va_list list_;
	va_start(list_, Nwg);

	for(int i = 0; i < Nwg; i++)
		gtk_box_pack_start(GTK_BOX(box), va_arg(list_, GtkWidget*), TRUE, TRUE, 0);

	va_end(list_);

}
