CXX = clang++
CPPFLAGS ?= $(INC_FLAGS) -Wall -Wextra -Wpedantic -std=c++20 -g
LDFLAGS = -ldl -lSDL2 -lassimp -lglad -Lvendor/glad

TARGET ?= game_engine
SRC_DIRS ?= src
BUILD_DIR ?= build

GLAD_STATIC_LIB = vendor/glad/glad.a

VENDOR_LIBS = $(GLAD_STATIC_LIB)

VENDOR_INCLUDES = vendor/stb
VENDOR_INCLUDES += vendor/spdlog/include
VENDOR_INCLUDES += vendor/glad/include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS += $(VENDOR_INCLUDES)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET): $(OBJS) $(VENDOR_LIBS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $< -o $@

$(GLAD_STATIC_LIB):
	$(MAKE) -C vendor/glad

run: $(BUILD_DIR)/$(TARGET)
	./build/game_engine

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
