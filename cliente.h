#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "ingresso.h"

typedef struct Cliente{
	char nome[50];
	int idade;
	Ingresso * ingresso; // Eficiência no espaço: posso ter um "tipo" de ingresso para certo filme só uma vez na memória, todos os clientes e itens da pilha apontam para ele.
			     // Se eu alterar o horário da seção, todos os clientes e pilhas terão a versão atualizada, que é desejável nesse cenário.
}Cliente;

#endif
