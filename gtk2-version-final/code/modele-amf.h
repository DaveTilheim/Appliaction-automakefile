/**
@file modele-amf.h
@brief contains the struct Modele_t and the prototypes of modele-amf.c
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#ifndef __MODELE__
#define __MODELE__

#define MAX_NEW_F 3
#define MAXC 20
#include "list.h"

#define MAX_LIB 50
#define MIN_LIB 0
#define MAXC_CFLAGS 50
#define MAXC_CHILD 51
#define N_MODE 8

/**
@struct Modele_t
*/
typedef struct{

	char exe[MAXC+1]; /*!< the executable of the makefile */
	char main[MAXC+1]; /*!< the main of the makefile */
	char **lib; /*!< the libs of the makefile */
	int tlib; /*!< the number of libs */
	int gtkMode; /*!< cptr who indicates if the gtkMode is active */
	int libSepMode; /*!< cptr who indicates if the libSepMode is active */
	int libComMode; /*!< cptr who indicates if the libComMode is active */
	int checkFileMode; /*!< cptr who indicates if the checkFileMode is active */
	int openAppMode; /*!< cptr who indicates if the openAppMode is active */
	char app[MAXC+1]; /*!< the name of the open app of the makefile */
	int compressedMode; /*!< cptr who indicates if the compressedMode is active */
	int customCflagsMode; /*!< cptr who indicates if the customCflagsMode is active */
	char cflags[MAXC_CFLAGS+1]; /*!< cflags of the makefile */
	int childMode; /*!< cptr who indicates if the childMode is active */
	char child[MAXC_CHILD+1]; /*!< names of the childs directories */


}Modele_t;

/**
@fn Modele_t *creer_modele(void)
@brief create the modele
@post modele created
@return a Modele_t pointer
*/
Modele_t *creer_modele(void);

/**
@fn void destroy_modele(Modele_t *m)
@brief destroy the modele
@pre m != NULL
@post modele destroy
*/
void destroy_modele(Modele_t *m);

/**
@fn void active_mode(Modele_t *m, int mode)
@brief active or disable a mode
@pre m != NULL , mode > 0 , mode <= N_MODE
@post mode actived or disabled
*/
void active_mode(Modele_t *m, int mode);

/**
@fn int run(Modele_t *m, GtkWidget *entryExeName, GtkWidget *entryMainName, List *entryLibName, GtkWidget *entryApp)
@brief set all the information in the modele and make the makefile
@param m the modele
@param entryExeName the name of the exe of the makefile
@param entryMainName the name of the main of the makefile
@param entryLibName a list contains the name of the libs of the makefile
@param entryApp the name of the open app of the makefile
@pre m != NULL, entryExeName != NULL, entryMainName != NULL, entryApp != NULL
@post run success or not
@return 1 success    0 fail
*/
int run(Modele_t *m, GtkWidget *entryExeName, GtkWidget *entryMainName, List *entryLibName, GtkWidget *entryApp);

/**
@fn void make_rapport(Modele_t *m)
@brief creates a rapport about the makefile creation 
@pre m != NULL
@post rapport makes
*/
void make_rapport(Modele_t *m);


#endif
