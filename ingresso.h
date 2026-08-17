#ifndef __INGRESSO_H__
#define __INGRESSO_H__

#include <time.h>

typedef struct Ingresso{
	char nome[50]; // deveria mudar para char* e alocar em tempo de execução?
	int sala_de_exibicao;
	time_t horario_da_secao;
	float preco;
}Ingresso;

#endif