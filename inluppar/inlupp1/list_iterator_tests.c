#include <CUnit/Basic.h>
#include "list_iterator.h"
#include "linked_list.h"


void test_create_and_destroy(){
  ioopm_list_t *l =ioopm_list_create();
  ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);
  ioopm_list_iterator_destroy(it);
  ioopm_list_destroy(l);

}

void test_advance_and_current(){
  ioopm_list_t *l =ioopm_list_create();
  for (int i = 0; i != 4; i++)
  {
    ioopm_list_append(l, i);
  }

  ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);
  //ioopm_list_iterator_advance(it);
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(it),0);

  ioopm_list_iterator_advance(it);
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(it),1);

  ioopm_list_iterator_advance(it);
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(it),2);

  ioopm_list_iterator_destroy(it);
  ioopm_list_destroy(l);


}

void test_at_end(){
  ioopm_list_t *l =ioopm_list_create();
  for (int i = 0; i != 100; i++)
  {
    ioopm_list_append(l, i);
  }
  ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);
  int count=0;

  while(!ioopm_list_iterator_at_end(it)){
    ioopm_list_iterator_advance(it);
    count++;
  }
  
  //printf("count är %d\n",count);
  CU_ASSERT_EQUAL(count,100);

  ioopm_list_iterator_destroy(it);
  ioopm_list_destroy(l);

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
    (CU_add_test(my_test_suite, "create and destroy", test_create_and_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "advannce and current", test_advance_and_current) == NULL) ||
    (CU_add_test(my_test_suite, "test at end bool", test_at_end) == NULL) ||

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
