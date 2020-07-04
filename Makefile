CXX = clang++
CPPFLAGS ?= $(INC_FLAGS) -Wall -Wextra -Wpedantic -std=c++17
LDFLAGS = -lGL -lGLEW -lSDL2

TARGET ?= game_engine
SRC_DIRS ?= src
BUILD_DIR ?= build

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
