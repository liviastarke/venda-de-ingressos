#ifndef __CINEMA_H__
#define __CINEMA_H__

#include "ingresso.h"
#include "cliente.h"
#include "pilha.h"

void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme);

void print_ingressos(PilhaIngresso * pilha);
void print_ingresso(Ingresso * ingresso);

#endif

