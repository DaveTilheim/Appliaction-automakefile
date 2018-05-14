/**
@file window-amf.h
@author Arthur Detrembleur (Appliaction [DaveTilheim])
@version 1.0
*/
#ifndef __WIN_AMF__
#define __WIN_AMF__

/**
@fn void print_help_mode(GtkWidget *widget, gpointer pData)
@brief print a window who describes all the differents mode of the program
@param widget unused
@param pData unused
@post window printed
*/ 
void print_help_mode(GtkWidget *widget, gpointer pData);

/**
@fn GtkWidget *create_window(void)
@brief create a basic window
@post window created
@return a GtkWidget
*/ 
GtkWidget *create_window(void);

/**
@fn GtkWidget *create_menu(GtkWidget *window, Controleur_t *c)
@brief create a menu
@param window the main window
@param c the controler
@post menu created
@return a GtkWidget
*/ 
GtkWidget *create_menu(GtkWidget *window, Controleur_t *c);


/**
@fn void destroy_mvc(Modele_t *m, Vue_t *v, Controleur_t *c)
@brief free MVC
@param m a Modele_t pointer
@param v a Vue_t pointer
@param c a Controleur_t pointer
@pre m != NULL, v != NULL, c != NULL
@post MVC desallocated
*/
void destroy_mvc(Modele_t *m, Vue_t *v, Controleur_t *c);

/**
@fn void print_information(GtkWidget *widget, gpointer pData)
@brief print a window wich contains information about the app
@param widget unused
@param pData unused
@post window printed
*/
void print_information(GtkWidget *widget, gpointer pData);

/**
@fn void print_help_editor(GtkWidget *widget, gpointer pData)
@brief print a window wich contains information about the editor mf
@param widget unused
@param pData unused
@post window printed
*/
void print_help_editor(GtkWidget *widget, gpointer pData);

/**
@fn int auto_makefile_main_program(void);
@brief main program
*/

#endif
