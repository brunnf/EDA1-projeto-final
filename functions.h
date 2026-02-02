#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

ListaClientes* criar_lista_clientes();
void ler_texto(char *buffer, int tamanho);
void cadastrar_cliente(ListaClientes *lista);
void listar_clientes(ListaClientes *lista);
Cliente* buscar_cliente_ptr(ListaClientes *lista, char *cpf_busca);
void editar_cliente(ListaClientes *lista);
void remover_cliente(ListaClientes *lista);
void menu_clientes(ListaClientes *lista);
ListaProdutos* criar_lista_produtos();
void cadastrar_produto(ListaProdutos *lista);
void listar_produtos(ListaProdutos *lista);
Produto* buscar_produto_ptr(ListaProdutos *lista, int cod);
void editar_produto(ListaProdutos *lista);
void remover_produto(ListaProdutos *lista);
void menu_produtos(ListaProdutos *lista);

#endif
