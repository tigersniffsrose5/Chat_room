CC = gcc

vpath %.h  ./Common/

CFLAGS = -g -w -lpthread -lmysqlclient 

TARGET = server

SrcFile = $(shell find . -name "*.c")

ObjFile = $(patsubst %.c,%.o,$(SrcFile))

$(TARGET):$(ObjFile)
	@$(CC) $(ObjFile) -lm -o $(TARGET) $(CFLAGS)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
	clean

clean:
	rm -rf *.o server


