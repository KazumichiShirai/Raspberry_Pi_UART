#Makefile.c
all: ctrl_mbed
.c.o:
	gcc -c $*.c
ctrl_mbed : main.o com_mbed.o uart.o
	gcc -o ctrl_mbed main.o com_mbed.o uart.o
main.o : main.c com_mbed.h
com_mbed.o : com_mbed.c com_mbed.h uart.h
uart.o : uart.c uart.h
clean:
	rm -f *.o *~
