CXX = clang++
CPPFLAGS ?= -Wall -Wextra -Wpedantic -std=c++20 -g

BUILD_DIR ?= build
TARGET ?= testgame
VENDOR_DIR ?= ../vendor

# SOURCES
SRCS := main.cpp
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# INCLUDES
VENDOR_INCLUDES = $(VENDOR_DIR)/stb
VENDOR_INCLUDES += $(VENDOR_DIR)/spdlog/include
VENDOR_INCLUDES += $(VENDOR_DIR)/glad/include
VENDOR_INCLUDES += $(VENDOR_DIR)/assimp/include

INC_DIRS := $(shell find ../libsge/src/engine -type d) .
INC_DIRS += $(VENDOR_INCLUDES)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# LIBRARIES
LIBS = sge z dl pthread
LIB_PATHS = ../libsge/build
LDFLAGS = $(addprefix -l,$(LIBS)) $(addprefix -L,$(LIB_PATHS))

.PHONY: clean run engine

$(BUILD_DIR)/$(TARGET): $(OBJS) engine
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $< -o $@

engine:
	$(MAKE) -C ../libsge

run: $(BUILD_DIR)/$(TARGET)
	./$<

clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
