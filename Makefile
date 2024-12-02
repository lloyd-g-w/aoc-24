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
# make build DAY=X
build: $(DAY)/$(TARGET)

# Run a specific days's executable
# make run DAY=X
run: d$(DAY)/$(TARGET)
	@test -n "d$(DAY)" && cd d$(DAY) && ./$(TARGET) < input || echo "No target specified or invalid target."

# Run a specific days's executable using the sample input
# make run_sample DAY=X
run_sample: d$(DAY)/$(TARGET)
	@test -n "d$(DAY)" && cd d$(DAY) && ./$(TARGET) < sample || echo "No target specified or invalid target."

.PHONY: all clean run run_sample
