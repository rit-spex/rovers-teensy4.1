# --------------------------------------------------------------------
#                           SPEX ROVER 2025
# --------------------------------------------------------------------
# Purpose: Simulate embedded Teensy subsystems as native executables
# Author : Tyler
# Date   : 2025-07-16
# --------------------------------------------------------------------

# ======= CONFIGURATION =======

SUBSYSTEMS := arm chassis science

# Select a single subsystem when invoking: make TARGET_SUBSYSTEM=arm
TARGET_SUBSYSTEM ?= arm
TARGET_EXEC := $(TARGET_SUBSYSTEM)

# Paths
SUBSYSTEM_DIR := ../$(TARGET_SUBSYSTEM)
BUILD_DIR     := build/spex_simulator
BIN_DIR       := bin
SIM_SRC_DIR   := src
SIM_INC_DIR   := include
LIBS_DIR      := ../libs
IMGUI_DIR     := ./external/imgui
SPDLOG_DIR    := ./external/spdlog

# Library Components
LIB_NAMES := CAN SMC SPARKMAX TICT249

# ======= SOURCES =======

SRC_DIRS := $(SUBSYSTEM_DIR)/src $(SIM_SRC_DIR)
INC_DIRS := $(SUBSYSTEM_DIR)/include $(SIM_INC_DIR)

$(foreach lib,$(LIB_NAMES), \
  $(eval SRC_DIRS += $(LIBS_DIR)/$(lib)/src) \
  $(eval INC_DIRS += $(LIBS_DIR)/$(lib)/include))

SRCS := $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name '*.cpp' -o -name '*.c' -o -name '*.s'))

IMGUI_SRCS := \
  $(IMGUI_DIR)/imgui.cpp \
  $(IMGUI_DIR)/imgui_demo.cpp \
  $(IMGUI_DIR)/imgui_draw.cpp \
  $(IMGUI_DIR)/imgui_tables.cpp \
  $(IMGUI_DIR)/imgui_widgets.cpp \
  $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
  $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp

SRCS += $(IMGUI_SRCS)
INC_DIRS += $(IMGUI_DIR) $(IMGUI_DIR)/backends $(SPDLOG_DIR)/include

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# ======= FLAGS =======

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
BUILD_DEF := -DBUILD_$(shell echo $(TARGET_SUBSYSTEM) | tr a-z A-Z)

CPPFLAGS := $(INC_FLAGS) -MMD -MP $(BUILD_DEF)
CXXFLAGS ?=
CFLAGS   ?=
LDFLAGS  := -lglfw -lGL -ldl -pthread

ifeq ($(GUI),1)
CPPFLAGS += -DENABLE_GUI
endif

# ======= BUILD RULES =======

# Default: build selected subsystem
all: $(BIN_DIR)/$(TARGET_EXEC)

# Build every subsystem (like build.sh all)
.PHONY: subsystems
subsystems:
	@for s in $(SUBSYSTEMS); do \
		$(MAKE) --no-print-directory TARGET_SUBSYSTEM=$$s; \
	done

# Convenience shortcuts: make arm / chassis / science
.PHONY: $(SUBSYSTEMS)
$(SUBSYSTEMS):
	@$(MAKE) --no-print-directory TARGET_SUBSYSTEM=$@

# Link final binary
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Built simulator: $@"

# Compile rules
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned all build output"

# Auto-dependencies
-include $(DEPS)
