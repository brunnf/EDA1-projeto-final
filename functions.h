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

#endif
