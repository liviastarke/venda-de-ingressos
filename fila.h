#ifndef __FILA_H__
#define __FILA_H__

#include "cliente.h"

#define QUEUE_SIZE 20

// Estrutura Fila: FIFO - First In, First Out
typedef struct FilaCliente{
	Cliente * items[QUEUE_SIZE];
	int front;
	int back;
	int qtd;
}FilaCliente;

void init_fila(FilaCliente * fila);

int fila_vazia(FilaCliente * fila);

int cheia_fila(FilaCliente * fila);

int tamanho(FilaCliente * fila);

Cliente * primeiro(FilaCliente * fila);

void enfileira(FilaCliente * fila, Cliente * valor);

Cliente * desenfileira(FilaCliente * fila);

void print_fila(FilaCliente * fila);

// checa se tamanho armazenado e tamanho calculado batem
void check_func(FilaCliente * fila);

#endif
