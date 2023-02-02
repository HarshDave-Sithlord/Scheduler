CC=gcc
CFLAGS=-I.
DEPS = linklist.h, scheduler.h utils.h create_obj.h exception_handler.h
OBJ = main.o scheduler.o linklist.o  create_obj.o exception_handler.o

%.o: %.c $(DEPS)
	$(CC) -c -l pthread -o $@ $< $(CFLAGS)

scheduler: $(OBJ)
	$(CC) -l pthread -o $@ $^ $(CFLAGS)
	
clean:
	rm ./*.o ./*.exe scheduler
