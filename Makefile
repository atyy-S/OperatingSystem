#define the c compiler to use 
CC=gcc

#Define any compile-time flags
CFLAGS=-Wall -g

#Define the target executable name
TARGET=Lab2

#'all:=' us the defult target
all: $(TARGET)

# the target will be rebuilt when 'make' is run
$(TARGET) : $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 