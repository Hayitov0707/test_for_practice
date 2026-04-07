CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Все программы
TARGETS = Integral List Quadratic_equation Stack

all: $(TARGETS)

# Added -lm here so the linker can find sin()
Integral: Integral.c
	$(CC) $(CFLAGS) -o Integral Integral.c -lm

List: List.c
	$(CC) $(CFLAGS) -o List List.c

Quadratic_equation: Quadratic_equation.c
	$(CC) $(CFLAGS) -o Quadratic_equation Quadratic_equation.c -lm

Stack: Stack.c
	$(CC) $(CFLAGS) -o Stack Stack.c

test: all
	@echo "=== Testing Integral ==="
	./Integral
	@echo "=== Testing List ==="
	./List
	@echo "=== Testing Stack ==="
	./Stack
	@echo "=== Testing Quadratic ==="
	./Quadratic_equation

clean:
	rm -f $(TARGETS)

.PHONY: all test clean
