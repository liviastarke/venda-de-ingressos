#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "ingresso.h"

typedef struct Cliente{
	char nome[50];
	int idade;
	Ingresso ingresso;
}Cliente;

#endif