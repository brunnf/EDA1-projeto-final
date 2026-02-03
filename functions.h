#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

void ler_texto(char *buffer, int tamanho);
void formatar_nome(char *nome);
void limpar_cpf(char *cpf_destino, char *cpf_origem);
int validar_data(char *data);
void imprimir_cpf_formatado(char *cpf_limpo);

ListaClientes* criar_lista_clientes();
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

void adicionar_ao_carrinho(ListaClientes *lista_c, ListaProdutos *lista_p);
void ver_carrinho(ListaClientes *lista_c);
void remover_do_carrinho(ListaClientes *lista_c);
void menu_compras(ListaClientes *lista_c, ListaProdutos *lista_p);
void menu_principal(ListaClientes *lista_c, ListaProdutos *lista_p);

void liberar_sistema(ListaClientes *lista_c, ListaProdutos *lista_p);

void limpar_tela();
void esperar(float segundos);
void pausar_enter();

#endif