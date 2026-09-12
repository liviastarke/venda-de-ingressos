# Relatório: Estudo Dirigido de Estrutura de Dados

## Overview da Funcionalidade do Programa

Implementei um sistema de venda de ingressos de acordo com as especificações, com ligeiras modificações. 
O programa exibe um menu (implementado via *switch-case* no *main*) com as seguintes opções:

> 0. Sair
> 1. Abrir cinema para clientes
> 2. Exibir pilhas de ingressos
> 3. Exibir filas
> 4. Vender ingresso

Inicialmente as filas estão vazias e as pilhas de ingressos já estão cheias, cada uma com ingressos para o 
mesmo filme. Há o mesmo número de filmes que de pilhas de ingressos e de filas para os filmes. Imagina-se 
também uma outra fila chamada *filaEntrada*, que é preenchida ao escolher a opção "1. Abrir cinema para 
clientes", com alguns poucos clientes predefinidos.

Só é possível vender ingressos se houver alguém na *filaEntrada*. Então, será pedido o número da pilha de 
ingressos de onde retirar o ingresso vendido. Após a venda é mostrado o par cliente-ingresso na tela, e 
esse cliente move-se para a fila correspondente ao ingresso do filme requisitado.


## Visão de alto nível do cinema

O arquivo *cinema.c* e seu *header file* definem as funções de mais alto nível do programa. Primeiramente, 
são incluídas as *structs* centrais *Ingresso*, *Cliente*, *PilhaIngresso* e *FilaCliente*:

```c
#include "ingresso.h"
#include "cliente.h"
#include "pilha.h"
#include "fila.h"
```

O arquivo *cinema.c* é responsável pelas operações de imprimir cada uma dessas estruturas na tela 
devidamente formatadas nas funções:

```c
void print_ingressos(PilhaIngresso * pilha);
void print_ingresso(Ingresso * ingresso);
void print_clientes(FilaCliente * fila);
void print_cliente(Cliente * cliente);
```

As funções de *print* recebem ponteiros como argumentos por motivos de eficiência de espaço, já que 
um ponteiro é menor que a *struct* inteira. Padronizei os nomes de funções do programa em *snake case*, 
e fiz distinção entre as formas singular e plural *print_cliente* e *print_clientes* para ter nomes 
de funções mais facilmente memorizáveis e ainda razoavelmente curtos.

As funcionalidades mais importantes para o menu principal foram escritas nas funções:

```c
void empilhar_ingressos(PilhaIngresso * pilha, Ingresso * filme);
Cliente * criar_cliente(char * nome, int idade, Ingresso * ingresso);
FilaCliente * receber_clientes();
void vender_ingresso(FilaCliente * filaEntrada, PilhaIngresso * pilha, FilaCliente * filaDestino);
```

Criei *empilhar_ingressos* para inicializar as pilhas de ingressos. Os ingressos em si são criados 
*hardcoded* em um vetor chamado *filmes*, que é relativamente simples de mudar, por isso não implementei 
uma função *criar_ingresso*, correspondente a *criar_cliente*. Adicionar um filme envolveria mudar a 
constante NUM\_FILMES e adicionar nome do filme, sala, hora e preço do ingresso no vetor *filmes*. Já 
para adicionar um cliente, como clientes devem ser mais únicos que filmes, um vetor não me pareceu 
apropriado. Em vez disso, porque alocar memória para um *Cliente* e inicializá-lo envolvia mais operações 
complicadas (como *strcpy*), eu criei essa função *criar_cliente* que aloca, inicializa, e retorna um 
ponteiro para meu novo cliente.

*receber_clientes* cria a fila de entrada (e retorna seu ponteiro) após inicializá-la com clientes criados 
via chamadas de *criar_cliente*. Os nomes e idades estão *hardcoded* aqui.

Por fim, *vender_ingresso* é responsável por desenfileirar o primeiro cliente da fila de entrada e 
colocá-lo na fila do filme após lhe dar um ingresso. É uma função simples graças às abstrações de enfileira, 
desenfileira e desempilha, implementados nos arquivos da fila e da pilha.

Uma última função que foi definida aqui porque não se encaixava na proposta de nenhum dos outros 
arquivos *.c* e seria um despedício criar um outro arquivo para ela foi `void check_alloc_err(void * pointer)`
, que é muito útil para usar em conjunto com *malloc* para checar se não ocorreram erros de alocação de 
memória. Escrevi ela há alguns meses e reaproveito sempre.

## Fila
## Pilha
## IO
## Makefile

