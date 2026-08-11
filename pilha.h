#ifndef __PILHA_H__
#define __PILHA_H__

#define STACK_SIZE 20

// Estrutura Pilha: LIFO - Last In, First Out
typedef struct{
	Ingresso * items[STACK_SIZE];
	int top;
}PilhaIngresso;

int pilha_vazia(PilhaIngresso * stack){
	return (stack->top == -1);
}

int pilha_cheia(PilhaIngresso * stack){
	return stack->top == STACK_SIZE - 1;
}

// Empilhar
int push(PilhaIngresso * stack, Ingresso * item){
	if (pilha_cheia(stack)){
		printf("PUSH FAILED: pilha cheia\n");
		return -1;
	}
	stack->items[++stack->top] = item;
	return 0;
}

// Desempilhar
Ingresso * pop(PilhaIngresso * stack){
	if (pilha_vazia(stack)){
		printf("POP FAILED: pilha vazia\n");
		return NULL;
	}
	return stack->items[stack->top--];
}

void init_stack(PilhaIngresso * stack){
	stack->top = -1;
}

// Retorna o valor no topo da pilha sem retirá-lo de lá.
Ingresso * top(PilhaIngresso * stack){
        if (pilha_vazia(stack)){
                printf("TOP FAILED: pilha vazia\n");
                return NULL;
        }
        return stack->items[stack->top];
}

void print_stack(PilhaIngresso * stack){
	for (int i = 0; i < STACK_SIZE; i++){
		if (i <= stack->top){
			printf("Stack item [%d]: %p\n", i, stack->items[i]);
		}
	}
}

#endif

