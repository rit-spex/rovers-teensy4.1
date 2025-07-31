# --------------------------------------------------------------------
#                           SPEX ROVER 2025
# --------------------------------------------------------------------
# file name    : makefile
# purpose      : to compile the teensy subsystems into executables 
#                that comuincate with the ROS 
# created on   : 7/16/2025 - Tyler
# last modified: 7/16/2025 - Tyler
# --------------------------------------------------------------------

TARGET_EXEC := final_program

BUILD_DIR := ./build/build
INC_DIRS  := ./build/include
SRC_DIRS  := ./build/src
SRC_DIRS2 := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := $(SRCS) $(shell find $(SRC_DIRS2) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(INC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I./include

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)

# CXX ?= g++

# # executable # 
# BIN_NAME = runner

# # path #
# LIBS_PATH  = ../libs # the global libaries
# BIN_PATH   = ../bin  # the compiled executable
# BUILD_PATH = build   # a temp folder for building each subsystem

# # extensions #
# SRC_EXT = cpp

# # code lists #
# # Find all source files in the source directory
# SOURCES = $(shell find $(BUILD_PATH) -name "*.cpp")

# # Set the object file names, with the source directory stripped
# # from the path, and the build path prepended in its place
# OBJECTS = $(SOURCES:$(BUILD_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

# # Set the dependency files that will be used to add header dependencies
# DEPS = $(OBJECTS:.o=.d)

# # flags #
# COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
# INCLUDES = -I build/

# # Space-separated pkg-config libraries used by this project
# .PHONY: default_target
# default_target: release

# .PHONY: release
# release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
# release: dirs
# 	@$(MAKE) all

# .PHONY: dirs
# dirs:


# .PHONY: clean
# clean:
# 	@echo "Deleting build and bin directories"
# 	@$(RM) -r $(BIN_PATH)

# # checks the executable
# .PHONY: all
# all: $(BIN_PATH)/$(BIN_NAME)
# 	@echo "Making executable: $(BIN_NAME) -> $<"
# 	@$(RM) $(BIN_NAME)
# 	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# # Creation of the executable
# $(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
# 	@echo "Linking: $@"
# 	$(CXX) $(OBJECTS) -o $@ 

# 	@echo "Creating directories"
# 	@mkdir -p $(BIN_PATH)
# # Add dependency files, if they exist
# # -include $(DEPS)

# # Source file rules
# # After the first compilation they will be joined with the rules from the
# # dependency files to provide header dependencies
# $(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
# 	@echo "Compiling: $< -> $@"
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@