TARGET = program
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

format:
	clang-format -i $(SRCS)

check-format:
	clang-format --dry-run --Werror $(SRCS)

test: $(TARGET)
	./$(TARGET)
