# Variables for compilers and tools
# (only set if not already set)
GCC ?= /usr/bin/gcc
MKDIR ?= /bin/mkdir

CCFLAGS := -c
LDFLAGS :=

# Variables for input and output files and directories
INC_DIR ?= ./include
SRC_DIR ?= ./src
OBJ_DIR ?= ./obj
BIN_DIR ?= ./bin
PROG ?= snake


# Debug/Release configurations
ifeq ($(DEBUG),1)
OBJ_DIR := $(OBJ_DIR)/debug
BIN_DIR := $(BIN_DIR)/debug

CCFLAGS += -g -DDEBUG
else
OBJ_DIR := $(OBJ_DIR)/release
BIN_DIR := $(BIN_DIR)/release

CCFLAGS += -O3
endif

LIBRARIES := 
LIB_PATHS := 
INCLUDES :=

INCLUDES += $(INC_DIR)


# Inclusion of external headers and libraries


# Add headers and libraries to compiler/linker flags
CCFLAGS += $(foreach inc,$(INCLUDES),-I$(inc))
LDFLAGS += $(foreach path,$(LIB_PATHS),-L$(path))
LDFLAGS += $(foreach lib,$(LIBRARIES),-l$(lib))


# List all source files, corresponding object files, and their directories
CSRC := $(shell find $(SRC_DIR) -name \*.c)
SRC := $(CSRC)

COBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.c.o,$(CSRC))
OBJ := $(COBJ)

DIRS := $(sort $(dir $(OBJ)) $(dir $(BIN_DIR)/$(PROG)))


# Targets
.PHONY: build clean

default: $(BIN_DIR)/$(PROG)

$(BIN_DIR)/$(PROG): $(OBJ)
	$(GCC) $(LDFLAGS) $^ -o $@

$(OBJ): | $(DIRS)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(GCC) $(CCFLAGS) $^ -o $@

$(DIRS):
	@$(MKDIR) -p $@ 2> /dev/null; true

echo:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(DIRS)

clean:
	@rm $(OBJ) $(PROG) 2> /dev/null; true

