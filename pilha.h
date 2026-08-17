#ifndef __PILHA_H__
#define __PILHA_H__

#include "ingresso.h"

#define STACK_SIZE 20

// Estrutura Pilha: LIFO - Last In, First Out
typedef struct{
	Ingresso * items[STACK_SIZE];
	int top;
}PilhaIngresso;

int pilha_vazia(PilhaIngresso * stack);

int pilha_cheia(PilhaIngresso * stack);

// Empilhar
int push(PilhaIngresso * stack, Ingresso * item);

// Desempilhar
Ingresso * pop(PilhaIngresso * stack);

void init_stack(PilhaIngresso * stack);

// Retorna o valor no topo da pilha sem retirá-lo de lá.
Ingresso * top(PilhaIngresso * stack);

void print_stack(PilhaIngresso * stack);

#endif

