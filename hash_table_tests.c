#include <CUnit/Basic.h>
#include "hash_table.h"


int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_look_up_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  ioopm_hash_table_destroy(ht);
}


void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_insert_update()
{
    // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value1 = 123;
  int value2 = 456;
  int result = 0;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value1);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value2);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int res = 0;
  // insert key-value pair and check that the mapping exists
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &res));


  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_existing()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int res_lookup = 0;
  int res_remove = 0;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &res_lookup));
  CU_ASSERT_EQUAL(res_lookup, value);

  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &res_remove));
  CU_ASSERT_EQUAL(res_remove, value);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &res_lookup));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_non_existing()
{

}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite hash_suite = CU_add_suite("Suite to test hash tables", init_suite, clean_suite);
  if (hash_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(hash_suite, "Create & destroy", test_create_destroy) == NULL) ||
    (CU_add_test(hash_suite, "Look up key in empty ht", test_look_up_empty) == NULL) ||
    (CU_add_test(hash_suite, "Insert in ht", test_insert_once) == NULL) ||
    (CU_add_test(hash_suite, "Update existing key", test_insert_update) == NULL) ||
    (CU_add_test(hash_suite, "Remove key from empty ht", test_remove_empty) == NULL) ||
    (CU_add_test(hash_suite, "Remove existing key from ht", test_remove_existing) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 