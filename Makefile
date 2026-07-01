CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/operations.c src/ui.c src/menu.c src/helpers.c src/habit.c
OUT = bin/momentum

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
