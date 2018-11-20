CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TARGET=tp-tas
RM=rm

CFLAGS=-Wall -g

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ) $(TARGET)
