#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Cliente {
    char cpf[15];
    char *nome;
    char email[100];
    char telefone[20];
    char data_nasc[12];
    struct Cliente *prox;
} Cliente;

typedef struct ListaClientes {
    Cliente *head;
    int qtd;
} ListaClientes;

typedef struct Produto {
    int cod;
    char *nome;
    float preco;
    int qtd;
    struct Produto *prox;
} Produto;

#endif