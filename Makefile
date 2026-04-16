CC=gcc
CFLAGS=-O2 -Wall -Wextra -I.
LIBS=-lm

SRC_DIR=exemplos
OBJ_DIR=obj
BIN_DIR=bin

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BINS=$(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

all: dirs $(BINS)

dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c partitura.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) $< -o $@ $(LIBS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean dirs
