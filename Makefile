HW5: HW5.o
	gcc -o HW5 HW5.o

HW5.o: HW5.c header.h
	gcc -c HW5.c

clean:
	rm HW5 HW5.o
