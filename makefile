CC = gcc

SRC_DIR = src
OUT_DIR = out

EXEC = sand

RAYLIB_DIR = /opt/homebrew/opt/raylib
CFLAGS = -Wall -Wextra -Wpedantic -I$(RAYLIB_DIR)/include
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib

SOURCES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

default: all clean

all: $(OUT_DIR) $(EXEC)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(OUT_DIR)

.PHONY: all clean run
