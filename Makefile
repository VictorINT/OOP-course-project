# Makefile pentru FixItNow

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# gaseste toate cpp-urile automat
SOURCES = $(shell find src -name '*.cpp')
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

TARGET = bin/fixitnow

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(OBJECTS) -o $@
	@echo "Build complete"

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin
	rm -f *.csv rapoarte/*.csv rapoarte/*.txt
	@echo "Clean"

run: all
	./$(TARGET)

.PHONY: all clean run
