CC=gcc
CFLAGS=-I. -Wall -g -lm
TARGET=testing
DEPS=file_struct.h
OBJ = common.o file_handling.o hashing.o lcs.o memory.o string_ops.o testing.o bag_of_words.o fingerprint.o

%.o: %.c %.h $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	\rm testing *.o *.stackdump