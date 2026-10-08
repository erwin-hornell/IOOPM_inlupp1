## Inlupp 1

Inlupp 1 is a C library created as part of the course Imperativ och objektorienterad programmeringsmetodik (1DL221), HT2026.

# The project contains:

A general hash table implementation supporting arbitrary key and value types through a value_t union with its own iterator.

A doubly linked list implementation with an iterator.

Unit tests for the hash table and linked list using CUnit.

freq-count, a small program that reads a text file and counts the frequency of each word using the hash table.

# Requirements

The project requires:

* GCC
* Make
* CUnit
* Valgrind (for memory checking)
* gcovr (for coverage)
* gprof (for profiling)

# Running
Hash table tests

Run the hash table test suite with:
```bash
make test-hash
```
Linked list tests

Run the linked list test suite with:

```bash
make test-list
```


Valgrind

To run the hash table tests with Valgrind:

```bash
make valgrind-hash
```


To run the linked list tests with Valgrind:

```bash
make valgrind-list
```

Code coverage

To generate coverage information for the hash table:

```bash
make coverage-hash
```

For the linked list:

```bash
make coverage-list
```

Or for both:

```bash
make coverage
```

freq-count

freq-count reads a text file and counts how frequently each word occurs using the hash table.

To run it:

```bash
make freq FILE=example.txt
```


Timing

To measure the execution time:

```bash
make freq-time FILE=example.txt
```

Profiling with gprof

To compile freq-count with profiling enabled, run it, and generate a profiling report:

```bash
make freq-gprof FILE=example.txt
```

The profiling report is written to profile.txt.

# Coverage
| FILE          | Lines     | Line Exec   | Line Cover | Branches   | Branches Exec   | Branch Cover |
| ------------- | --------- |--------|-------| --------- |--------|-------|
| hash_table.c  |   114     | 114    | 100%  |34    |  34  | 100%|
| linked_list.c |   105     | 105    | 100%  |26      |22 |   84%|

Data is from gcov, see Run section for information on how to run
 
# Design choices

The hash table and linked list use value_t to allow the data structures to store different types of values without having to implement separate versions for integers, pointers, floats, etc.

Both the list and hash table lack the ability to check added values if there type matches the type of the rest of the structure. Making debugging potentially harder.

Neither the list or hash table has ownership of pointers inserted or used as keys.

# Cleaning generated files

To remove compiled binaries and generated coverage/profiling files:

```bash
make clean
```
