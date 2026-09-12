#ifndef __CINEMA_H__
#define __CINEMA_H__

#include "ingresso.h"
#include "cliente.h"
#include "pilha.h"
#include "fila.h"

#include <stdlib.h>

// Ingresso * criar_ingresso(char * nome, int sala_de_exibicao, time_t horario_de_exibicao, float preco); // Os ingressos foram criados de outra forma
Cliente * criar_cliente(char * nome, int idade, Ingresso * ingresso);

void vender_ingresso(FilaCliente * filaEntrada, PilhaIngresso * pilha, FilaCliente * filaDestino);

void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme);
void print_ingressos(PilhaIngresso * pilha);
void print_ingresso(Ingresso * ingresso);

FilaCliente * receber_clientes();
void print_clientes(FilaCliente * fila);
void print_cliente(Cliente * cliente);

void check_alloc_err(void * pointer);

#endif

