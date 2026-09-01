objects = cinema.o pilha.o fila.o

C-cinema : $(objects)
	cc $(objects) -o C-cinema

cinema.o : cinema.c cinema.h ingresso.h cliente.h pilha.h fila.h
	cc -c cinema.c -o cinema.o -g
pilha.o : pilha.c pilha.h ingresso.h
	cc -c pilha.c -o pilha.o -g
fila.o : fila.c fila.h cliente.h
	cc -c fila.c -o fila.o -g

clean :
	rm C-cinema $(objects)

