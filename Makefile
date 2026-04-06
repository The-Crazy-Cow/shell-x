DEBUG ?= false
EXEC = mt

# build directories
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
	CFLAGS += -DDEBUG -g -O0  
#see also gcc fsanitize and his options  for gdb
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
	if [ -f "file.db" ]; then mv file.db build/; fi  #move the db file to the build directory if build programm in root directory of project

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

#use only for some internal tests
do_test:
	$(CC) tests.c -o test
	@echo "running test result\n\n"
	./test

clean_test:
	rm -rf test

##################################

.PHONY: all clean mrproper