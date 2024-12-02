# Compiler and flags
CC = g++
CFLAGS = -Wall -g

# Days (directories)
DAYS = $(wildcard d*/)
TARGET = main
FILES = main.cpp 

# Compile all days
all: $(DAYS:%/$(TARGET))

# Rule to compile each day
%/$(TARGET): %/$(FILES)
	$(CC) $(CFLAGS) -o $@ $<

# Clean all days
clean:
	@for day in $(DAYS); do \
		rm -f $$day/$(TARGET); \
	done

# Build a specific days's executable
build: $(DAY)/$(TARGET)

# Run a specific days's executable
run: $(DAY)/$(TARGET)
	@echo "Specify the day to run: make run DAY=dX"
	@test -n "$(DAY)" && cd $(DAY) && ./$(TARGET) < input || echo "No target specified or invalid target."

# Run a specific days's executable using the sample input
run_sample: $(DAY)/$(TARGET)
	@echo "Specify the day to run: make run DAY=dX"
	@test -n "$(DAY)" && cd $(DAY) && ./$(TARGET) < sample || echo "No target specified or invalid target."

.PHONY: all clean run run_sample
