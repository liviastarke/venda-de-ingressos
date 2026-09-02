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
	Ingresso filmes[3] = {
		{"Cyrano de Bergerac", 1, hora, 14.99},
		{"Vidas ao Vento",     2, hora, 23.89},
		{"Quarto de Guerra",   3, hora, 19.90},
	};

	PilhaIngresso * ingressos = (PilhaIngresso *) malloc(sizeof(PilhaIngresso)*3);
	//PilhaIngresso * pilhaA  = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	//PilhaIngresso * pilhaB  = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	//PilhaIngresso * pilhaC  = (PilhaIngresso *) malloc(sizeof(PilhaIngresso));
	for(int i = 0; i < 3; i++){
		empilhar_ingressos(&ingressos[i], &filmes[i]);
	}

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
		printf("0. Sair\n1. Abrir cinema para clientes\n2. Exibir pilhas de ingressos\n3. Exibir filas\n4. Vender ingresso\n\n");
		scanf("%d", &opt); // TODO: validação de entrada

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
			for(int i = 0; i < 3; i++){
				printf("--------\nPilha %d:\n", i);
				print_ingressos(&ingressos[i]);
				printf("\n");
			}
			break;
		case 3:
			print_clientes(filaEntrada);
			print_clientes(filaA);
			print_clientes(filaB);
			print_clientes(filaC);
			break;
		case 4:
			int num_pilha;
			scanf("%d", &num_pilha); // TODO: validação de entrada
			vender_ingresso(filaEntrada, &ingressos[num_pilha], filaA); // TODO: trocar filaA por vetor -> fila[num_pilha] correspondente.
			break;
		default:
			printf("Opção inválida! Escolha uma opção válida! (•ˋ _ ˊ•)\n");
			break;
		}
	}
	return 0;
}

/**
 * Como fazer a fila ser decidida de acordo com o ingresso?
 * Devo transformar as filas de filmes separadas em um único vetor?
 */
void vender_ingresso(FilaCliente * filaEntrada, PilhaIngresso * pilha, FilaCliente * filaDestino){
	Cliente * cliente = desenfileira(filaEntrada);
	if (cliente == NULL){
		printf("Não há mais clientes.\n");
		return;
	}
	cliente->ingresso = pop(pilha);
	enfileira(filaDestino, cliente);
	printf("Venda realizada!\n");
	print_cliente(cliente);
}

FilaCliente * receber_clientes(){
	FilaCliente * fila = malloc(sizeof(FilaCliente));
	init_fila(fila);
	Cliente * novo_cliente = criar_cliente("Lívia", 19, INGRESSO_NULO);
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
