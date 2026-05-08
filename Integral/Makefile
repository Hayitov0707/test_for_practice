CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

LIB_SRC = integral.c
TEST_SRC = test_integral.c
TARGET = test_run

all: $(TARGET)

$(TARGET): $(LIB_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_SRC) $(TEST_SRC) $(LDFLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

fmt:
	clang-format -style=LLVM -i *.c *.h

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h

.PHONY: all test clean fmt check_fmt
