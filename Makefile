# Generic Makefile for compiling a simple executable.
 
CC := clang++
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
CFLAGS := -g -Wall -std=c++11
LIBS := -lSDL2 -lSDL2_image
TARGET := vroom

SRC_EXT := cpp
SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT) ! -name *\main.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

TEST_CFLAGS := -g -Wall -std=c++11 -I./ -I$(SRC_DIR)
TEST_LIBS := 
TEST_TARGET := vroomTest

TEST_SOURCES := $(shell find $(TEST_DIR) -type f -name *.$(SRC_EXT) ! -name *\main.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%,$(BUILD_DIR)/$(TEST_DIR)/%,$(TEST_SOURCES:.$(SRC_EXT)=.o))
TEST_DEPS := $(TEST_OBJECTS:.o=.deps)

all: $(TEST_TARGET) $(TARGET)

$(TARGET): $(OBJECTS) $(BUILD_DIR)/main.o
	@echo " Linking..."; $(CC) $^ -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS) $(BUILD_DIR)/$(TEST_DIR)/main.o
	@echo " Linking..."; $(CC) $^ -o $(TEST_TARGET) $(TEST_LIBS)

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	@echo " CC $<"; $(CC) $(TEST_CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

-include $(DEPS)
-include $(TEST_DEPS) 
.PHONY: clean