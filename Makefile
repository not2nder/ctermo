CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LIBS = -lncurses

TARGET = ctermo
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
