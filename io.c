#include "io.h"

#include <stdio.h>

void esperar(){ // travar até resposta
	int c;
	printf("\nPressione ENTER para continuar");
	while((c = getchar()) != '\n' && c != EOF); // get at least one char till \n and maintain buffer clean
}

/**
 * Função de entrada para números inteiros.
 *
 * Usa scanf mas checa o número de elementos lidos para ter certeza de retornar um valor válido e limpa o buffer para evitar loop infinito.
 *
 */
int get_opt(){
	int opt;
	int c;
	while(1){
		if (scanf("%d", &opt) == 1)
			break;
		printf("Por favor, entre um número: ");
		while((c = getchar()) != '\n' && c != EOF); // clean buffer if invalid input
	}
	while((c = getchar()) != '\n' && c != EOF); // clean buffer for next call to get_opt or esperar
	return opt;
}

