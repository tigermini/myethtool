CC = gcc
OBJS = main.o myethtool.o
TARGET = out

.PHONY:
	all clean
all:$(OBJS)
	$(CC) -o $(TARGET) main.o myethtool.o

main.o:main.c myethtool.h
	$(CC) -c main.c -o main.o
myethtool.o:myethtool.h
	$(CC) -c myethtool.c -o myethtool.o
clean:
	rm -rf $(OBJS) $(TARGET)

