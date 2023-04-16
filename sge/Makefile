CXX = clang++
ARCHIVER = llvm-ar
CPPFLAGS ?= -Wall -Wextra -Wpedantic -std=c++20 -g

BUILD_DIR ?= build
TARGET ?= editor
VENDOR_DIR ?= ./vendor

DEFINES =  SPDLOG_COMPILED_LIB
DEFINES += SGE_ENABLE_PROFILING
DEFINE_FLAGS = $(addprefix -D,$(DEFINES))

# SOURCES
SRC_DIR ?= src
SRCS := $(SRC_DIR)/stb_image.cpp

SRCS += $(shell find $(SRC_DIR)/engine -name *.cpp)
SRCS += $(shell find $(SRC_DIR)/platform -name *.cpp)
SRCS += $(shell find $(SRC_DIR)/editor -name *.cpp)

SRCS += $(shell find $(VENDOR_DIR)/imgui/ -maxdepth 1 -name *.cpp)
SRCS += $(shell find $(VENDOR_DIR)/yaml-cpp/src -name *.cpp)
SRCS += $(VENDOR_DIR)/imgui/backends/imgui_impl_sdl.cpp
SRCS += $(VENDOR_DIR)/imgui/backends/imgui_impl_opengl3.cpp
SRCS += $(VENDOR_DIR)/imguizmo/ImGuizmo.cpp

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# INCLUDES
VENDOR_INCLUDES =  $(VENDOR_DIR)/stb
VENDOR_INCLUDES += $(VENDOR_DIR)/spdlog/include
VENDOR_INCLUDES += $(VENDOR_DIR)/glad/include
VENDOR_INCLUDES += $(VENDOR_DIR)/assimp/include
VENDOR_INCLUDES += $(VENDOR_DIR)/entt/single_include/entt
VENDOR_INCLUDES += $(VENDOR_DIR)/glm
VENDOR_INCLUDES += $(VENDOR_DIR)/imgui
VENDOR_INCLUDES += $(VENDOR_DIR)/sdl/include
VENDOR_INCLUDES += $(VENDOR_DIR)/yaml-cpp/include
VENDOR_INCLUDES += $(VENDOR_DIR)/portable-file-dialogs
VENDOR_INCLUDES += $(VENDOR_DIR)/imguizmo

INC_DIRS := $(SRC_DIR)
INC_DIRS += $(VENDOR_DIR)
INC_DIRS += $(VENDOR_INCLUDES)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# LIBRARIES
LIBS = dl SDL2 assimp glad spdlog pthread z
VENDOR_LIB_PATHS = $(VENDOR_DIR)/spdlog/build $(VENDOR_DIR)/glad $(VENDOR_DIR)/assimp/lib $(VENDOR_DIR)/sdl/build
LDFLAGS = $(addprefix -l,$(LIBS)) $(addprefix -L,$(VENDOR_LIB_PATHS))

$(BUILD_DIR)/$(TARGET): vendor $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) $(DEFINE_FLAGS) -c $< -o $@

vendor:
	$(MAKE) -C $(VENDOR_DIR)

.PHONY: clean run deps vendor

run: $(BUILD_DIR)/$(TARGET)
	./$<

clean:
	$(RM) -rf $(BUILD_DIR)

clean-deps:
	$(MAKE) clean -C $(VENDOR_DIR)

MKDIR_P ?= mkdir -p
