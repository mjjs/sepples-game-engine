CXX = clang++
CPPFLAGS ?= $(INC_FLAGS) -Wall -Wextra -Wpedantic -std=c++20 -g

TARGET ?= game_engine
SRC_DIRS ?= src
BUILD_DIR ?= build

LIBS = dl SDL2 assimp glad spdlog pthread
VENDOR_LIB_PATHS = vendor/spdlog/build vendor/glad

LDFLAGS = $(addprefix -l,$(LIBS)) $(addprefix -L,$(VENDOR_LIB_PATHS))

GLAD_STATIC_LIB = vendor/glad/libglad.a
SPDLOG_STATIC_LIB = vendor/spdlog/build/libspdlog.a

VENDOR_LIBS = $(GLAD_STATIC_LIB) $(SPDLOG_STATIC_LIB)

VENDOR_INCLUDES = vendor/stb
VENDOR_INCLUDES += vendor/spdlog/include
VENDOR_INCLUDES += vendor/glad/include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS += $(VENDOR_INCLUDES)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

DEFINES = SPDLOG_COMPILED_LIB
DEFINE_FLAGS = $(addprefix -D,$(DEFINES))

$(BUILD_DIR)/$(TARGET): $(OBJS) $(VENDOR_LIBS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) $(DEFINE_FLAGS) -c $< -o $@

$(GLAD_STATIC_LIB):
	$(MAKE) -C vendor/glad

$(SPDLOG_STATIC_LIB):
	$(MKDIR_P) vendor/spdlog/build
	cd vendor/spdlog/build && cmake .. && $(MAKE) -j

run: $(BUILD_DIR)/$(TARGET)
	./build/game_engine

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
