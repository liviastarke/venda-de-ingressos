#ifndef __CINEMA_H__
#define __CINEMA_H__

#include "ingresso.h"
#include "cliente.h"
#include "pilha.h"
#include "fila.h"

void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme);
void print_ingressos(PilhaIngresso * pilha);
void print_ingresso(Ingresso * ingresso);

void esperar();
void check_alloc_err(void * pointer);

#endif

