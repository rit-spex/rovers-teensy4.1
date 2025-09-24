# --------------------------------------------------------------------
#                           SPEX ROVER 2025
# --------------------------------------------------------------------
# Purpose: Simulate embedded Teensy subsystems as native executables
# Author : Tyler
# Date   : 2025-07-16
# --------------------------------------------------------------------

# ======= CONFIGURATION =======

# Set this variable when invoking make: e.g., make TARGET_SUBSYSTEM=arm
TARGET_SUBSYSTEM ?= arm
TARGET_EXEC := $(TARGET_SUBSYSTEM)

# Paths
SUBSYSTEM_DIR := ../$(TARGET_SUBSYSTEM)
BUILD_DIR     := build
BIN_DIR       := bin
SIM_SRC_DIR   := src
SIM_INC_DIR   := include
LIBS_DIR      := ../libs
IMGUI_DIR := ./external/imgui

# Library Components
LIB_NAMES := CAN SMC SPARKMAX TICT249

# ======= SOURCE AND INCLUDE FILES =======

# Subsystem source and include dirs
SRC_DIRS := $(SUBSYSTEM_DIR)/src $(SIM_SRC_DIR)
INC_DIRS := $(SUBSYSTEM_DIR)/include $(SIM_INC_DIR)

# Add library source and include dirs
$(foreach lib,$(LIB_NAMES), \
    $(eval SRC_DIRS += $(LIBS_DIR)/$(lib)/src) \
    $(eval INC_DIRS += $(LIBS_DIR)/$(lib)/include) \
)

# Find all .cpp, .c, .s source files
SRCS := $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name '*.cpp' -o -name '*.c' -o -name '*.s'))

# Add imgui source files
IMGUI_SRCS := \
    $(IMGUI_DIR)/imgui.cpp \
    $(IMGUI_DIR)/imgui_demo.cpp \
    $(IMGUI_DIR)/imgui_draw.cpp \
    $(IMGUI_DIR)/imgui_tables.cpp \
    $(IMGUI_DIR)/imgui_widgets.cpp \
    $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
    $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \

# Add ImGui sources to the full source list
SRCS := $(SRCS) $(IMGUI_SRCS)

# Add ImGui headers to header list
INC_DIRS := $(INC_DIRS) $(IMGUI_DIR)
INC_DIRS := $(INC_DIRS) $(IMGUI_DIR)/backends

# Object files (e.g., build/src/foo.cpp.o)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Dependency files (e.g., build/src/foo.cpp.d)
DEPS := $(OBJS:.o=.d)

# ======= FLAGS =======

# Include flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Define build macro (e.g., -DBUILD_ARM)
BUILD_DEF := -DBUILD_$(shell echo $(TARGET_SUBSYSTEM) | tr a-z A-Z)

# Compiler flags
CPPFLAGS := $(INC_FLAGS) -MMD -MP $(BUILD_DEF)
LDFLAGS := -lglfw -lGL -ldl -pthread

# ======= BUILD RULES =======

# Default target
all: $(BIN_DIR)/$(TARGET_EXEC)

# Link final binary
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Built simulator: $@"

# C source build rule
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C++ source build rule
$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Assembly build rule (optional)
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET_SUBSYSTEM)
	@echo "Cleaned build output for: $(TARGET_SUBSYSTEM)"

# Auto-dependencies
-include $(DEPS)
