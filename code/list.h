/**
@file list.h
@brief contains the struct List and the prototypes of list.c
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#ifndef __LIST__
#define __LIST__

/**
@struct List_t
*/
struct List_t{

	struct List_t *next; /*!< point to the next cell of the List */
	void *data; /*!< The data contain in the current cell of the list */
};

typedef struct List_t List;

/**
@fn unsigned length_list(List *L)
@brief show the length of the list
@param L a list
@post the length of L
@return a value between 0 and +inf
*/
unsigned length_list(List *L);

/**
@fn List *empty_list(void)
@brief create an empty list
@post empty list created
@return pointer null
*/
List *empty_list(void);

/**
@fn List *create_cell(void *data)
@brief create a cell
@param data a generic pointer contains generic data
@pre data != NULL
@post cell created and contains data
@return a sub-list
*/
List *create_cell(void *data);

/**
@fn List *add_first(List *L, void *data)
@brief add a cell at the begining of the list
@param L a list
@param data a generic pointer contains generic data
@pre data != NULL
@post length_list(L) + 1
@return a new list
*/
List *add_first(List *L, void *data);

/**
@fn List *add_last(List *L, void *data)
@brief add a cell at the end of the list
@param L a list
@param data a generic pointer contains generic data
@pre data != NULL
@post length_list(L) + 1
@return a new list
*/
List *add_last(List *L, void *data);

/**
@fn List *add_at(List *L, int i, void *data)
@brief add a cell at the index i of the list
@param L a list
@param i the index
@param data a generic pointer contains generic data
@pre data != NULL
@post length_list(L) + 1
@return a new list
*/
List *add_at(List *L, int i, void *data);

/**
@fn List *remove_list(List *L)
@brief remove all the cells of the list
@param L a list
@post empty_list()
@return a pointer NULL
*/
List *remove_list(List *L);

/**
@fn List *remove_first_element(List *L)
@brief remove a cell at the begining of the list
@param L a list
@post length_list(L) - 1
@return a new list
*/
List *remove_first_element(List *L);

/**
@fn void *get_element(List *L, int i)
@brief get the i element of the list
@param L a list
@param i the index
@post i element got
@return a generic pointer
*/
void *get_element(List *L, int i);

/**
@fn void set_element(List *L, int i, void *data)
@brief change the i element of the list with data
@param L a list
@param i the index
@param data the new data to put in the list
@post i element of the list changed
*/
void set_element(List *L, int i, void *data);


#endif
