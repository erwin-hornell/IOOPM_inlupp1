#pragma once
#include "hash_table.h"
#include <stdbool.h>

/// @brief Returns if a given key is in the hash table
/// @param ht hash table we check
/// @param key key to look up
/// @return true if key is present else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key);

/// @brief Checks if hash table is empty
/// @param ht hash table we check
/// @return true if hash table is empty
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief Returns size of given hash table
/// @param ht hash table we check
/// @return Size of the hash table
int ioopm_hash_table_size(ioopm_hash_table_t *ht);