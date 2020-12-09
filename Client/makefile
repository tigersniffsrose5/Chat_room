CC = gcc

vpath %.h ./Common/libb64/include/b64/ ./Common/

CFLAGS = -g -w -lpthread -lcurses -lncursesw -ICommon/libb64/include

TARGET = client

SrcFile = $(shell find . -name "*.c")

ObjFile = $(patsubst %.c,%.o,$(SrcFile))

$(TARGET):$(ObjFile)
	@$(CC) $(ObjFile) -lm -o $(TARGET) $(CFLAGS)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
	clean

clean:
	$(RM) $(ObjFile) client


