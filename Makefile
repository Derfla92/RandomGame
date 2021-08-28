COMPILING := g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g -pg

LIB := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lyaml-cpp -lstdc++fs

OBJ_DIR := build
SRC_DIR := src

SRC_FILES := $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(OBJ_FILES)
	$(COMPILING) $^ -o program $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	mkdir -p build
	$(COMPILING) $(LIB) -c -o $@ $<

.PHONY: clean

.PHONY:run

.PHONY:clean run

run:run_it go


run_it:
	make
ifeq ($(OS),Windows_NT)
go:
	./program.exe

clean:
	rm -rf $(OBJ_DIR)/*
	rm -f program.exe
	
else
go:
	./program
clean:
	rm -rf $(OBJ_DIR)/*
	rm -f program
endif
