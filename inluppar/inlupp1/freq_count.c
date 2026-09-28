#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"


void process_word(char *word, ioopm_hash_table_t *ht)
{
    int freq = 0;

    if (ioopm_hash_table_lookup(ht, word, &freq))
    {
        ioopm_hash_table_insert(ht, word, freq + 1);
    }
    else
    {
        ioopm_hash_table_insert(ht, strdup(word), 1);
    }
}


void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");
  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);
    if (feof(f))
    {
      free(buf);
      break;
    }
    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }
    free(buf);
  }
  fclose(f);
}

/// @brief A word together with its frequency
struct freq_word
{
  char *word;
  int freq;
};


static int cmp_freq_words(const void *p1, const void *p2)
{
  const struct freq_word *w1 = p1;
  const struct freq_word *w2 = p2;

  return w1->freq - w2->freq;
}


static int cmp_freq_words_reverse(const void *p1, const void *p2)
{
  return -cmp_freq_words(p1, p2);
}


void sort_freq_words(struct freq_word words[], size_t no_words)
{
  qsort(words, no_words, sizeof(struct freq_word), cmp_freq_words_reverse);
}


#ifndef TESTING
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s file1 ... filen", argv[0]);
    return 1;
  }

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  

  for (int i = 1; i < argc; ++i)
  {
    process_file(argv[i], ht);
  }

  int size = ioopm_hash_table_size(ht);
  struct freq_word freq_words[size];
  ioopm_hash_table_iterator_t *it=ioopm_hash_table_iterator_create(ht);

  
  // frequencies into the array above
  for(int i=0;i!=size;i++){
    freq_words[i].word=ioopm_hash_table_iterator_current_key(it);
    freq_words[i].freq=ioopm_hash_table_iterator_current_value(it);
    ioopm_hash_table_iterator_advance(it);
  }

  sort_freq_words(freq_words, size);

  for (int i = 0; i < size; ++i)
  {
    printf("%s: %d\n", freq_words[i].word, freq_words[i].freq);
  }

  
  // being allocated, and then insert code here to free it.
  //

  for(int i=0;i!=size;i++){
    free(freq_words[i].word);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}
#endif
