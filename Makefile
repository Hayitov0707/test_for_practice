# Определяем компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

# Список всех исходных файлов и тестов
SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
OBJS = $(SRCS:.c=.o)
TEST_BINS = $(TEST_SRCS:.c=)

.PHONY: all clean format check-format test

all: $(OBJS)

# 1. Очистка директории
clean:
	rm -rf *.o $(TEST_BINS) *.out

# 2. Форматирование (используем clang-format)
format:
	clang-format -i *.c *.h

# 3. Проверка форматирования
check-format:
	clang-format --dry-run --Werror *.c *.h

# 4. Запуск тестов
test: $(TEST_BINS)
	@for test_bin in $(TEST_BINS); do \
		echo "Running $$test_bin..."; \
		./$$test_bin || exit 1; \
	done

# Правило для сборки тестов
%_test: %_test.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
