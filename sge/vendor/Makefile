CXX = clang++
ARCHIVER = llvm-ar-11
CPPFLAGS ?= -std=c++20 -g
# Uncomment for debugging
#CPPFLAGS += -Wall -Wextra -Wpedantic

BUILD_DIR ?= build

DEFINES = SPDLOG_COMPILED_LIB
DEFINE_FLAGS = $(addprefix -D,$(DEFINES))

# SOURCES
SRCS += imgui/ -maxdepth 1 -name *.cpp
SRCS += yaml-cpp/src -name *.cpp
SRCS += imgui/backends/imgui_impl_sdl.cpp
SRCS += imgui/backends/imgui_impl_opengl3.cpp
SRCS += imguizmo/ImGuizmo.cpp

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

GLAD_STATIC_LIB =   glad/libglad.a
SPDLOG_STATIC_LIB = spdlog/build/libspdlog.a
SDL_STATIC_LIB =    sdl/build/libSDL2.a
ASSIMP_STATIC_LIB = assimp/build/lib/libassimp.a

STATIC_LIBS = $(GLAD_STATIC_LIB) $(SPDLOG_STATIC_LIB) $(SDL_STATIC_LIB) $(ASSIMP_STATIC_LIB)

all: $(STATIC_LIBS)

$(GLAD_STATIC_LIB):
	$(MAKE) -C glad

$(SPDLOG_STATIC_LIB):
	$(MKDIR_P) spdlog/build
	cd spdlog/build && cmake .. && $(MAKE) -j

$(SDL_STATIC_LIB):
	$(MKDIR_P) sdl/build
	cd sdl/build && cmake .. && $(MAKE) -j

$(ASSIMP_STATIC_LIB):
	$(MKDIR_P) assimp/build
	cd assimp/build && cmake -D BUILD_SHARED_LIBS=OFF .. && $(MAKE) -j

.PHONY: clean run deps

clean:
	$(RM_RF) spdlog/build
	$(RM_RF) sdl/build
	$(RM_RF) assimp/build
	$(RM_RF) glad/libglad.a

MKDIR_P ?= mkdir -p
RM_RF ?= rm -rf
