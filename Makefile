CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

DIRS = Integral Stack List Quadratic

TARGETS = $(shell find $(DIRS) -name "*.c" -not -name "*_test.c" 2>/dev/null | sed 's/\.c//')
TEST_TARGETS = $(shell find $(DIRS) -name "*_test.c" 2>/dev/null | sed 's/\.c//')

all: $(TARGETS) $(TEST_TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

test: all
	@for test in $(TEST_TARGETS); do \
		./$$test || exit 1; \
	done

clean:
	rm -f $(TARGETS) $(TEST_TARGETS)
	find . -type f -executable -exec rm -f {} +

fmt:
	clang-format -style=LLVM -i $$(find . -name "*.c" -o -name "*.h")

.PHONY: all test clean fmt
