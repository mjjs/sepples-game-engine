CXX = clang++
ARCHIVER = llvm-ar-11
CPPFLAGS ?= -Wall -Wextra -Wpedantic -std=c++20 -g

BUILD_DIR ?= build
TARGET ?= libsge.a
VENDOR_DIR ?= ../vendor

DEFINES = SPDLOG_COMPILED_LIB
DEFINE_FLAGS = $(addprefix -D,$(DEFINES))

# SOURCES
SRC_DIRS ?= src
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# INCLUDES
VENDOR_INCLUDES = $(VENDOR_DIR)/stb
VENDOR_INCLUDES += $(VENDOR_DIR)/spdlog/include
VENDOR_INCLUDES += $(VENDOR_DIR)/glad/include
VENDOR_INCLUDES += $(VENDOR_DIR)/assimp/include

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS += $(VENDOR_INCLUDES)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# LIBRARIES
LIBS = dl SDL2 assimp glad spdlog pthread z
VENDOR_LIB_PATHS = $(VENDOR_DIR)/spdlog/build $(VENDOR_DIR)/glad $(VENDOR_DIR)/assimp/build/lib $(VENDOR_DIR)/sdl/build
LDFLAGS = $(addprefix -l,$(LIBS)) $(addprefix -L,$(VENDOR_LIB_PATHS))

GLAD_STATIC_LIB =   $(VENDOR_DIR)/glad/libglad.a
SPDLOG_STATIC_LIB = $(VENDOR_DIR)/spdlog/build/libspdlog.a
SDL_STATIC_LIB =    $(VENDOR_DIR)/sdl/build/libSDL2.a
ASSIMP_STATIC_LIB = $(VENDOR_DIR)/assimp/build/lib/libassimp.a

STATIC_LIBS = $(GLAD_STATIC_LIB) $(SPDLOG_STATIC_LIB) $(SDL_STATIC_LIB) $(ASSIMP_STATIC_LIB)

$(BUILD_DIR)/$(TARGET): $(OBJS) deps
	$(ARCHIVER) rc $@ $(OBJS)
	./scripts/combine-static-libs.sh

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) $(DEFINE_FLAGS) -c $< -o $@

deps: $(STATIC_LIBS)

$(GLAD_STATIC_LIB):
	$(MAKE) -C $(VENDOR_DIR)/glad

$(SPDLOG_STATIC_LIB):
	$(MKDIR_P) $(VENDOR_DIR)/spdlog/build
	cd $(VENDOR_DIR)/spdlog/build && cmake .. && $(MAKE) -j

$(SDL_STATIC_LIB):
	$(MKDIR_P) $(VENDOR_DIR)/sdl/build
	cd $(VENDOR_DIR)/sdl/build && cmake .. && $(MAKE) -j

$(ASSIMP_STATIC_LIB):
	$(MKDIR_P) $(VENDOR_DIR)/assimp/build
	cd $(VENDOR_DIR)/assimp/build && cmake -D BUILD_SHARED_LIBS=OFF .. && $(MAKE) -j

run: $(BUILD_DIR)/$(TARGET)
	./build/game_engine

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)

clean-deps:
	$(RM) -r $(GLAD_STATIC_LIB) $(VENDOR_DIR)/spdlog/build $(VENDOR_DIR)/sdl/build $(VENDORI_DIR)/assimp/build

MKDIR_P ?= mkdir -p
