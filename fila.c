#include "fila.h"

#include <stdio.h>

void init_fila(FilaCliente * fila){
	fila->front = 0;
	fila->back = -1;
	fila->qtd = 0;
}

int fila_vazia(FilaCliente * fila){
	return fila->qtd == 0;
}

int cheia_fila(FilaCliente * fila){
	return fila->qtd == QUEUE_SIZE;
}

int tamanho(FilaCliente * fila){
	if (fila_vazia(fila)){
		printf("fila vazia\n");
		return 0;
	} else {
		int size;
		if (fila->front < fila->back)
			size = (fila->back - fila->front);
		else
			size = (QUEUE_SIZE - fila->front) + fila->back;
		size++;
		printf("Tamanho é %d\n", size);
		return size;
	}
}

Cliente * primeiro(FilaCliente * fila){
	if (fila_vazia(fila)){
		printf("fila vazia\n");
		return NULL;
	}
	Cliente * ret = fila->items[fila->front];
	printf("primeiro: %p\n", ret);
	return ret;
}

void enfileira(FilaCliente * fila, Cliente * valor){
	if (cheia_fila(fila)){
		printf("pilha cheia\n");
	} else {
		fila->back = (fila->back + 1) % QUEUE_SIZE;
		fila->qtd++;
		fila->items[fila->back] = valor;
	}
}

Cliente * desenfileira(FilaCliente * fila){
	Cliente * item;
	if (fila_vazia(fila)){
		printf("fila vazia\n");
		return NULL;
	}
	item = fila->items[fila->front];
	fila->front = (fila->front + 1) % QUEUE_SIZE;
	fila->qtd--;
	printf("desenfileirado item [%p]\n", item);
	return item;
}

void print_fila(FilaCliente * fila){
	printf("-----------------------\nFila:\n");
	if(fila_vazia(fila)){
		printf("fila vazia\n");
		return;
	}

	for (int i = fila->front; i <= fila->back; i++){
		printf("FilaCliente[%d] = %p\n", i, fila->items[i]);
	}
	printf("-----------------------\n");
}

// checa se tamanho armazenado e tamanho calculado batem
void check_func(FilaCliente * fila){
	int tam = tamanho(fila);
	printf("\n-> tam = %d = %d\n", tam, fila->qtd);
	if (tam != fila->qtd){
		printf("Houve um erro no cálculo do tamanho!!!\n");
	}
}
