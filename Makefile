DEBUG ?= false
EXEC = mt     #final executable name

# build direcotries
OBJ     = obj
LIB     = lib
INCLUDE = include
BUILD   = build
BIN     = bin
SRC     = src
MAIN    = $(SRC)/main.c
CORE    = $(SRC)/core

# set gcc options
CC     = gcc
CFLAGS = -Wall -Werror -Wextra -O2
ifeq ($(DEBUG),true)
    CFLAGS += -g -O0
endif

# sources and object files
SRCS = $(wildcard $(CORE)/*.c)
OBJS = $(patsubst $(CORE)/%.c, $(OBJ)/%.o, $(SRCS)) $(OBJ)/main.o

all: $(OBJS)
ifeq ($(DEBUG),true)
    @echo "Generate executables in debug mode..."
else
    @echo "Generate executables in release mode..."
endif
    $(CC) $^ -o $(BUILD)/$(EXEC) $(CFLAGS)

$(OBJ)/%.o : $(CORE)/%.c
    $(CC) -I$(INCLUDE) -c $< -o $@ $(CFLAGS)

$(OBJ)/main.o : $(MAIN)
    $(CC) -I$(INCLUDE) -c $< -o $@ $(CFLAGS)

clean:
    @echo "Cleaning all .o files..."
    rm -rf $(OBJ)/*

mrproper: clean
    @echo "Cleaning all generated files..."
    rm -rf $(BUILD)/* $(LIB)/*

.PHONY: all clean mrproper