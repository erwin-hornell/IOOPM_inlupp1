CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lcunit

TARGET = hash_table_tests

all: $(TARGET)

$(TARGET): hash_table.c hash_table_tests.c hash_table.h
	$(CC) $(CFLAGS) hash_table.c hash_table_tests.c -o $(TARGET) $(LDLIBS)

test: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test valgrind clean