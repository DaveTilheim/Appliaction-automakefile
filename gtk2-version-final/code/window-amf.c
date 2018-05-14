/**
@file window-amf.c
@author Arthur Detrembleur (Appliaction [DaveTilheim])
@version 1.0
*/
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdarg.h>
#include <assert.h>
#include "vue-amf.h"
#include "controleur-amf.h"
#include "modele-amf.h"
#include "editor-amf.h"
#include "util-gtk.h"



GtkWidget *create_window(void){

	GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Auto Makefile");
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy_fenetre), NULL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	
	return window;
}


 void print_information(GtkWidget *widget, gpointer pData){

	GtkWidget *window = create_window();
	gtk_window_set_title(GTK_WINDOW(window), "Information");
	GtkWidget *box = gtk_vbox_new(TRUE, 5);
	#ifdef __APPLE__
	GtkWidget *label = gtk_label_new("\nAuto Makefile apple version (1.0)\nCreated by Arthur Detrembleur\nLanguage used C \nCompany Appliaction\n10/05/18");
	GtkWidget *picture = gtk_image_new_from_file("../pictures/apple.png");
	#else
	GtkWidget *label = gtk_label_new("Auto Makefile linux version\nCreated by Arthur Detrembleur\nLanguage used C \nCompany Appliaction\n10/05/18");
	GtkWidget *picture = gtk_image_new_from_file("../pictures/linux.png");
	#endif
	fill_box(box, 2, label, picture);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show_all(window);
	gtk_main();
}
 void print_help_mode(GtkWidget *widget, gpointer pData){

	GtkWidget *window = create_window();
	gtk_window_set_title(GTK_WINDOW(window), "Help (modes)");
	GtkWidget *box = gtk_vbox_new(TRUE, 5);
	gchar *txt;
	txt = g_locale_to_utf8("<b>HELP</b>", -1, NULL, NULL, NULL);
	GtkWidget *lab = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(lab), TRUE);
	txt = g_locale_to_utf8("   <b>[Gtk+2]</b> Actives GTKFLAGS (`pkg-config --cflags --libs gtk+-2.0`)   \n\n", -1, NULL, NULL, NULL);
	GtkWidget *labelGtk = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(labelGtk), TRUE);

	txt = g_locale_to_utf8("   <b>[Sep. libs]</b> Actives the possibility to create dynamics separates libs   \n\n", -1, NULL, NULL, NULL);
	GtkWidget *labelSeparatesLibs = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(labelSeparatesLibs), TRUE);

	txt = g_locale_to_utf8("   <b>[Com. lib]</b> Actives the possibility to create a dynamic commune lib composed of all the libs\n\n   ", -1, NULL, NULL, NULL);
	GtkWidget *labelCommuneLib = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(labelCommuneLib), TRUE);

	txt = g_locale_to_utf8("   <b>[Check Files]</b> Actives the verification of the existence of the differents files\n\n   ", -1, NULL, NULL, NULL);
	GtkWidget *labelCheckFiles = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(labelCheckFiles), TRUE);
	
	txt = g_locale_to_utf8("   <b>[Compr. project]</b> Actives the possibility to compress all the files with 'make tar'\n\n   ", -1, NULL, NULL, NULL);
	GtkWidget *labelCompProj = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(labelCompProj), TRUE);

	txt = g_locale_to_utf8("   <b>[Custom CFLAGS]</b> Actives the possibility to custom the cflags\ndefault cflags: --std=c99 --pedantic -Wall -W -Wmissing-prototypes   \n\n", -1, NULL, NULL, NULL);
	GtkWidget *cflags = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(cflags), TRUE);

	txt = g_locale_to_utf8("   <b>[Children]</b> Actives the possibility to indicate to the program the differents childs directories[separe with <b>';'</b>]   \n\n", -1, NULL, NULL, NULL);
	GtkWidget *child = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(child), TRUE);

	txt = g_locale_to_utf8("   <b>[Open With app]</b> Actives the possibility to open all the files with an app with 'make open'\n\n", -1, NULL, NULL, NULL);
	GtkWidget *openApp = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(openApp), TRUE);
	g_free(txt);
	
	fill_box(box, 9, lab, labelGtk, labelSeparatesLibs, labelCommuneLib, labelCheckFiles, labelCompProj, cflags, child, openApp);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show_all(window);
	gtk_main();

}

 void print_help_editor(GtkWidget *widget, gpointer pData){

 	GtkWidget *window = create_window();
 	gtk_window_set_title(GTK_WINDOW(window), "Help (editor)");
 	GtkWidget *box = gtk_vbox_new(FALSE, 5);
	gchar *txt;
	txt = g_locale_to_utf8("\n<b>HELP</b>", -1, NULL, NULL, NULL);
	GtkWidget *lab1 = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(lab1), TRUE);
	txt = g_locale_to_utf8("\n\nThanks to <b>Editor mf -> ctrl+e</b>\n", -1, NULL, NULL, NULL);
	GtkWidget *lab2 = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(lab2), TRUE);
	txt = g_locale_to_utf8("you can add your own instructions\n", -1, NULL, NULL, NULL);
	GtkWidget *lab3 = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(lab3), TRUE);
	txt = g_locale_to_utf8("  at the end of your Makefile with <b>ctrl+s</b>   \n\n", -1, NULL, NULL, NULL);
	GtkWidget *lab4 = gtk_label_new(txt);
	gtk_label_set_use_markup(GTK_LABEL(lab4), TRUE);
	g_free(txt);
	fill_box(box, 4, lab1, lab2, lab3, lab4);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show_all(window);
	gtk_main();
 }

 GtkWidget *create_menu(GtkWidget *window, Controleur_t *c){

	assert(c != NULL && window != NULL);

	GtkWidget *barre_menu = gtk_menu_bar_new();
	GtkAccelGroup *accelerateur = NULL;
	accelerateur = gtk_accel_group_new();
  	gtk_window_add_accel_group(GTK_WINDOW(window),accelerateur);

	/* sous-menus */
	GtkWidget *menu_gtkMakefile = gtk_menu_new();
	GtkWidget *menu_help = gtk_menu_new();
	/* show sous-menu-items */
	GtkWidget *item_gtkMakefile = gtk_menu_item_new_with_label("Auto Makefile");
	GtkWidget *item_help = gtk_menu_item_new_with_label("help");
	/* items */
	GtkWidget *item_quitter = gtk_menu_item_new_with_mnemonic("_Quit");
	GtkWidget *item_a_propos = gtk_menu_item_new_with_mnemonic("_Information");
	GtkWidget *item_mode = gtk_menu_item_new_with_mnemonic("_Modes");
	GtkWidget *item_edit = gtk_menu_item_new_with_mnemonic("_Edit MF");
	GtkWidget *item_edit_help = gtk_menu_item_new_with_mnemonic("_Help editor");


 	gtk_widget_add_accelerator(item_quitter, "activate", accelerateur, GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_a_propos, "activate", accelerateur, GDK_KEY_i, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_mode, "activate", accelerateur, GDK_KEY_m, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_edit, "activate", accelerateur, GDK_KEY_e, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_edit_help, "activate", accelerateur, GDK_KEY_h, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_gtkMakefile), menu_gtkMakefile);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_help), menu_help);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_edit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_a_propos);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), gtk_separator_menu_item_new());
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_quitter);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_help), item_mode);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_help), item_edit_help);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_gtkMakefile);
	gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_help);
	
	g_signal_connect(G_OBJECT(item_edit), "activate", G_CALLBACK(makefile_editor_beta), NULL);
	g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(destroy_fenetre), NULL);
	g_signal_connect(G_OBJECT(item_a_propos), "activate", G_CALLBACK(print_information), NULL);
	g_signal_connect(G_OBJECT(item_mode), "activate", G_CALLBACK(print_help_mode), NULL);
	g_signal_connect(G_OBJECT(item_edit_help), "activate", G_CALLBACK(print_help_editor), NULL);

	
	return barre_menu;
}


 void destroy_mvc(Modele_t *m, Vue_t *v, Controleur_t *c){

	assert(m != NULL && v != NULL && c != NULL);
	
	destroy_controleur(c);
	destroy_vue(v);
	destroy_modele(m);
}