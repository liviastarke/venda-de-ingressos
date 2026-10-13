# Sistema de venda de ingressos

Trabalho para a disciplina de Estrutura de Dados e Algoritmos. Abaixo são listados os requisitos e instruções 
para compilação. Detalhes sobre a funcionalidade, estrutura dos arquivos e implementação, encontram-se em 
*relatorio.md*.

## Requisitos

- [x] Pilha

- [x] Fila

- [x] Opções de pilha dentro do programa

- [x] Opções de fila dentro do programa

- [x] Makefile para facilitar minha vida

- [x] Completar operações

- [x] Terminar a interface


## Instruções de compilação

Compilar e rodar (inclui símbolos para debug):

```bash
make
./C-cinema
```

O arquivo binário C-cinema é excluído pelo .gitignore. Para excluir os arquivos de compilação:

```bash
make clean
```

O Makefile ainda é bem básico, a ser melhorado. Para compilar sem a flag "-g" rodar `make CFLAGS=""`

Mais detalhes sobre [Make e Makefile aqui](https://www.gnu.org/software/make/manual/make.html).

