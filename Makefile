CC = gcc
CFLAGS = -Wall -g

TARGET = Aty_TestLibFS

SRCS = Aty_TestLibFS.c Aty_LibFS.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o