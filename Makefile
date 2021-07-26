CXX = clang++
CPPFLAGS ?= $(INC_FLAGS) -Wall -Wextra -Wpedantic -std=c++17 -g
LDFLAGS = -lGL -lGLEW -lSDL2 -lassimp

TARGET ?= game_engine
SRC_DIRS ?= src
BUILD_DIR ?= build

VENDOR_LIBS = vendor/stb vendor/spdlog/include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) $(LIBS_DIR)

INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(addprefix -I,$(VENDOR_LIBS))

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(TARGET)
	./build/game_engine

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
