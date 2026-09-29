#include "list_iterator.h"
#include "linked_list.h"

typedef struct list_iterator ioopm_list_iterator_t;

typedef int elem_t;
typedef struct link link_t;

struct link 
{
  elem_t element;
  link_t *next;
};

struct list_iterator
{
    ioopm_list_t *linked_list;
    link_t *current_element;
};


struct list
{
    link_t *head;  
    link_t *tail;  
    int size;     
};


ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l){
    ioopm_list_iterator_t *it = calloc(1,sizeof(ioopm_list_iterator_t));
    
    it->linked_list=l;
    it->current_element=l->head->next;
    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter){
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter){
    return iter->current_element==NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter){
    link_t *new = iter->current_element->next;
    iter->current_element=new;
}

int ioopm_list_iterator_current(ioopm_list_iterator_t *iter){
    return iter->current_element->element;
}

