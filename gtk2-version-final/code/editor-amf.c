/**
@file editor-amf.c
@brief contains the C code about the editor makefile
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <assert.h>
#include <string.h>
#include "editor-amf.h"
#include "util-gtk.h"

extern GtkWidget *create_window(void);

/**
@fn static void save_makefile_beta(GtkWidget *widget, gpointer pData)
@brief save a makefile
@param widget unused
@param pData text
@post makefile saved
*/
static void save_makefile_beta(GtkWidget *widget, gpointer pData){
	
	static int i = 0;
	if(i)
		return;
	GtkWidget *text_view = (GtkWidget *) pData;
	gtk_widget_set_sensitive(text_view, FALSE);
	GtkTextIter start, end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(text_view));
	gchar *text;
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	text = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
	if(!text)
		return;
	FILE *fmakefileBeta = fopen("Makefile", "a");
	fprintf(fmakefileBeta, "\n### Additional instructions\n");
	if(!fmakefileBeta)
		return;
	fprintf(fmakefileBeta, "%s\n", text);
	fclose(fmakefileBeta);
	i++;
	
}	

/**
@fn static GtkWidget *create_menu_editor_beta(GtkWidget *window)
@brief create a menu
@param window the main window
@post menu created
@return a GtkWidget
*/
static GtkWidget *create_menu_editor_beta(GtkWidget *window, GtkWidget *text){

	GtkWidget *barre_menu = gtk_menu_bar_new();
	GtkAccelGroup *accelerateur = NULL;
	accelerateur = gtk_accel_group_new();
  	gtk_window_add_accel_group(GTK_WINDOW(window),accelerateur);

  	/* sous-menus */
	GtkWidget *menu_gtkMakefile = gtk_menu_new();
	
	/* show sous-menu-items */
	GtkWidget *item_gtkMakefile = gtk_menu_item_new_with_label("Auto Makefile");
	
	/* items */
	GtkWidget *item_save = gtk_menu_item_new_with_mnemonic("_Save");


 	gtk_widget_add_accelerator(item_save, "activate", accelerateur, GDK_KEY_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

 
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_gtkMakefile), menu_gtkMakefile);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_save);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_gtkMakefile);
	g_signal_connect(G_OBJECT(item_save), "activate", G_CALLBACK(save_makefile_beta), text);
	

	return barre_menu;
	
}




void makefile_editor_beta(GtkWidget *widget, gpointer pData){

	GtkWidget *window = create_window();
	gtk_window_set_title(GTK_WINDOW(window), "Makefile Editor");
	GtkWidget *label = gtk_label_new("\t\tInsert your own instructions\t\t");
	GtkWidget *text = gtk_text_view_new();
	GtkWidget *menu = create_menu_editor_beta(window, text);
	GtkWidget *boxAll = gtk_vbox_new(FALSE, 5);
	GtkWidget *separator1 = gtk_hseparator_new();
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	fill_box(boxAll, 4, menu, label, separator1,text);
	gtk_container_add(GTK_CONTAINER(window), boxAll);
	gtk_widget_show_all(window);
	gtk_main();

}
