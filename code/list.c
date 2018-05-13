/**
@file list.c
@brief contains the C code about the data sruct 'List'
@author Arthur Detrembleur (DaveTilheim)
@version 1.0
*/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


inline List *empty_list(void){

	return NULL;
}

/**
@fn static inline int is_empty(List *L)
@brief indicates if a list is empty
@param L a list
@post list empty or not
@return 0 -> not empty list  1 -> empty list
*/
static inline int is_empty(List *L){

	return L == NULL;
}

unsigned length_list(List *L){

	List *p = L;
	if(is_empty(p))
		return 0;
	int u = 0;
	while(p != NULL){
		p = p->next;
		u++;
	}

	return u;
}

List *create_cell(void *data){

	assert(data != NULL);

	List *cell = malloc(sizeof(List));
	if(!cell)
		return empty_list();

	cell->data = data;
	cell->next = NULL;

	return cell;
}

List *add_first(List *L, void *data){

	assert(data != NULL);

	List *cell = create_cell(data);
	cell->next = L;

	return cell;
}

List *add_last(List *L, void *data){

	assert(data != NULL);

	List *p = L;
	List *cell = create_cell(data);
	while(p->next != NULL)
		p = p->next;
	p->next = cell;

	return L;
}

List *add_at(List *L, int i, void *data){

	assert(data != NULL);

	if(i >= length_list(L) || i < 0){
		printf("index to big\n");
		return NULL;
	}

	List *p_cour = L;
	List *p_avant = p_cour->next;
	List *cell = create_cell(data);
	if(!i)
		return add_first(L, data);
	for(int j = 0; j < i; j++){
		p_avant = p_cour;
		p_cour = p_cour->next;
	}
	p_avant->next = cell;
	cell->next = p_cour;

	return L;
}



List *remove_first_element(List *L){

	if(is_empty(L))
		return NULL;
	List *p = L;
	L = L->next;
	free(p);

	return L;
}

List *remove_list(List *L){

	if(is_empty(L)){
		return empty_list();
	}
	L = remove_first_element(L);

	return remove_list(L);
}


void *get_element(List *L, int i){

	if(i >= length_list(L) || i < 0){
		printf("index wrong\n");
		return NULL;
	}

	List *p = L;
	for(int j = 0; j < i; j++)
		p = p->next;

	return p->data;
}

void set_element(List *L, int i, void *data){

	assert(data != NULL);
	
	if(i >= length_list(L) || i < 0){
		printf("index wrong\n");
		return;
	}

	List *p = L;
	for(int j = 0; j < i; j++)
		p = p->next;

	p->data = data;
}




