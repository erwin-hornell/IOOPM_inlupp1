CC = gcc

CFLAGS = -Wall -Wextra -g
LDLIBS = -lcunit

PROFLAGS = -pg
TIME = time --verbose
VALGRIND = valgrind
COVERAGE = gcovr 

TARGET_HASH = hash_table_tests
TARGET_LIST = linked_list_tests
TARGET_FREQ = freq-count

all: $(TARGET_HASH) $(TARGET_LIST)


hash_table_tests: hash_table.c hash_table_tests.c
	$(CC) $(CFLAGS) --coverage $^ -o $@ $(LDLIBS)

linked_list_tests: linked_list.c linked_list_tests.c
	$(CC) $(CFLAGS) --coverage $^ -o $@ $(LDLIBS)


test-hash: $(TARGET_HASH)
	./$(TARGET_HASH)

test-list: $(TARGET_LIST)
	./$(TARGET_LIST)


valgrind-hash: $(TARGET_HASH)
	$(VALGRIND) ./$(TARGET_HASH)

valgrind-list: $(TARGET_LIST)
	$(VALGRIND) ./$(TARGET_LIST)


coverage-hash: $(TARGET_HASH)
	./$(TARGET_HASH)
	$(COVERAGE) -r . --filter='hash_table.c'
	$(COVERAGE) --txt-metric branch --filter='hash_table.c'

coverage-list: $(TARGET_LIST)
	./$(TARGET_LIST)
	$(COVERAGE) -r . --filter='linked_list.c'
	$(COVERAGE) --txt-metric branch --filter='linked_list.c'


coverage: coverage-hash coverage-list

freq: hash_table.c
	$(CC) $(CFLAGS) $^ ./$(TARGET_FREQ).c -o $(TARGET_FREQ)


#Runs time om freq-time program
freq-time: hash_table.c
	$(CC) $(CFLAGS) $^ ./$(TARGET_FREQ).c -o $(TARGET_FREQ)
	$(TIME) ./$(TARGET_FREQ) $(FILE)

#Runs gprof on freq-count program
freq-gprof: hash_table.c
	$(CC) $(CFLAGS) $(PROFLAGS) $^ ./$(TARGET_FREQ).c -o $(TARGET_FREQ)
	./$(TARGET_FREQ) $(FILE)
	gprof $(TARGET_FREQ) gmon.out > profile.txt
	less profile.txt


clean:
	rm -f $(TARGET_HASH) $(TARGET_LIST) $(TARGET_FREQ)
	rm -f *.gcda *.gcno *.gcov
	rm -f gmon.out profile.txt


.PHONY: all test-hash test-list valgrind-hash valgrind-list \
        coverage-hash coverage-list coverage freq freq-time freq-gprof clean