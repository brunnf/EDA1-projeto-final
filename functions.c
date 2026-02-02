#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

ListaClientes* criar_lista_clientes() {
    ListaClientes *lista = (ListaClientes*) malloc(sizeof(ListaClientes));
    if (lista != NULL) {
        lista->head = NULL;
        lista->qtd = 0;
    }
    return lista;
}

void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void cadastrar_cliente(ListaClientes *lista) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    char buffer_nome[100];

    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("\n--- Novo Cliente ---\n");
    printf("CPF: ");
    ler_texto(novo->cpf, 15);

    printf("Nome: ");
    ler_texto(buffer_nome, 100);
    novo->nome = (char*) malloc(strlen(buffer_nome) + 1);
    strcpy(novo->nome, buffer_nome);

    printf("Email: ");
    ler_texto(novo->email, 100);
    printf("Telefone: ");
    ler_texto(novo->telefone, 20);
    printf("Data Nasc: ");
    ler_texto(novo->data_nasc, 12);

    novo->prox = lista->head;
    lista->head = novo;
    lista->qtd++;

    printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes(ListaClientes *lista) {
    if (lista->head == NULL) {
        printf("\nLista vazia.\n");
        return;
    }

    Cliente *atual = lista->head;
    printf("\n--- Lista de Clientes (%d total) ---\n", lista->qtd);
    while (atual != NULL) {
        printf("CPF: %s | Nome: %s | Email: %s | Tel: %s | Nasc: %s\n", 
               atual->cpf, atual->nome, atual->email, atual->telefone, atual->data_nasc);
        atual = atual->prox;
    }
}

Cliente* buscar_cliente_ptr(ListaClientes *lista, char *cpf_busca) {
    Cliente *atual = lista->head;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf_busca) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void editar_cliente(ListaClientes *lista) {
    char cpf[15];
    printf("Digite o CPF para editar: ");
    ler_texto(cpf, 15);

    Cliente *q = buscar_cliente_ptr(lista, cpf);

    if (q != NULL) {
        char buffer_nome[100];
        printf("Editando dados de: %s\n", q->nome);
        
        printf("Novo Nome: ");
        ler_texto(buffer_nome, 100);
        q->nome = (char*) realloc(q->nome, strlen(buffer_nome) + 1);
        strcpy(q->nome, buffer_nome);

        printf("Novo Email: ");
        ler_texto(q->email, 100);

        printf("Novo Telefone: ");
        ler_texto(q->telefone, 20);

        printf("Nova Data Nasc: ");
        ler_texto(q->data_nasc, 12);

        printf("Dados atualizados com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
}

void remover_cliente(ListaClientes *lista) {
    char cpf_busca[15];
    printf("Digite o CPF para remover: ");
    ler_texto(cpf_busca, 15);

    Cliente *atual = lista->head;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->cpf, cpf_busca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        lista->head = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual->nome);
    free(atual);
    lista->qtd--;
    
    printf("Cliente removido com sucesso.\n");
}

void menu_clientes(ListaClientes *lista) {
    int opcao=-1;
    do {
        printf("\n--- GESTAO DE CLIENTES ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Editar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: cadastrar_cliente(lista); break;
            case 2: listar_clientes(lista); break;
            case 3: editar_cliente(lista); break;
            case 4: remover_cliente(lista); break;
            case 0: break;
            default: printf("\nOpcao invalida! Tente apenas numeros de 0 a 4.\n");
        }
    } while (opcao != 0);
}
