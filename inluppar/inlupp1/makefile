CC = gcc
CFLAGS = -Wall -Wextra -g

linked_list_tests: linked_list.c linked_list_tests.c linked_list.h 
	$(CC) $(CFLAGS) linked_list.c linked_list_tests.c -o linked_list_tests -lcunit

list_iterator_tests: linked_list.c linked_list.h list_iterator.c list_iterator.h list_iterator_tests.c
	$(CC) $(CFLAGS) linked_list.c list_iterator.c list_iterator_tests.c -o list_iterator_tests -lcunit

test: linked_list_tests list_iterator_tests
	./linked_list_tests 
	./list_iterator_tests

valgrind: linked_list_tests list_iterator_tests
	valgrind --leak-check=full ./linked_list_tests
	valgrind --leak-check=full ./list_iterator_tests
