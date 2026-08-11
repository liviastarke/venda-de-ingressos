#ifndef __CINEMA_H__
#define __CINEMA_H__

typedef struct Ingresso{
	char nome[50]; // deveria mudar para char* e alocar em tempo de execução?
	int sala_de_exibicao;
	time_t horario_da_secao;
	float preco;
}Ingresso;

typedef struct Cliente{
	char nome[50];
	int idade;
	Ingresso ingresso;
}Cliente;

#include "pilha.h"

void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme);

void print_ingressos(PilhaIngresso * pilha);
void print_ingresso(Ingresso * ingresso);

#endif

