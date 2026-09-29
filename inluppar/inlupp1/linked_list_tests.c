#include <CUnit/Basic.h>
#include "linked_list.h"
#include "list_iterator.h"


void test_create_and_destroy_ll(){
    ioopm_list_t *ll = ioopm_list_create();
    ioopm_list_destroy(ll);
}

void test_append_once(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  CU_ASSERT_EQUAL(ioopm_list_last(ll),67);

  ioopm_list_destroy(ll);
}

void test_append_multiple_and_destroy(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  ioopm_list_append(ll,68);
  ioopm_list_append(ll,69);
  ioopm_list_append(ll,70);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),4);

  ioopm_list_destroy(ll);
}

void test_append_and_remove(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  CU_ASSERT_EQUAL(ioopm_list_last(ll),67);
  ioopm_list_remove(ll,0);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),0);
  CU_ASSERT_NOT_EQUAL(ioopm_list_last(ll),67); //så inte sent noden togs bort
  ioopm_list_destroy(ll);
}

void test_insert_at_last(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  ioopm_list_append(ll,68);
  ioopm_list_append(ll,69);
  ioopm_list_append(ll,70);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),4);
  
  ioopm_list_insert(ll,4,1);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),5);
  CU_ASSERT_EQUAL(ioopm_list_last(ll),1);
  ioopm_list_destroy(ll);
}

void test_insert_at_first(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  ioopm_list_append(ll,68);
  ioopm_list_append(ll,69);
  ioopm_list_append(ll,70);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),4);
  
  ioopm_list_insert(ll,0,1);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),5);
  CU_ASSERT_EQUAL(ioopm_list_head(ll),1);
  CU_ASSERT_EQUAL(ioopm_list_last(ll),70);
  ioopm_list_destroy(ll);
}

void test_insert_middle(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  ioopm_list_append(ll,68);
  ioopm_list_append(ll,69);
  ioopm_list_append(ll,70);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),4);
  
  ioopm_list_insert(ll,2,1);
  CU_ASSERT_EQUAL(ioopm_list_get(ll,2),1);
  ioopm_list_destroy(ll);
}

void test_is_emtpy_true(){
  ioopm_list_t *ll = ioopm_list_create();
  CU_ASSERT_TRUE(ioopm_list_is_empty(ll));

  ioopm_list_append(ll,67);
  ioopm_list_remove(ll,0);
  CU_ASSERT_TRUE(ioopm_list_is_empty(ll));

  ioopm_list_destroy(ll);
}

void test_is_emtpy_false(){
  ioopm_list_t *ll = ioopm_list_create();
  CU_ASSERT_TRUE(ioopm_list_is_empty(ll));

  ioopm_list_append(ll,67);
  CU_ASSERT_FALSE(ioopm_list_is_empty(ll));

  ioopm_list_remove(ll,0);
  CU_ASSERT_TRUE(ioopm_list_is_empty(ll));

  ioopm_list_destroy(ll);
}

void test_get(){
  ioopm_list_t *ll = ioopm_list_create();
  ioopm_list_append(ll,67);
  ioopm_list_append(ll,68);
  ioopm_list_append(ll,69);
  ioopm_list_append(ll,70);
  CU_ASSERT_EQUAL(ioopm_list_size(ll),4);

  CU_ASSERT_EQUAL(ioopm_list_get(ll,0),67);
  CU_ASSERT_EQUAL(ioopm_list_get(ll,1),68);
  CU_ASSERT_EQUAL(ioopm_list_get(ll,2),69);
  CU_ASSERT_EQUAL(ioopm_list_get(ll,3),70);

  ioopm_list_destroy(ll);
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
    (CU_add_test(my_test_suite, "create and destroy", test_create_and_destroy_ll) == NULL) ||
    (CU_add_test(my_test_suite, "append once", test_append_once) == NULL) ||
    (CU_add_test(my_test_suite, "append multiple and destroy", test_append_multiple_and_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "append and remove", test_append_and_remove) == NULL) ||
    (CU_add_test(my_test_suite, "insert at last", test_insert_at_last) == NULL) ||
    (CU_add_test(my_test_suite, "insert at first", test_insert_at_first) == NULL) ||
    (CU_add_test(my_test_suite, "insert at middle", test_insert_middle) == NULL) ||
    (CU_add_test(my_test_suite, "is empty true", test_is_emtpy_true) == NULL) ||
    (CU_add_test(my_test_suite, "is empty false", test_is_emtpy_false) == NULL) ||
    (CU_add_test(my_test_suite, "test for get", test_get) == NULL) ||


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
