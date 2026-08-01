CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Iinclude
LIBS = -lncurses

TARGET = termo
SRC = src/main.c src/ui.c src/colors.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
