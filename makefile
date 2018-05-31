simulador: simulador.o
	gcc simulador.o -o simulador -std=c99  -O2
simulador.o: main.c
	gcc -c main.c -o simulador.o -std=c99 -O2
clean:
	rm *.o simulador
