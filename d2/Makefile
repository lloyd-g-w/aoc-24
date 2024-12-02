CC = g++
CFLAGS = -Wall -g
TARGET = main
FILES = main.cpp 
OBJS = $(FILES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(FILES:.cpp=.d) $(TARGET)

run: $(TARGET)
	./$(TARGET) < input

run_sample: $(TARGET)
	./$(TARGET) < sample 

.PHONY: all clean run run_sample
