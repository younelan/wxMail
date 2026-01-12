# wxEudora Makefile
# A wxWidgets port of Eudora email client

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = 

# wxWidgets configuration
WX_CONFIG = wx-config
WX_CXXFLAGS = $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS = $(shell $(WX_CONFIG) --libs aui,core,base,xrc)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/wxeudora

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/panels/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Create necessary directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link the executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(WX_LIBS)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(WX_CXXFLAGS) -c $< -o $@

# Run the application
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Check if wxWidgets is installed
check-wx:
	@echo "Checking wxWidgets installation..."
	@which $(WX_CONFIG) > /dev/null || (echo "ERROR: wx-config not found. Please install wxWidgets." && exit 1)
	@echo "wxWidgets version: $$($(WX_CONFIG) --version)"
	@echo "wxWidgets CXXFLAGS: $(WX_CXXFLAGS)"
	@echo "wxWidgets LIBS: $(WX_LIBS)"

# Help target
help:
	@echo "wxEudora Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build the application (default)"
	@echo "  run        - Build and run the application"
	@echo "  clean      - Remove build artifacts"
	@echo "  rebuild    - Clean and rebuild everything"
	@echo "  check-wx   - Verify wxWidgets installation"
	@echo "  help       - Show this help message"

.PHONY: all run clean rebuild check-wx help
