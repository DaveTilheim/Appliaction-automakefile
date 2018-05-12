#ifndef __LIST__
#define __LIST__


struct List_t{

	struct List_t *next;
	void *data;
};

typedef struct List_t List;

unsigned length_list(List *L);

List *empty_list(void);

List *create_cell(void *data);

List *add_first(List *L, void *data);

List *add_last(List *L, void *data);

List *add_at(List *L, int i, void *data);

List *remove_list(List *L);

List *remove_first_element(List *L);

void print_list_int(List *L);

void *get_element(List *L, int i);

void set_element(List *L, int i, void *data);


#endif
