# Supreme Makefile by Václav Blažej

CC = g++
CXXFLAGS = --std=c++17 -Wall -Wextra -pedantic -g -O3 -fopenmp -l sqlite3 
DEPFLAGS     = -MT $@ -MMD -MP -MF ./build/$*.d


MAIN_FILES   = $(shell grep -lr 'int main' './src/' | grep 'cpp$$')
OTHER_FILES  = $(shell grep -Lr 'int main' './src/' | grep 'cpp$$')

SOURCE_FILES = $(OTHER_FILES) $(MAIN_FILES)
EXE_FILES    = $(MAIN_FILES:./src/%.cpp=./exe/%)
TEST_EXE_FLS = $(filter %test, $(EXE_FILES))
OBJECT_FILES = $(OTHER_FILES:./src/%.cpp=./build/%.o)
HEADER_FILES = $(OTHER_FILES:.cpp=.hpp)
DEPENDENCIES = $(SOURCE_FILES:./src/%.cpp=./build/%.d)

compile: $(EXE_FILES)

./build/%.o: ./src/%.cpp ./build/%.d
	@mkdir -p `dirname $@`
	$(CC) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

$(EXE_FILES): ./exe/%: ./src/%.cpp $(OBJECT_FILES)
	@mkdir -p `dirname $@`
	$(CC) $(CXXFLAGS) -o $@ $< $(OBJECT_FILES)

test: $(TEST_EXE_FLS)
	@./test.sh

.PHONY: clean
clean:
	@echo "don't change this rule, as it may be dangerous if small bugs are introduced"
	rm -rf build/ exe/

count:
	wc -l src/*.?pp src/*/*.?pp

$(DEPENDENCIES):
include $(wildcard $(DEPENDENCIES))
