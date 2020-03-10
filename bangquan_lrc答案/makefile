SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o, $(SRC))
TARGET = test
CC = gcc
$(TARGET): $(OBJ)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $< -o $@
clean:
	rm *.o $(TARGET) 
