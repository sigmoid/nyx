# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Define directories
SRCDIR = src
INCDIR = include
BINDIR = bin

# Define target
TARGET = $(BINDIR)/app

# Find all source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Run the application with arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Debug the application with arguments
debug: $(TARGET)
	gdb --args ./$(TARGET) $(ARGS)

# Clean the build
clean:
	rm -rf $(BINDIR)/*

# Phony targets
.PHONY: all run debug clean