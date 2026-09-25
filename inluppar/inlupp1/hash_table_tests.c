#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdbool.h>
#include "hash_table_iterator.h"




void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
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

void test_remove_once(){
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key1 = "abc";
  int value1 = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key1, &result));
  CU_ASSERT_EQUAL(result, 0);

   // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key1, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key1, &result));
  CU_ASSERT_EQUAL(result, value1);

  char* key2 = "def";
  int value2 = 456;

  //insert key2 and check result
  ioopm_hash_table_insert(ht, key2, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key2, &result));
  CU_ASSERT_EQUAL(result, value2);
  

  //remove key1 and shearch for key1
  ioopm_hash_table_remove(ht,key1,&result);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht,key1, &result));

  //check key2 still correct
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht,key2, &result));
  CU_ASSERT_EQUAL(result, value2);


  //destroy hash table
  ioopm_hash_table_destroy(ht);

}


void test_has_key_insert_two(){
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  char* key2 = "goodbye";
  //int value2 = 69;

  //ingen key "hello"
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,key1));

  //inserta key och value och kolla så nyckel finns. 
  ioopm_hash_table_insert(ht,key1,value1);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,key2));
  
  ioopm_hash_table_destroy(ht);
}

void test_has_three_keys(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  char* key2 = "goodbye";
  int value2 = 69;

  char* key3 = "hello again";
  int value3 = 6767;

  char* fake_key = "foo";

  //insert key and value 1-3
  ioopm_hash_table_insert(ht,key1,value1);
  ioopm_hash_table_insert(ht,key2,value2);
  ioopm_hash_table_insert(ht,key3,value3);

  //look for key 1-3 and check fake key is not true
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,fake_key));

  ioopm_hash_table_destroy(ht);
}

void test_insert_remove_key(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;
  int result;

  ioopm_hash_table_insert(ht,key1,value1);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));


  //remove key1 and check its removed successfully
  ioopm_hash_table_remove(ht,key1,&result);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,key1));

  ioopm_hash_table_destroy(ht);
}

void test_add_3_keys_remove_2nd(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  char* key2 = "goodbye";
  int value2 = 69;

  char* key3 = "hello again";
  int value3 = 6767;

  int result;

  //insert key and value 1-3
  ioopm_hash_table_insert(ht,key1,value1);
  ioopm_hash_table_insert(ht,key2,value2);
  ioopm_hash_table_insert(ht,key3,value3);

  ioopm_hash_table_remove(ht,key2,&result);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key3));

  ioopm_hash_table_destroy(ht);
}

void test_size_zero_ht(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht),0);

   ioopm_hash_table_destroy(ht);
}

void test_single_element_size(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  ioopm_hash_table_insert(ht,key1,value1);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht),1);

   ioopm_hash_table_destroy(ht);
}

void test_size_big(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  char* key2 = "goodbye";
  int value2 = 69;

  char* key3 = "hello again";
  int value3 = 6767;


  //insert key and value 1-3
  ioopm_hash_table_insert(ht,key1,value1);
  ioopm_hash_table_insert(ht,key2,value2);
  ioopm_hash_table_insert(ht,key3,value3);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key3));

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht),3);

  ioopm_hash_table_destroy(ht);
}

void test_size_remove_element(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;

  char* key2 = "goodbye";
  int value2 = 69;

  char* key3 = "hello again";
  int value3 = 6767;

  int result;

  //insert key and value 1-3
  ioopm_hash_table_insert(ht,key1,value1);
  ioopm_hash_table_insert(ht,key2,value2);
  ioopm_hash_table_insert(ht,key3,value3);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,key3));

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht),3);

  ioopm_hash_table_remove(ht,key2,&result);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht),2);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_empty_false(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;
  ioopm_hash_table_insert(ht,key1,value1);

  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);

}

void test_hash_table_empty_true(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  ioopm_hash_table_destroy(ht);
}

void test_iterator_at_end_empty(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_one_element(){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "hello";
  int value1 = 67;
  ioopm_hash_table_insert(ht,key1,value1);

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  //ioopm_hash_table_iterator_advance(it);

  CU_ASSERT_EQUAL(strcmp(ioopm_hash_table_iterator_current_key(it),key1),0);
  CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it),value1);

  ioopm_hash_table_iterator_advance(it);

  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  CU_ASSERT_EQUAL(iteration_count, 3);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_visited_once()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;
  int key_1_count = 0;
  int key_2_count = 0;
  int key_3_count = 0;


  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
   
    if(strcmp(ioopm_hash_table_iterator_current_key(it),keys[0])==0){
        key_1_count++;
    }
    if(strcmp(ioopm_hash_table_iterator_current_key(it),keys[1])==0){
      key_2_count++;
    }
    if(strcmp(ioopm_hash_table_iterator_current_key(it),keys[2])==0){
      key_3_count++;
    }
    ioopm_hash_table_iterator_advance(it);
  }

  CU_ASSERT_EQUAL(key_1_count,1);
  CU_ASSERT_EQUAL(key_2_count,1);
  CU_ASSERT_EQUAL(key_3_count,1);
  

 
  CU_ASSERT_EQUAL(iteration_count, 3);
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_multiple_elements_in_buckets()
  {
  char *keys[18] = {
        "key0",  "key1",  "key2",  "key3",  "key4",  "key5",
        "key6",  "key7",  "key8",  "key9",  "key10", "key11",
        "key12", "key13", "key14", "key15", "key16", "key17"};

  int values[18] = {
      0, 1, 2, 3, 4, 5,
      6, 7, 8, 9, 10, 11,
      12, 13, 14, 15, 16, 17};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 18; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  CU_ASSERT_EQUAL(iteration_count,18);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}






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
void test1(void) {
  CU_ASSERT(42);
}

void test2(void) {
  CU_ASSERT_EQUAL(1 + 1, 2);
}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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
    (CU_add_test(my_test_suite, "create + destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "insert once", test_insert_once) == NULL) || 
    (CU_add_test(my_test_suite, "insert + remove element", test_remove_once) == NULL) ||
    (CU_add_test(my_test_suite, "has key, insert two", test_has_key_insert_two) == NULL) ||
    (CU_add_test(my_test_suite, "add 3 keys, rem 2nd", test_add_3_keys_remove_2nd) == NULL) ||
    (CU_add_test(my_test_suite, "insert + remove, has key", test_insert_remove_key) == NULL) ||
    (CU_add_test(my_test_suite, "has 3 keys", test_has_three_keys) == NULL) ||
    (CU_add_test(my_test_suite, "size big", test_size_big) == NULL) ||
    (CU_add_test(my_test_suite, "size zero", test_size_zero_ht) == NULL) ||
    (CU_add_test(my_test_suite, "size 1", test_single_element_size) == NULL) ||
    (CU_add_test(my_test_suite, "size remove element", test_size_remove_element) == NULL) ||
    (CU_add_test(my_test_suite, "is empty false", test_hash_table_empty_false) == NULL) ||
    (CU_add_test(my_test_suite, "is empty true", test_hash_table_empty_true) == NULL) ||
    (CU_add_test(my_test_suite, "one element iterator", test_iterator_one_element) == NULL) ||
    (CU_add_test(my_test_suite, "iterator at end empty", test_iterator_at_end_empty) == NULL) ||
    (CU_add_test(my_test_suite, "iterator several entries", test_iterator_several_entries) == NULL) ||
    (CU_add_test(my_test_suite, "iterator visited once", test_iterator_visited_once) == NULL) ||
    (CU_add_test(my_test_suite, "iterator, multiple elim/bucket", test_iterator_multiple_elements_in_buckets) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_NORMAL);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
