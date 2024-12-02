BUILD_DIR?=build/
CC?=gcc
CFLAGS?=-ggdb
SOURCES_C=$(wildcard *.c)
OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/terminal/%.o, $(SOURCES_C))

.PHONY: all clean

all: terminal

terminal: $(BUILD_DIR)/terminal.bin

$(BUILD_DIR)/terminal.bin: main.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "--> Created  terminal.bin"

clean:
	@rm -f $(BUILD_DIR)/terminal.bin