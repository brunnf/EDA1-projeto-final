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

    novo->carrinho = NULL;

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

ListaProdutos* criar_lista_produtos() {
    ListaProdutos *lista = (ListaProdutos*) malloc(sizeof(ListaProdutos));
    if (lista != NULL) {
        lista->head = NULL;
        lista->qtd = 0;
    }
    return lista;
}

void cadastrar_produto(ListaProdutos *lista) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    char buffer_nome[100];

    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("\n--- Novo Produto ---\n");
    printf("Codigo (numero unico): ");
    scanf("%d", &novo->cod);
    getchar(); 

    if (buscar_produto_ptr(lista, novo->cod) != NULL) {
        printf("Erro: Ja existe um produto com este codigo.\n");
        free(novo);
        return;
    }

    printf("Nome do Produto: ");
    ler_texto(buffer_nome, 100);

    novo->nome = (char*) malloc(strlen(buffer_nome) + 1);
    strcpy(novo->nome, buffer_nome);

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &novo->qtd);
    getchar(); 

    novo->prox = lista->head;
    lista->head = novo;
    lista->qtd++;

    printf("Produto cadastrado com sucesso!\n");
}

void listar_produtos(ListaProdutos *lista) {
    if (lista->head == NULL) {
        printf("\nLista de produtos vazia.\n");
        return;
    }

    Produto *atual = lista->head;
    printf("\n--- Estoque de Produtos (%d itens) ---\n", lista->qtd);
    while (atual != NULL) {
        printf("COD: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n", 
               atual->cod, atual->nome, atual->preco, atual->qtd);
        atual = atual->prox;
    }
}

Produto* buscar_produto_ptr(ListaProdutos *lista, int cod) {
    Produto *atual = lista->head;
    while (atual != NULL) {
        if (atual->cod == cod) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void editar_produto(ListaProdutos *lista) {
    int cod;
    printf("Digite o Codigo do produto para editar: ");
    scanf("%d", &cod);
    getchar(); 

    Produto *p = buscar_produto_ptr(lista, cod);

    if (p != NULL) {
        char buffer_nome[100];
        printf("Editando produto: %s (Preco atual: %.2f)\n", p->nome, p->preco);
        
        printf("Novo Nome: ");
        ler_texto(buffer_nome, 100);

        p->nome = (char*) realloc(p->nome, strlen(buffer_nome) + 1);
        strcpy(p->nome, buffer_nome);

        printf("Novo Preco: ");
        scanf("%f", &p->preco);

        printf("Nova Quantidade: ");
        scanf("%d", &p->qtd);
        getchar();

        printf("Produto atualizado com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void remover_produto(ListaProdutos *lista) {
    int cod;
    printf("Digite o Codigo do produto para remover: ");
    scanf("%d", &cod);
    getchar();

    Produto *atual = lista->head;
    Produto *anterior = NULL;

    while (atual != NULL && atual->cod != cod) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
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
    
    printf("Produto removido com sucesso.\n");
}

void menu_produtos(ListaProdutos *lista) {
    int opcao = -1;
    do {
        printf("\n--- GESTAO DE PRODUTOS ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Editar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: cadastrar_produto(lista); break;
            case 2: listar_produtos(lista); break;
            case 3: editar_produto(lista); break;
            case 4: remover_produto(lista); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

void adicionar_ao_carrinho(ListaClientes *lista_c, ListaProdutos *lista_p) {
    char cpf[15];
    printf("\n--- Adicionar Produtos ao Carrinho ---\n");
    printf("Digite o CPF do Cliente comprador: ");
    ler_texto(cpf, 15);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf);
    if (cli == NULL) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    listar_produtos(lista_p);
    
    int cod, qtd;
    printf("\nDigite o CODIGO do produto que deseja comprar: ");
    scanf("%d", &cod);
    getchar();

    Produto *prod = buscar_produto_ptr(lista_p, cod);
    if (prod == NULL) {
        printf("Produto nao existe!\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &qtd);
    getchar();

    if (qtd > prod->qtd) {
        printf("Erro: Estoque insuficiente! Disponivel: %d\n", prod->qtd);
        return;
    }

    ItemCarrinho *novo_item = (ItemCarrinho*) malloc(sizeof(ItemCarrinho));
    if (novo_item == NULL) {
        printf("Erro de memoria.\n");
        return;
    }

    novo_item->produto = prod; 
    novo_item->qtd_compra = qtd;

    novo_item->prox = cli->carrinho;
    cli->carrinho = novo_item;

    printf("Produto adicionado ao carrinho de %s!\n", cli->nome);
}

void ver_carrinho(ListaClientes *lista_c) {
    char cpf[15];
    printf("\n--- Ver Carrinho ---\n");
    printf("Digite o CPF do Cliente: ");
    ler_texto(cpf, 15);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf);
    if (cli == NULL) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    if (cli->carrinho == NULL) {
        printf("O carrinho de %s esta vazio.\n", cli->nome);
        return;
    }

    printf("\nCarrinho de compras de: %s\n", cli->nome);
    printf("--------------------------------------------------\n");
    
    ItemCarrinho *item = cli->carrinho;
    float total = 0.0;
    int total_itens = 0;

    while (item != NULL) {
        float subtotal = item->produto->preco * item->qtd_compra;
        
        printf("- %s | Qtd: %d | Unit: R$ %.2f | Sub: R$ %.2f\n", 
               item->produto->nome, item->qtd_compra, item->produto->preco, subtotal);
        
        total += subtotal;
        total_itens += item->qtd_compra;
        item = item->prox;
    }
    printf("--------------------------------------------------\n");
    printf("TOTAL DE ITENS: %d\n", total_itens);
    printf("VALOR TOTAL DA COMPRA: R$ %.2f\n", total);
}

void remover_do_carrinho(ListaClientes *lista_c) {
    char cpf[15];
    printf("\n--- Remover Item do Carrinho ---\n");
    printf("Digite o CPF do Cliente: ");
    ler_texto(cpf, 15);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf);
    if (cli == NULL) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    if (cli->carrinho == NULL) {
        printf("Carrinho vazio.\n");
        return;
    }

    ver_carrinho(lista_c); 

    int cod;
    printf("\nDigite o CODIGO do produto para remover do carrinho: ");
    scanf("%d", &cod);
    getchar();

    ItemCarrinho *atual = cli->carrinho;
    ItemCarrinho *anterior = NULL;

    while (atual != NULL && atual->produto->cod != cod) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Item nao encontrado no carrinho.\n");
        return;
    }

    if (anterior == NULL) {
        cli->carrinho = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual); 
    printf("Item removido do carrinho!\n");
}

void menu_compras(ListaClientes *lista_c, ListaProdutos *lista_p) {
    int opcao = -1;
    do {
        printf("\n--- MODO COMPRA (CARRINHO) ---\n");
        printf("1. Adicionar Produto ao Carrinho\n");
        printf("2. Ver Carrinho / Finalizar\n");
        printf("3. Remover Item do Carrinho\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: adicionar_ao_carrinho(lista_c, lista_p); break;
            case 2: ver_carrinho(lista_c); break;
            case 3: remover_do_carrinho(lista_c); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menu_principal(ListaClientes *lista_c, ListaProdutos *lista_p) {
    int opcao = -1;

    do {
        printf("\n=============================\n");
        printf("      SISTEMA DE GESTAO      \n");
        printf("=============================\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("2. Gerenciamento de Produtos\n");
        printf("3. Modo Compra (Carrinho)\n");
        printf("0. Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: 
                menu_clientes(lista_c); 
                break;
            case 2: 
                menu_produtos(lista_p); 
                break;
            case 3:
                menu_compras(lista_c, lista_p);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}