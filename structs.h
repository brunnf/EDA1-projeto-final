#ifndef STRUCTS_H
#define STRUCTS_H



typedef struct Cliente {
    char cpf[20];
    char *nome;
    char *email;
    char telefone[20];
    char data_nasc[12];
    struct ItemCarrinho *carrinho;
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

typedef struct ListaProdutos {
    Produto *head;
    int qtd;
} ListaProdutos;

typedef struct ItemCarrinho {
    struct Produto *produto;
    int qtd_compra;          
    struct ItemCarrinho *prox;
} ItemCarrinho;

#endif