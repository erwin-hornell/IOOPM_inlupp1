#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#define No_Buckets 17
typedef struct entry entry_t;

struct entry
{
  char *key;     // holds the key
  int value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  // DODGE: hard-coding number of buckets as No_Buckets.
  // NOTE: addressing this dodge is optional.
  entry_t buckets[No_Buckets];
};

static entry_t *entry_create(char *key, int value, entry_t *next)
{
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;
  return entry;
}

static entry_t *entry_destroy(entry_t *entry)
{
  entry_t *next = entry->next;
  free(entry);
  return next;
}

static void bucket_destroy(entry_t *sentinel) {
  entry_t *current = sentinel->next;
  while(current != NULL)
  {
    current = entry_destroy(current);
  }
}

ioopm_hash_table_t *ioopm_hash_table_create(void) {
 return calloc(1, sizeof(ioopm_hash_table_t));
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
 // DOGE: update as to not only handle ht of length No_Buckets 
 for(int i = 0; i < No_Buckets; i++)
 {
    bucket_destroy(&ht->buckets[i]);
 }
 free(ht);
}

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


static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
  size_t bucket = string_knr_hash(key) % No_Buckets;

  entry_t *prev = &ht->buckets[bucket];
  entry_t *current = prev->next;

  while (current != NULL && strcmp(current->key, key) != 0)
  {
    prev = current;
    current = prev->next;
  }
  return prev;
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

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
  // find previous entry, or the last entry if the key does not exist
  entry_t *prev = find_previous_entry(ht, key);

  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (prev->next != NULL)
  {
    *result = prev->next->value;
    return true;
  }
  else
  {
    return false;
  }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result)
{
  entry_t *prev = find_previous_entry(ht, key);
  if(prev->next == NULL)
  {
    return false;
  }
  else
  {
    *result = prev->next->value;
    prev->next = entry_destroy(prev->next);
    return true;
  }
}