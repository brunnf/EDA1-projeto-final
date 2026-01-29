#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

typedef struct Cliente
{
    int cpf;
    char *nome;
    int telefone;
    struct Cliente * prox;
} cliente;

typedef struct Produto
{
    int cod;
    char *nome;
    int preco;
    struct Produto * prox;
} produto;



#endif