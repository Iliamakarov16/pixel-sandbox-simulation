# Simple cross-platform Makefile for a raylib project
# Usage:
#   make            # build Release
#   make DEBUG=1    # build Debug
#   make run        # run the program
#   make clean      # remove build artifacts

# Project settings
APP_NAME := pixel-simulation
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

# Toolchain
CXX ?= g++ 
DEBUG ?= 0

ifeq ($(DEBUG),1)
  CXXFLAGS ?= -std=c++17 -O0 -g3 -Wall -Wextra -Wpedantic
else
  CXXFLAGS ?= -std=c++17 -O2 -DNDEBUG -Wall -Wextra -Wpedantic
endif

# Ensure pkg-config can see common system paths (helps on WSL/Ubuntu)
export PKG_CONFIG_PATH ?= /usr/lib/x86_64-linux-gnu/pkgconfig:/usr/lib/pkgconfig:/usr/share/pkgconfig

# Try pkg-config first for raylib
HAVE_PKGCONFIG := $(shell pkg-config --exists raylib && echo yes || echo no)
ifeq ($(HAVE_PKGCONFIG),yes)
  RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
  RAYLIB_LIBS   := $(shell pkg-config --libs raylib)
else
  # Fallback per-platform link flags. Optionally set RAYLIB_INC and RAYLIB_LIBDIR.
  RAYLIB_INC ?=
  RAYLIB_LIBDIR ?=
  RAYLIB_CFLAGS := $(if $(RAYLIB_INC),-I$(RAYLIB_INC),)
  
  # Detect platform
  UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
  ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    RAYLIB_LIBS := $(if $(RAYLIB_LIBDIR),-L$(RAYLIB_LIBDIR),) -lraylib -lopengl32 -lgdi32 -lwinmm
  else ifeq ($(UNAME_S),Darwin)
    # macOS
    RAYLIB_LIBS := $(if $(RAYLIB_LIBDIR),-L$(RAYLIB_LIBDIR),) -lraylib \
                   -framework Cocoa -framework IOKit -framework CoreFoundation \
                   -framework CoreVideo -framework OpenGL
  else
    # Linux and others (WSL/Ubuntu): try to auto-detect common install paths
    # Auto-detect header dir if not provided
    ifeq ($(RAYLIB_INC),)
      RAYLIB_INC := $(shell \
        if [ -f /usr/include/raylib.h ]; then echo /usr/include; \
        elif [ -f /usr/local/include/raylib.h ]; then echo /usr/local/include; \
        elif [ -f /usr/include/raylib/raylib.h ]; then echo /usr/include/raylib; \
        elif [ -f /usr/local/include/raylib/raylib.h ]; then echo /usr/local/include/raylib; \
        fi)
    endif
    RAYLIB_CFLAGS := $(RAYLIB_CFLAGS) $(if $(RAYLIB_INC),-I$(RAYLIB_INC),)

    # Auto-detect lib dir if not provided
    ifeq ($(RAYLIB_LIBDIR),)
      RAYLIB_LIBDIR := $(shell \
        if [ -f /usr/lib/x86_64-linux-gnu/libraylib.so ] || [ -f /usr/lib/x86_64-linux-gnu/libraylib.a ]; then echo /usr/lib/x86_64-linux-gnu; \
        elif [ -f /usr/local/lib/libraylib.so ] || [ -f /usr/local/lib/libraylib.a ]; then echo /usr/local/lib; \
        elif [ -f /usr/lib/libraylib.so ] || [ -f /usr/lib/libraylib.a ]; then echo /usr/lib; \
        fi)
    endif

    RAYLIB_LIBS := $(if $(RAYLIB_LIBDIR),-L$(RAYLIB_LIBDIR),) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXi
  endif
endif

# Build rules
all: $(APP_NAME)

$(APP_NAME): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(RAYLIB_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

run: $(APP_NAME)
	./$(APP_NAME)

clean:
	$(RM) $(OBJ) $(APP_NAME) $(APP_NAME).exe

.PHONY: all run clean
