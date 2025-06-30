EXEC = tema1
SRC = *.c
CC = gcc
OBJ = $(SRC:.c=.o)


CFLAGS = -Wall -Wextra

build:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

run:
	./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)
