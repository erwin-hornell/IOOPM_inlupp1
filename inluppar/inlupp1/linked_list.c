#include "linked_list.h"

typedef struct list ioopm_list_t;
typedef int elem_t;
typedef struct link link_t;

struct link 
{
  elem_t element;
  link_t *next;
};

struct list
{
    link_t *head;  
    link_t *tail;  
    int size;     
};


//helper taken from https://wrigstad.com/ioopm/assignments/lists.html
link_t *link_new(elem_t element, link_t *next)
{
  link_t *result = malloc(sizeof(struct link));

  if (result)
    {
      result->element = element;
      result->next = next;
    }

  return result;
}

//helper taken from https://wrigstad.com/ioopm/assignments/lists.html
link_t *list_inner_find_previous(link_t *link, int index)
{
  link_t *cursor = link;

  for (int i = 0; i < index; ++i)
    {
      cursor = cursor->next;
    }

  return cursor;
}



ioopm_list_t *ioopm_list_create(void){
    ioopm_list_t *list = calloc(1,sizeof(ioopm_list_t));
    link_t *sentinel =  calloc(1,sizeof(link_t));
    list->head=sentinel;
    list->tail=sentinel;
    sentinel->next=NULL;
    list->size=0;

    return list;
}

void ioopm_list_destroy(ioopm_list_t *list){
    link_t *current = list->head;
    
    while(current!=NULL){
        link_t *next = current->next;
        free(current);
        current=next;
    }
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, int value){
    link_t *new = calloc(1,sizeof(link_t));
    new->element = value;
    new->next=NULL;
    
    link_t *prev = list->tail;
    prev->next = new;
    
    list->tail = new;
    list->size++;
}

void ioopm_list_prepend(ioopm_list_t *list, int value){
    int size = list->size;

    //if tom lista 
    if(size==0){
        ioopm_list_append(list,value);
    }
    //annars lägg först, byt sent nod pek
    else{
        link_t *point_new = list->head->next;
        link_t *new_next = link_new(value,point_new);
        list->head->next=new_next;
        list->size++;
    }
}

int ioopm_list_head(ioopm_list_t *list){
    return list->head->next->element;
}

int ioopm_list_last(ioopm_list_t *list){
    return list->tail->element;
}

void ioopm_list_insert(ioopm_list_t *list, int index, int value){
    //hitta platsen innan
    link_t *prev = list_inner_find_previous(list->head,index);

    //sätt in nya
    link_t *new = link_new(value,prev->next);

    if(prev->next==NULL){
        list->tail=new;
    }
    //byt pekare på föregående
    prev->next = new;
    list->size++;
}

int ioopm_list_remove(ioopm_list_t *list, int index){
    link_t *prev = list_inner_find_previous(list->head,index);
    link_t *current = prev->next;

    if(current == list->tail){
        list->tail=prev;
    }

    int value = prev->next->element;
    prev->next=current->next;

    free(current);
    list->size--;
    return value;
}

int ioopm_list_get(ioopm_list_t *list, int index){
    link_t *prev = list_inner_find_previous(list->head,index);
    return prev->next->element;
}

int ioopm_list_size(ioopm_list_t *list){
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list){
    return list->size==0;
}
