CC = gcc

CFLAGS = -g -w -lpthread -lmysqlclient  -lcurses -lncursesw

TARGET = client

SrcFile = $(wildcard *.c)

ObjFile = $(patsubst %.c,%.o,$(SrcFile))

$(TARGET):$(ObjFile)
	@$(CC) $(ObjFile) -o $(TARGET) $(CFLAGS)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
	clean

clean:
	rm -rf *.o client

