#include "hash_table.h"
#define No_Buckets 17


typedef struct entry entry_t;

typedef struct hash_table_iterator ioopm_hash_table_iterator_t;

struct entry 
{
  char *key;     // holds the key
  int value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  // DODGE: hard-coding number of buckets as 17.
  // NOTE: addressing this dodge is optional.
  entry_t buckets[No_Buckets];
};

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  int current_bucket;
  entry_t *current_entry;
};

static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key){
  size_t bucket = string_knr_hash(key) % No_Buckets;
  entry_t *current = &ht->buckets[bucket]; //=ht->buckets+bucket

  while(current->next != NULL && strcmp(current->next->key, key) != 0){
    current=current->next;
  }
  return current;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
  return calloc(1, sizeof(ioopm_hash_table_t));
}

static entry_t *entry_create(char *key, int value, entry_t *next)
{
  entry_t *entry = malloc(sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;
  return entry;
}

static void *entry_destroy(entry_t *current){
  free(current);
  return NULL;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  
  
  for(int bucket = 0;bucket<No_Buckets;bucket++){
     entry_t *current = ht->buckets[bucket].next;
     
     while(current!=NULL){
      
      entry_t *next = current->next;
      entry_destroy(current);
      //free(current);
      current=next;
     }

  }

  free(ht);
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
  // look for an entry with the key we want
  entry_t *previous = find_previous_entry(ht, key);
  entry_t *current = previous->next;
  
  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (current != NULL)
  {
    *result = current->value;
    return true;
  }
  else
  {
    return false;
  }
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value) 
{
  // find previous entry, or the last entry if the key does not exist
  entry_t *previous = find_previous_entry(ht, key);

  // if the key exists, update the value, otherwise create a new entry
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL);
  }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result){
  entry_t *prev = find_previous_entry(ht,key);
  entry_t *current = prev->next;

  if(current==NULL){
      return false;
  }
  else{
      prev->next=current->next;
      *result = current->value;

      free(current);
      return true;
  } 
}


bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key){
  // look for an entry with the key we want
  entry_t *previous = find_previous_entry(ht, key);
  entry_t *current = previous->next;

  return current != NULL;
}

int bucket_size(entry_t *first){
  int count = 0;

  while(first != NULL){
    first=first->next;
    count++;
  }
  return count;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht){
  int size = 0;
  for (int i = 0; i < No_Buckets; i++) {
    size += bucket_size(ht->buckets[i].next);
  }
  return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht){
  return ioopm_hash_table_size(ht)==0;
}


static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
  // advance to the next entry in the bucket
  it->current_entry = it->current_entry->next;

  // if it was null advance to the next bucket
  if (it->current_entry == NULL)
  {
    it->current_bucket += 1;

    // if the next bucket existed, update the current entry
    if (it->current_bucket != No_Buckets)
    {
      it->current_entry = &it->ht->buckets[it->current_bucket];
     }
  }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it)
{
  while (it->current_bucket != No_Buckets &&
         it->current_entry == &it->ht->buckets[it->current_bucket])
  {
    advance_iterator_state(it); 
  }
}


ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_iterator_t *it = malloc(sizeof(ioopm_hash_table_iterator_t));
  it->ht = ht;
  it->current_bucket = 0;
  it->current_entry = &ht->buckets[0];
  skip_sentinel_nodes(it);
  return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it){
  //STUB
  free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it){
  return it->current_bucket == No_Buckets;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it){
  assert(!ioopm_hash_table_iterator_at_end(it) && "iterator at end when advancing");

  advance_iterator_state(it);
  skip_sentinel_nodes(it);

}

char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it){
  return it->current_entry->key;
}

int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it){
  return it->current_entry->value;
}

