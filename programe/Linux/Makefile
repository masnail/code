SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES)) 
ELF:=main
CFLAGS:=-Wall
CC:=gcc


$(ELF):$(OBJS)
	$(CC) -o $@ $^
.PHONEY:clean
clean:
	rm -rf $(ELF) $(OBJS)

