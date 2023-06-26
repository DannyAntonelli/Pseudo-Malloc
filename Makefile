SRCDIR := src
TESTDIR := tests
OBJDIR := obj

# Find all source files in the source directory
SOURCES := $(wildcard $(SRCDIR)/*.c)

# Generate corresponding object file names for source files
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Find all test files in the tests directory
TEST_SOURCES := $(wildcard $(TESTDIR)/*.c)

# Generate corresponding object file names for test files
TEST_OBJS := $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/%.o, $(TEST_SOURCES))

# Compiler options
CC := gcc
CFLAGS := -c -Wall -Wextra -std=gnu99 -g -I$(SRCDIR)

# Target and dependencies
TARGET := $(OBJDIR)/main
TEST_TARGETS := $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/%, $(TEST_SOURCES))
DEPS := $(filter-out $(OBJDIR)/main.o, $(OBJS))

# Default target
all: $(TARGET)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to compile test files into object files
$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to build the final target
$(TARGET): $(DEPS) $(OBJDIR)/main.o
	$(CC) $^ -o $@
	$(RM) $(TARGET).o

# Rule to build each test target
$(OBJDIR)/%: $(OBJDIR)/%.o $(DEPS)
	$(CC) $^ -o $@

# Build all test targets
tests: $(TEST_TARGETS)

# Clean the generated object files and targets
clean:
	$(RM) $(OBJDIR)/*.o $(TARGET) $(TEST_TARGETS)