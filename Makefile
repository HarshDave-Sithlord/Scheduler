CC=gcc
CFLAGS=-I.
DEPS = linklist.h, scheduler.h utils.h
OBJ = main.o scheduler.o linklist.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scheduler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm ./*.o ./*.exe scheduler