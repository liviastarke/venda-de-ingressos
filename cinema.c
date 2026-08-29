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
	PilhaIngresso * pilhaA = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	PilhaIngresso * pilhaB = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	PilhaIngresso * pilhaC = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	empilhar_ingressos(pilhaA, &filmeA);

	FilaCliente * filaEntrada = NULL;
	FilaCliente * filaA = (FilaCliente *) malloc(sizeof(FilaCliente));
	FilaCliente * filaB = (FilaCliente *) malloc(sizeof(FilaCliente));
	FilaCliente * filaC = (FilaCliente *) malloc(sizeof(FilaCliente));
	init_fila(filaA);
	init_fila(filaB);
	init_fila(filaC);

	int opt = 1;
	while(opt != 0){
		printf("------------------------------\nO que deseja fazer hoje?\n\n");
		printf("0. Sair\n1. Abrir cinema para clientes\n2. Exibir pilhas de ingressos\n3. Exibir filas\n\n");
		scanf("%d", &opt);

		switch(opt){
		case 0:
			printf("Saindo...\n");
			break;
		case 1:
			printf("Abrindo as portas...\nFormou-se uma fila!\n");
			filaEntrada = receber_clientes();
			print_clientes(filaEntrada);
			break;
		case 2:
			print_ingressos(pilhaA);
			break;
		case 3:
			print_clientes(filaEntrada);
			print_clientes(filaA);
			print_clientes(filaB);
			print_clientes(filaC);
			break;
		default:
			printf("Opção inválida! Escolha uma opção válida! (•ˋ _ ˊ•)\n");
			break;
		}
	}
	return 0;
}

FilaCliente * receber_clientes(){
	FilaCliente * fila = malloc(sizeof(FilaCliente));
	init_fila(fila);
	Cliente * novo_cliente = criar_cliente("Lívia Sarah", 19, INGRESSO_NULO);
//	strcpy(novo_cliente->nome, "Lívia Sarah");
//	novo_cliente->idade = 19;
//	novo_cliente->ingresso = INGRESSO_NULO;
	enfileira(fila, novo_cliente);
	return fila;
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

void print_clientes(FilaCliente * fila){
	if (fila == NULL || fila_vazia(fila)){
		printf("Fila vazia\n");
		return;
	}

	for (int i = fila->front; i <= fila->back; i++){
		print_cliente(fila->items[i]);
	}
}

void print_ingresso(Ingresso * ingresso){
	if (ingresso == INGRESSO_NULO){
		printf("Sem ingresso\n");
		return;
	}

	printf("\"%s\" - Sala %d\t", ingresso->nome, ingresso->sala_de_exibicao);
	printf("-> R$%.2f\t", ingresso->preco);
	printf("%s", ctime(&ingresso->horario_da_secao));
}

void print_cliente(Cliente * cliente){
	printf("%s, %d anos\tIngresso: ", cliente->nome, cliente->idade);
	print_ingresso(cliente->ingresso);
}

Ingresso * criar_ingresso(char * nome, int sala_de_exibicao, time_t horario_de_exibicao, float preco){
	// TODO: prioridade baixa
}

Cliente * criar_cliente(char * nome, int idade, Ingresso * ingresso){
	Cliente * novo_cliente = malloc(sizeof(Cliente));
	strcpy(novo_cliente->nome, nome);
        novo_cliente->idade = idade;
        novo_cliente->ingresso = ingresso;
	return novo_cliente;
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
