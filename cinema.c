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

#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_FILMES 3

int main(){
	printf("\nBem vindo ao sistema de venda de ingressos CineCapi!\n\n");
	
	Ingresso filmes[NUM_FILMES] = {
		{"Cyrano de Bergerac", 1, 1791063000, 14.99},
		{"Vidas ao Vento",     2, 1790978400, 23.89},
		{"Quarto de Guerra",   3, 1791061200, 19.90},
	};

	PilhaIngresso * ingressos = (PilhaIngresso *) malloc(sizeof(PilhaIngresso)*NUM_FILMES);

	for(int i = 0; i < NUM_FILMES; i++){
		empilhar_ingressos(&ingressos[i], &filmes[i]);
	}

	FilaCliente * filaEntrada = NULL;

	FilaCliente * filasFilmes = (FilaCliente *) malloc(sizeof(FilaCliente)*NUM_FILMES);

	for(int i = 0; i < NUM_FILMES; i++){
		init_fila(&filasFilmes[i]);
	}

	int opt = 1;
	while(opt != 0){
		printf("------------------------------\nO que deseja fazer hoje?\n\n");
		printf("0. Sair\n1. Abrir cinema para clientes\n2. Exibir pilhas de ingressos\n3. Exibir filas\n4. Vender ingresso\n\n");
		opt = get_opt();

		switch(opt){

		case 0:
			printf("Saindo...\n");
			break;

		case 1:
			printf("Abrindo as portas...\nFormou-se uma fila!\n");
			filaEntrada = receber_clientes();
			print_clientes(filaEntrada);
			esperar();
			break;

		case 2:
			for(int i = 0; i < NUM_FILMES; i++){
				printf("--------\nPilha %d:\n", i+1);
				print_ingressos(&ingressos[i]);
				printf("\n");
				esperar();
			}
			break;

		case 3:
			printf("--------\nFila de entrada:\n");
			print_clientes(filaEntrada);
			printf("\n");
			for(int i = 0; i < NUM_FILMES; i++){
				printf("--------\nFila %d - Filme \"%s\":\n", i+1, filmes[i].nome);
				print_clientes(&filasFilmes[i]);
				printf("\n");
			}
			esperar();
			break;

		case 4:
			if (filaEntrada == NULL || fila_vazia(filaEntrada)){
				printf("Não há clientes para quem vender ingressos!\n");
				esperar();
				break;
			}

			int num_pilha;
			printf("Digite o número da pilha de ingressos do filme (1 a %d): ", NUM_FILMES);
			num_pilha = get_opt();

			if (num_pilha < 1 || num_pilha > NUM_FILMES){
				printf("Pilha inexistente. Não foi possível realizar a venda.\n");
				esperar();
				break;
			}
			num_pilha--;
			vender_ingresso(filaEntrada, ingressos+num_pilha, filasFilmes+num_pilha);
			break;

		default:
			printf("Opção inválida! Escolha uma opção válida! (•ˋ _ ˊ•)\n");
			esperar();
			break;
		}
	}

	free(ingressos);

	free(filaEntrada);

	if (filasFilmes != NULL)
		free(filasFilmes);

	return 0;
}

void vender_ingresso(FilaCliente * filaEntrada, PilhaIngresso * pilha, FilaCliente * filaDestino){

	Cliente * cliente = desenfileira(filaEntrada);

	if (cliente == NULL){
		printf("Não há mais clientes.\n");
		return;
	}

	cliente->ingresso = pop(pilha);

	if (cliente->ingresso == NULL){
		printf("Ingressos esgotados! Não foi possível realizar a venda.\nCliente insatisfeito! Você perdeu um cliente!\n");
		print_cliente(cliente);
		esperar();
		return;
	}

	enfileira(filaDestino, cliente);
	printf("Venda realizada!\nCliente: ");
	print_cliente(cliente);
	esperar();
}

FilaCliente * receber_clientes(){
	FilaCliente * fila = malloc(sizeof(FilaCliente));
	init_fila(fila);
	Cliente * novo_cliente = criar_cliente("Ana", 19, NULL);
	enfileira(fila, novo_cliente);
	novo_cliente = criar_cliente("João", 31, NULL);
	enfileira(fila, novo_cliente);
	novo_cliente = criar_cliente("Armando", 76, NULL);
	enfileira(fila, novo_cliente);
	novo_cliente = criar_cliente("Helena", 24, NULL);
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
	if (ingresso == NULL){
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

