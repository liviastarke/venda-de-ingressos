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


## Visão de Alto Nível do Cinema

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


## Pilha

As funções relacionadas à pilha estão em *pilha.c*. A pilha foi implementada como visto em aula, mas com o 
tipo `Ingresso *` em vez de primitivos. Tanto a pilha quanto a fila têm o mesmo tamanho máximo (20 elementos) 
definido em uma constante no *header file* correspondente (nomeados STACK\_SIZE e QUEUE\_SIZE, para ter alguma 
consistência nos nomes e ser mais intuitivo). Para definir o tipo `Ingresso *`, separei a definição da *struct 
Ingresso* em outro *.h*, para ter a referência tanto em *cinema.h* quanto em *pilha.h*. (Mais tarde fiz o mesmo 
para a *struct Cliente* para ter referências em *cinema.h* e em *fila.h*.) Vale notar que os *header files* já 
precisam conhecer essas *structs* para as assinaturas das funções. Tomei o cuidado de usar `#ifndef` para 
garantir que não teria problemas com redefinições de tipos e funções.


## Fila

As funções relacionadas à fila estão em *fila.c*. A fila circular foi implementada como visto em sala de aula. 
Vi por bem armazenar o tamanho da fila na estrutura (que chamei de *qtd*), embora já tivesse feito uma função 
para calcular o tamanho com base nos valores *front* e *back* de início e fim da fila. Acredito que seja 
possível implementar a fila circular sem armazenar a quantidade de elementos nela, mas me pareceu mais fácil 
ter as coisas definidas dessa forma.

O tipo *FilaCliente* armazena apenas os ponteiros para *Cliente*. Achei apropriado porque fazia muitas 
operações com ponteiros, mas isso também torna o tipo *FilaCliente* menor. Pensei em usar o tipo de ponteiro 
genérico `void *` que implementei como exercício das aulas, por ser mais flexível, mas acabei usando `Cliente *` 
para manter a consistência com a pilha que eu já tinha implementado. Além do mais, como é um programa pequeno 
é mais fácil definir um vetor do tipo `Cliente *` do que ficar fazendo *cast* entre tipos de ponteiro.


## IO

A última coisa que fiz foi substituir todos os *scanf* por uma função personalizada que tratasse erros de 
entrada inválida, que chamei de *get_opt* com a ideia de que ela é usada para *get* da opção entrada pelo 
usuário. A função *esperar* foi implementada bem antes durante o desenvolvimento e inicialmente estava no 
*cinema.c*, e serve só para que a saída seja mais limpa e o programa seja mais interativo. Movi para *io.c* 
quando escrevi *get_opt*. Obviamente *io.c* é acompanhado pelo seu próprio *header file* *io.h*.

A escolha de separar essas duas funções em especial foi inspirada por um Estudo Dirigido anterior em que 
separei um arquivo *inputs.h* para funções de entrada. Sinto que faz muito sentido separar, apesar de serem 
funções curtas, por serem já duas. Tenho achado apropriado ter funções de entrada separadas do resto.

Me pergunto se seria apropriado colocar as funções de *print* nesses arquivos, mas isso envolveria incluir 
as *structs* *Cliente*, *FilaCliente*, *Ingresso* e *PilhaIngresso* aqui também. Me pareceu demais por agora.


## Makefile

Depois de escrever o terceiro arquivo *.c* comecei a ter problemas para digitar o comando de compilação, então 
fui pesquisar as regras básicas para usar o *make*. Escrevi um *Makefile* básico para recompilar o projeto (com 
a *flag* *-g* por default, porque eu sempre tinha que passar alguma coisa no *gdb* para debugging). Também 
adicionei a opção *make clean* para excluir os arquivos objeto e a compilação. Para compilar sem os símbolos 
para depuração, basta rodar `make CFLAGS=""` em vez de `make`.


