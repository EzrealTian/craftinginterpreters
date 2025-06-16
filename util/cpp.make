# Makefile for building a single configuration of the CPP interpreter. It expects
# variables to be passed in for:
#
# MODE         "debug" or "release".
# NAME         Name of the output executable (and object file directory).
# SOURCE_DIR   Directory where source files and headers are found.

CC := g++
CXX := g++  
CFLAGS := -std=c++17
CXXFLAGS := $(CFLAGS)

CFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter

# If we're building at a point in the middle of a chapter, don't fail if there
# are functions that aren't used yet.
ifeq ($(SNIPPET),true)
	CFLAGS += -Wno-unused-function
endif

# Mode configuration.
ifeq ($(MODE),debug)
	CFLAGS += -O0 -DDEBUG -g
	BUILD_DIR := build/debug
else
	CFLAGS += -O3 -flto
	BUILD_DIR := build/release
endif

# Files.
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.cc)
OBJECTS := $(addprefix $(BUILD_DIR)/$(NAME)/, $(notdir $(SOURCES:.cc=.o)))

# Targets ---------------------------------------------------------------------

# Link the interpreter.
$(BUILD_DIR)/$(NAME)/%.o: $(SOURCE_DIR)/%.cc $(HEADERS)
	@ printf "%8s %-40s %s\n" $(CXX) $< "$(CXXFLAGS)"
	@ mkdir -p $(@D)  # 自动创建目录
	@ $(CXX) -c $(CXXFLAGS) -o $@ $<

# Compile object files.
build/$(NAME): $(OBJECTS)
	@ printf "%8s %-40s %s\n" $(CXX) $@ "$(CXXFLAGS)"
	@ mkdir -p build
	@ $(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: default