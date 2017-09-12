CC=gcc
CFLAGS=-I. -Wall
TARGET=testing
OBJ = common.o file_handling.o hashing.o lcs.o memory.o string_ops.o testing.o

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	\rm testing.exe *.o