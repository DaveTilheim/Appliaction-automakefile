/**
@file controleur.h
@brief contains the struct Controleur_t and the prototypes of controleur.c
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#ifndef __CONTROLEUR__
#define __CONTROLEUR__

#include <gtk/gtk.h>
#include "modele.h"
#include "vue.h"

/**
@struct Controleur_t
*/
typedef struct{

	Vue_t *v; /*!< the vue of the app */
	Modele_t *m; /*!< the modele of the app */
	GtkWidget *spinButtonNLib; /*!< a spin button [number of libs] */
	GtkWidget *entryExeName; /*!< an entry indicates the name of the exe of the makefile */
	List *entryLibName; /*!< a list of entry */
	GtkWidget *entryMainName; /*!< an entry indicates the name of the main of the makefile */
	GtkWidget *checkButtonGtkMode; /*!< a check button who indicates if the gtkMode is active */
	GtkWidget *checkButtonLibSeparateMode; /*!< a check button who indicates if the libSepMode is active */
	GtkWidget *checkButtonLibCommuneMode; /*!< a check button who indicates if the libComMode is active */
	GtkWidget *checkButtonCheckFileMode; /*!< a check button who indicates if the checkFileMode is active */
	GtkWidget *checkButtonOpenWithApp; /*!< a check button who indicates if the openAppMode is active */
	GtkWidget *entryOpenApp; /*!< an entry indicates the name of the open app of the makefile */
	GtkWidget *buttonConfirm; /*!< a button who makes the makefile */
	GtkWidget *checkButtonCompressed; /*!< a check button who indicates if the compressedMode is active */
	GtkWidget *checkButtonCustomCflagsMode; /*!< a check button who indicates if the customCflagsMode is active */
	GtkWidget *entryCflags; /*!< an entry indicates the cflags of the makefile */
	GtkWidget *checkButtonChildMode; /*!< a check button who indicates if the childMode is active */
	GtkWidget *entryChild; /*!< an entry indicates the name of the children of the makefile */
	GtkWidget *buttonRapport; /*!< a button who makes a rapport */

}Controleur_t;

/**
@fn Controleur_t *creer_controleur(Vue_t *v, Modele_t *m)
@brief create the controleur
@param v the vue
@param m the modele
@pre v != NULL, m != NULL
@post controleur created
@return a Controleur_t pointer
*/
Controleur_t *creer_controleur(Vue_t *v, Modele_t *m);

/**
@fn void destroy_controleur(Controleur_t *c)
@brief destroy the controleur
@param c the controleur
@param m the modele
@pre c != NULL
@post controleur destroyed
*/
void destroy_controleur(Controleur_t *c);

/**
@fn void destroy_fenetre(GtkWidget *widget, gpointer pData)
@brief destroy current window
@param widget unsused
@param pData unused
@post window destroyed
*/
void destroy_fenetre(GtkWidget *widget, gpointer pData);

/**
@fn void spin_add_library_entry(GtkWidget *widget, gpointer pData)
@brief add an entry in the vue
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post entry add
*/
void spin_add_library_entry(GtkWidget *widget, gpointer pData);

/**
@fn void make_makefile(GtkWidget *widget, gpointer pData)
@brief generate the makefile
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post makefile generated or not with error codes
*/
void make_makefile(GtkWidget *widget, gpointer pData);

/**
@fn void gtk_mode(GtkWidget *widget, gpointer pData)
@brief actives gtkMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post gtkMode activated
*/
void gtk_mode(GtkWidget *widget, gpointer pData);

/**
@fn void libs_mode(GtkWidget *widget, gpointer pData)
@brief actives libSepMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post libSepMode activated
*/
void libs_mode(GtkWidget *widget, gpointer pData);

/**
@fn void libc_mode(GtkWidget *widget, gpointer pData)
@brief actives libComMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post libComMode activated
*/
void libc_mode(GtkWidget *widget, gpointer pData);

/**
@fn void checkf_mode(GtkWidget *widget, gpointer pData)
@brief actives checkFileMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post checkFileMode activated
*/
void checkf_mode(GtkWidget *widget, gpointer pData);

/**
@fn void open_app_mode(GtkWidget *widget, gpointer pData)
@brief actives openAppMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post openAppMode activated
*/
void open_app_mode(GtkWidget *widget, gpointer pData);

/**
@fn void compressed_mode(GtkWidget *widget, gpointer pData)
@brief actives compressMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post compressMode activated
*/
void compressed_mode(GtkWidget *widget, gpointer pData);

/**
@fn void custom_flags_mode(GtkWidget *widget, gpointer pData)
@brief actives customFlagsMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post customFlagsMode activated
*/
void custom_cflags_mode(GtkWidget *widget, gpointer pData);

/**
@fn void child_mode(GtkWidget *widget, gpointer pData)
@brief actives childMode
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post childMode activated
*/
void child_mode(GtkWidget *widget, gpointer pData);

/**
@fn void create_rapport(GtkWidget *widget, gpointer pData)
@brief makes rapport
@param widget unsused
@param pData the controleur
@pre pData != NULL
@post rapport created
*/
void create_rapport(GtkWidget *widget, gpointer pData);


#endif
