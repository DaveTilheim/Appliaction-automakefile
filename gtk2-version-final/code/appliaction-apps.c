/**
@file appliaction-apps.c
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
#include "window-amf.h"
#include "util-gtk.h"


int auto_makefile_main_program(void){
	
	#ifdef _WIN32
	fprintf(stderr, "WARNING [auto-makefile works only on Mac and Linux]\n");
	return -1;
	#endif
	GdkColor color;
  	gdk_color_parse ("grey", &color);
  	
	GtkWidget *labelWarn = gtk_label_new(" previous Makefile will be removed \n");
	gtk_widget_modify_fg (labelWarn, GTK_STATE_NORMAL, &color);

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
	
	v->boxAll = gtk_vbox_new(FALSE, 5);

	GtkWidget *menu = create_menu(v->window, c);

	GtkWidget *separator1 = gtk_hseparator_new();
	GtkWidget *separator2 = gtk_hseparator_new();

	fill_box(v->boxWidget[0], 2, v->labelEntryExeName, c->entryExeName);
	fill_box(v->boxWidget[1], 2, v->labelEntryNLib, c->spinButtonNLib);
	fill_box(v->boxWidget[3], 2, v->labelEntryMainName, c->entryMainName);
	fill_box(v->vboxWidget, 15, v->boxWidget[0], v->boxWidget[1], v->boxWidget[3],c->checkButtonGtkMode, c->checkButtonLibSeparateMode, 
		c->checkButtonLibCommuneMode, c->checkButtonCheckFileMode,c->checkButtonCompressed, separator1, c->checkButtonCustomCflagsMode, c->entryCflags,
		c->checkButtonChildMode, c->entryChild, c->checkButtonOpenWithApp, c->entryOpenApp);
	fill_box(v->hboxWidget,2, v->vboxWidget, v->boxWidget[2]);
	fill_box(v->boxAll, 7, menu, v->hboxWidget, c->buttonConfirm, c->buttonRapport, v->labelWarning, separator2, labelWarn);

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

	destroy_mvc(m, v, c);

	#ifdef __APPLE__
	printf("\n[Auto Makefile mac edition is closed]\n\n");
	#else
	printf("\n[Auto Makefile linux edition is closed]\n\n");
	#endif

	return 0;
}
