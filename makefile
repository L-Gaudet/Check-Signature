# Compiler
CXX = g++

# Google Test path
GTEST_DIR = /opt/homebrew/opt/googletest

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I$(GTEST_DIR)/include

# Linker flags
LDFLAGS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

# Source and output directories
SRC_DIR = ./source
OBJ_DIR = ./obj
OUT_DIR = ./
TEST_DIR = ./tests

# Output binary names
OUTPUT = checksig
TEST_OUTPUT = testchecksig

# Find all .cc files in the source directory, excluding main.cc
SOURCES = $(filter-out $(SRC_DIR)/main.cc, $(wildcard $(SRC_DIR)/*.cc))

# Find the test file
TEST_SOURCE = $(TEST_DIR)/FileCheckerTests.cc

# Convert the source files into object files in the object directory
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))
MAIN_OBJECT = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_DIR)/CheckSigInterface.cc)
TEST_OBJECT = $(patsubst $(TEST_DIR)/%.cc, $(OBJ_DIR)/%.o, $(TEST_SOURCE))

# Default target
all: $(OUT_DIR)/$(OUTPUT)

# Rule to build the binary
$(OUT_DIR)/$(OUTPUT): $(OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the test binary
$(OUT_DIR)/$(TEST_OUTPUT): $(OBJECTS) $(TEST_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to build the test object file
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run the tests
run_tests: $(OUT_DIR)/$(TEST_OUTPUT)
	./$(OUT_DIR)/$(TEST_OUTPUT)

# Clean up
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(OUT_DIR)/$(OUTPUT)
	rm -f $(OUT_DIR)/$(TEST_OUTPUT)

# Phony targets
.PHONY: all run_tests clean
