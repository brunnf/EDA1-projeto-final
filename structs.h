#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

typedef struct Cliente
{
    int cpf;
    char *nome;
    int telefone;
} cliente;

typedef struct Produto
{
    int cod;
    char *nome;
    int preco;
}Produto;



#endif