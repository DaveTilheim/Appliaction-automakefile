/**
@file main.c
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdarg.h>
#include <assert.h>
#include "vue.h"
#include "controleur.h"
#include "modele.h"

/**
@fn static void print_help(GtkWidget *widget, gpointer pData)
@brief print a window who describes all the differents mode of the program
@param widget unused
@param pData unused
@post window printed
*/
static void print_help(GtkWidget *widget, gpointer pData);

/**
@fn static GtkWidget *create_window(void)
@brief create a basic window
@post window created
@return a GtkWidget
*/
static GtkWidget *create_window(void);

/**
@fn static GtkWidget *create_menu(GtkWidget *window, Controleur_t *c)
@brief create a menu
@param window the main window
@param c the controler
@post menu created
@return a GtkWidget
*/
static GtkWidget *create_menu(GtkWidget *window, Controleur_t *c);

/**
@fn void fill_box(GtkWidget *box, int Nwg, ...)
@brief fill a box with widgets
@param box a GtkWidget
@param Nwg the number of widgets to fill in box
@param ... the widgets
@post box fills
*/
void fill_box(GtkWidget *box, int Nwg, ...);

static void destruction_mvc(Modele_t *m, Vue_t *v, Controleur_t *c);


int main(int argc, char **argv){
	//#undef __APPLE__
	//to test the linux edition on mac
	#ifdef _WIN32
	fprintf(stderr, "WARNING [auto-makefile works only on Mac and Linux]\n");
	return -1;
	#endif

	gtk_init(&argc, &argv);

	Modele_t *m = creer_modele();
	if(!m){
		fprintf(stderr, "ERROR\n");
		return -1;
	}
	Vue_t *v = creer_vue(m);
	if(!v){
		fprintf(stderr, "ERROR\n");
		destroy_modele(m);
		return -1;
	}
	Controleur_t *c = creer_controleur(v, m);
	if(!c){
		fprintf(stderr, "ERROR\n");
		destroy_modele(m);
		destroy_vue(v);
		return -1;
	}

	v->window = create_window();
	gtk_window_set_default_size(GTK_WINDOW(v->window), 800, 800);
	v->boxAll = gtk_vbox_new(FALSE, 5);
	GtkWidget *menu = create_menu(v->window, c);
	fill_box(v->boxWidget[0], 2, v->labelEntryExeName, c->entryExeName);
	fill_box(v->boxWidget[1], 2, v->labelEntryNLib, c->spinButtonNLib);
	fill_box(v->boxWidget[3], 2, v->labelEntryMainName, c->entryMainName);
	fill_box(v->vboxWidget, 14, v->boxWidget[0], v->boxWidget[1], v->boxWidget[3],c->checkButtonGtkMode, c->checkButtonLibSeparateMode, 
		c->checkButtonLibCommuneMode, c->checkButtonCheckFileMode,c->checkButtonCompressed, c->checkButtonCustomCflagsMode, c->entryCflags,
		c->checkButtonChildMode, c->entryChild, c->checkButtonOpenWithApp, c->entryOpenApp);
	fill_box(v->hboxWidget,2, v->vboxWidget, v->boxWidget[2]);
	fill_box(v->boxAll, 5, menu, v->hboxWidget, c->buttonConfirm, c->buttonRapport, v->labelWarning);

	gtk_container_add(GTK_CONTAINER(v->window), v->boxAll);

	gtk_widget_show_all(v->window);

	gtk_widget_hide(c->entryOpenApp);
	gtk_widget_hide(c->entryCflags);
	gtk_widget_hide(c->entryChild);

	g_signal_connect(G_OBJECT(c->spinButtonNLib), "value-changed", G_CALLBACK(spin_add_library_entry), c);
	g_signal_connect(G_OBJECT(c->buttonConfirm), "clicked", G_CALLBACK(make_makefile), c);
	g_signal_connect(G_OBJECT(c->checkButtonGtkMode), "clicked", G_CALLBACK(gtk_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonLibSeparateMode), "clicked", G_CALLBACK(libs_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonLibCommuneMode), "clicked", G_CALLBACK(libc_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonCheckFileMode), "clicked", G_CALLBACK(checkf_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonOpenWithApp), "clicked", G_CALLBACK(open_app_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonCompressed), "clicked", G_CALLBACK(compressed_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonCustomCflagsMode), "clicked", G_CALLBACK(custom_cflags_mode), c);
	g_signal_connect(G_OBJECT(c->checkButtonChildMode), "clicked", G_CALLBACK(child_mode), c);
	g_signal_connect(G_OBJECT(c->buttonRapport), "clicked", G_CALLBACK(create_rapport), c);

	#ifdef __APPLE__
	printf("\n[Auto Makefile mac edition is running]\n");
	#else
	printf("\n[Auto Makefile linux edition is running]\n");
	#endif

	gtk_main();

	destruction_mvc(m, v, c);

	#ifdef __APPLE__
	printf("\n[Auto Makefile mac edition is closed]\n\n");
	#else
	printf("\n[Auto Makefile linux edition is closed]\n\n");
	#endif

	return 0;
}


static GtkWidget *create_window(void){

	GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Auto Makefile");
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy_fenetre), NULL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	
	return window;
}

void fill_box(GtkWidget *box, int Nwg, ...){

	assert(box != NULL && Nwg > 0);

	va_list list_;
	va_start(list_, Nwg);

	for(int i = 0; i < Nwg; i++)
		gtk_box_pack_start(GTK_BOX(box), va_arg(list_, GtkWidget*), TRUE, TRUE, 0);

	va_end(list_);

}

static void affiche_a_porpos(GtkWidget *widget, gpointer pData){

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

static void print_help(GtkWidget *widget, gpointer pData){

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

static GtkWidget *create_menu(GtkWidget *window, Controleur_t *c){

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


 	gtk_widget_add_accelerator(item_quitter, "activate", accelerateur, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_a_propos, "activate", accelerateur, GDK_i, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 	gtk_widget_add_accelerator(item_mode, "activate", accelerateur, GDK_m, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
 

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_gtkMakefile), menu_gtkMakefile);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_help), menu_help);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_quitter);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_gtkMakefile), item_a_propos);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_help), item_mode);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_gtkMakefile);
	gtk_menu_shell_append(GTK_MENU_SHELL(barre_menu), item_help);
	

	g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(destroy_fenetre), NULL);
	g_signal_connect(G_OBJECT(item_a_propos), "activate", G_CALLBACK(affiche_a_porpos), NULL);
	g_signal_connect(G_OBJECT(item_mode), "activate", G_CALLBACK(print_help), NULL);

	
	return barre_menu;
}



static void destruction_mvc(Modele_t *m, Vue_t *v, Controleur_t *c){

	assert(m != NULL && v != NULL && c != NULL);
	
	destroy_controleur(c);
	destroy_vue(v);
	destroy_modele(m);
}

