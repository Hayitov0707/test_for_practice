CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

SRC = allocator.c linear_allocator.c pool_allocator.c buddy_allocator.c array_list.c queue.c hash_table.c main.c
OBJ = $(SRC:.c=.o)
TARGET = allocator_suite

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

fmt:
	clang-format -style=LLVM -i *.c *.h

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h

.PHONY: all test clean fmt check_fmt
