objects = cinema.o pilha.o fila.o

C-cinema : $(objects)
	cc $(objects) -o C-cinema

cinema.o : cinema.h ingresso.h cliente.h pilha.h fila.h
pilha.o : pilha.h ingresso.h
fila.o : fila.h cliente.h
