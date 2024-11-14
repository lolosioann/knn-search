# Compiler
CC = gcc

export LD_LIBRARY_PATH=/usr/local/MATLAB/R2024b/bin/glnxa64:$LD_LIBRARY_PATH

# Paths
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
MATLAB_ROOT = /usr/local/MATLAB/R2024b# Update this with your actual MATLAB path

# Compiler and Linker flags
CFLAGS = -I$(INC_DIR) -I$(MATLAB_ROOT)/extern/include -Wall -O3 #-g #-O0
LDFLAGS = -L/usr/lib/x86_64-linux-gnu  -lstdc++ -lm -lopenblas -L$(MATLAB_ROOT)/bin/glnxa64 -lmat -lmx 

# Source files and corresponding object files in the build directory
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Executable name
TARGET = $(BUILD_DIR)/serial_knn

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .c file into .o file in the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn’t exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

