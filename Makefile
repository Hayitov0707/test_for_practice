CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
AR = ar rc

# Старые программы
OLD_TARGETS = Integral List Quadratic_equation Stack

all: $(OLD_TARGET)

# --- Старые цели (твои программы) ---

Integral: Integral.c
	$(CC) $(CFLAGS) -o Integral Integral.c -lm

List: List.c
	$(CC) $(CFLAGS) -o List List.c

Quadratic_equation: Quadratic_equation.c
	$(CC) $(CFLAGS) -o Quadratic_equation Quadratic_equation.c -lm

Stack: Stack.c
	$(CC) $(CFLAGS) -o Stack Stack.c


# Запускаем и твои старые тесты, и новый тест библиотеки
test: all
	@echo "=== Testing Integral ==="
	./Integral
	@echo "=== Testing List ==="
	./List
	@echo "=== Testing Stack ==="
	./Stack
	@echo "=== Testing Quadratic ==="
	./Quadratic_equation


# Чистка всего: и программ, и объектников, и библиотек
clear:
	rm -f $(OLD_TARGETS) *.o *.a

# Совместимость: чтобы старая команда clean тоже работалclean: clear

# Форматирование (по твоему новому стилю)
fmt:
	clang-format -style=LLVM -i `find . -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find . -regex ".+\.[ch]"` --dry-run --Werror

.PHONY: all test clear clean fmt check_fmt
