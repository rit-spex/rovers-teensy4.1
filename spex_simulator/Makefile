# --------------------------------------------------------------------
#                           SPEX ROVER 2025
# --------------------------------------------------------------------
# file name    : makefile
# purpose      : to compile the teensy subsystems into executables 
#                that comuincate with the ROS 
# created on   : 7/16/2025 - Tyler
# last modified: 7/16/2025 - Tyler
# --------------------------------------------------------------------

# the subsystem name
TARGET_SUBSYSTEM:= chassis

# the exe name
TARGET_EXEC := $(TARGET_SUBSYSTEM)

# the libs folder
TARGET_LIBS:= ./libs

SUBSYSTEM_PATH:= ../$(TARGET_SUBSYSTEM)
BUILD_DIR := ./build
INC_DIRS  := $(SUBSYSTEM_PATH)/include
SRC_DIRS  := $(SUBSYSTEM_PATH)/src
SRC_DIRS2 := ./src
BIN_DIR   := ./bin

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := $(SRCS) $(shell find $(SRC_DIRS2) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# add the libs sources
SRCS := $(SRCS) $(shell find ../libs/CAN/src -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := $(SRCS) $(shell find ../libs/SMC/src -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := $(SRCS) $(shell find ../libs/SPARKMAX/src -name '*.cpp' -or -name '*.c' -or -name '*.s')
SRCS := $(SRCS) $(shell find ../libs/TICT249/src -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(INC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I./include -I../libs/CAN/include -I../libs/SMC/include -I../libs/SPARKMAX/include -I../libs/TICT249/include

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
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
	rm -r ./$(TARGET_SUBSYSTEM)
	rm -r $(TARGET_LIBS)


# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)