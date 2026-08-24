// Entrega dia 24/09
//
// fila de pessoas (já preenchida)
// pilha de ingressos (já preenchida)
// venda: desempilha ingresso, pessoa sai da fila e é criado um par pessoa-ingresso
// fila do filme/sala: fila de pares pessoa-ingresso, inicialmente vazias e vão sendo preenchidas após as vendas
// print de todas as filas
//
// filas são circulares, pilhas são vetores

#include "cinema.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	printf("\nBem vindo ao sistema de venda de ingressos CineCapi!\n\n");
	
	time_t hora = time(NULL);
	Ingresso filmeA = {"Titanic", 1, hora, 19.9};
	PilhaIngresso * pilhaA = (PilhaIngresso *) malloc(sizeof(PilhaIngresso)); //init_stack(pilhaA);
	empilhar_ingressos(pilhaA, &filmeA);

	int opt = 1;
	while(opt != 0){
		printf("------------------------------\nO que deseja fazer hoje?\n\n");
		printf("0. Sair\n1. Abrir cinema para clientes\n2. Exibir pilhas de ingressos\n\n");
		scanf("%d", &opt);

		switch(opt){
		case 0:
			printf("Saindo...\n");
			break;
		case 1:
			printf("Abrindo as portas...\nFormou-se uma fila!\n");
			// preencher clientes aqui
			break;
		case 2:
			print_ingressos(pilhaA);
			break;
		default:
			printf("Opção inválida! Escolha uma opção válida! (•ˋ _ ˊ•)\n");
			break;
		}
	}
	return 0;
}

void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme){
	init_stack(pilha); // IMPORTANTE!
	for (int i = 0; i < STACK_SIZE; i++){ // encher até o final
		push(pilha, filme);
	}
}

void print_ingressos(PilhaIngresso * pilha){
	for (int i = 0; i < STACK_SIZE; i++){
		if (i <= pilha->top){
			printf("Ingresso [%d]:\t", i+1);
			print_ingresso(pilha->items[i]);
		}
	}
}

void print_ingresso(Ingresso * ingresso){
	printf("\"%s\" - Sala %d\t", ingresso->nome, ingresso->sala_de_exibicao);
	printf("-> R$%.2f\t", ingresso->preco);
	printf("%s", ctime(&ingresso->horario_da_secao));
}

void check_alloc_err(void * pointer){
    if (pointer == NULL){
        printf("Foi detectado um erro.\n");
        exit(EXIT_FAILURE); // terminar o programa com erro
    }
}

void esperar(){ // travar até resposta
	printf("\nPressione ENTER para continuar");
	getchar();
	getchar();
}