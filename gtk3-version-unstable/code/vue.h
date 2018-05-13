/**
@file vue.h
@brief contains the struct Vue_t and the prototypes of vue.c
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#ifndef __VUE__
#define __VUE__

#include <gtk/gtk.h>
#include "modele.h"

#define N_BOX_WIDGET 7

/**
@struct Vue_t
*/
typedef struct{

	Modele_t *m; /*!< the modele of the app */
	GtkWidget *window; /*!< the main window */
	GtkWidget *boxAll; /*!< the main box */
	GtkWidget *hboxWidget; /*!< a box contains widgets */
	GtkWidget *vboxWidget; /*!< a box contains widgets */
	GtkWidget *boxWidget[N_BOX_WIDGET]; /*!< a box contains widgets */
	List *boxLib; /*!< a list of box */
	GtkWidget *labelEntryExeName; /*!< a label indicates the entry of the exe name */
	GtkWidget *labelEntryNLib; /*!< a label indicates the entry of the number of libs */
	List *labelEntryNameLib; /*!< a list contains labels */
	GtkWidget *labelEntryMainName; /*!< a label indicates the entry of the main name */
	GtkWidget *labelWarning; /*!< a label indicates error */

}Vue_t;

/**
@fn Vue_t *creer_vue(Modele_t *m)
@brief create the vue
@param m the modele
@pre m != NULL
@post vue created
@return a Vue_t pointer
*/
Vue_t *creer_vue(Modele_t *m);

/**
@fn void destroy_vue(Vue_t *v)
@brief destroy the vue
@param v the vue of the app
@pre v != NULL
@post vue destroy
*/
void destroy_vue(Vue_t *v);

/**
@fn void spin_add_library_hbox(Vue_t *v)
@brief add an hbox to the vue
@param v the vue of the app
@pre v != NULL
@post hbox added
*/
void spin_add_library_hbox(Vue_t *v);

/**
@fn void spin_sub_library_hbox(Vue_t *v)
@brief sub an hbox to the vue
@param v the vue of the app
@pre v != NULL
@post hbox subed
*/
void spin_sub_library_hbox(Vue_t *v);

/**
@fn void spin_add_library_label(Vue_t *v)
@brief add a label to the vue
@param v the vue of the app
@pre v != NULL
@post label added
*/
void spin_add_library_label(Vue_t *v);

/**
@fn void spin_sub_library_label(Vue_t *v)
@brief sub a label to the vue
@param v the vue of the app
@pre v != NULL
@post label subed
*/
void spin_sub_library_label(Vue_t *v);

/**
@fn void box_in_window_and_show(Vue_t *v)
@brief puts widgets in the window and shows them
@param v the vue of the app
@pre v != NULL
@post widgets show
*/
void box_in_window_and_show(Vue_t *v);


#endif
