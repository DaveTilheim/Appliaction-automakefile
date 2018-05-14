/**
@file main-amf.c
@author Arthur Detrembleur (Appliaction [DaveTilheim])
@version 1.0
*/
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdarg.h>
#include <assert.h>
#include "appliaction-apps.h"



int main(int argc, char **argv){
	

	gtk_init(&argc, &argv);
	
	if(auto_makefile_main_program())
		return -1;

	return 0;
}





