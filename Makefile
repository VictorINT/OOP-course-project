CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iinclude/models -Iinclude/managers -Iinclude/utils -Iinclude/views
LDFLAGS  = 

SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin

SOURCES  = $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS  = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET   = $(BIN_DIR)/FixItNow

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "\n>>> Compilation finished: $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo ">>> Cleanup finished."

run: all
	./$(TARGET)

.PHONY: all clean run