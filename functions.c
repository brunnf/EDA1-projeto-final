#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void formatar_nome(char *nome) {
    int nova_palavra = 1;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isspace(nome[i])) {
            nova_palavra = 1;
        } else if (nova_palavra) {
            nome[i] = toupper(nome[i]);
            nova_palavra = 0;
        } else {
            nome[i] = tolower(nome[i]);
        }
    }
}

void limpar_cpf(char *cpf_destino, char *cpf_origem) {
    int j = 0;
    for (int i = 0; cpf_origem[i] != '\0'; i++) {
        if (isdigit(cpf_origem[i])) {
            cpf_destino[j++] = cpf_origem[i];
        }
    }
    cpf_destino[j] = '\0';
}

int validar_data(char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;
    return 1;
}

void imprimir_cpf_formatado(char *cpf_limpo) {
    if (strlen(cpf_limpo) != 11) {
        printf("%s", cpf_limpo); 
        return;
    }
    printf("%c%c%c.%c%c%c.%c%c%c-%c%c", 
           cpf_limpo[0], cpf_limpo[1], cpf_limpo[2],
           cpf_limpo[3], cpf_limpo[4], cpf_limpo[5],
           cpf_limpo[6], cpf_limpo[7], cpf_limpo[8],
           cpf_limpo[9], cpf_limpo[10]);
}

void cadastrar_cliente(ListaClientes *lista) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    char buffer_temp[100];

    if (novo == NULL) return;
    
    novo->carrinho = NULL;

    printf("\n--- Novo Cliente ---\n");
    printf("CPF: ");
    ler_texto(buffer_temp, 20);
    limpar_cpf(novo->cpf, buffer_temp);

    if (strlen(novo->cpf) != 11) {
        printf("Erro: CPF invalido.\n");
        free(novo);
        return;
    }
    do {
        printf("Nome: ");
        ler_texto(buffer_temp, 100); 
        if (strlen(buffer_temp) == 0) {
            printf("Erro: O nome nao pode ficar em branco!\n");
        }
    } while (strlen(buffer_temp) == 0);

    formatar_nome(buffer_temp);

    novo->nome = (char*) malloc(strlen(buffer_temp) + 1);
    strcpy(novo->nome, buffer_temp);

    printf("Email: ");
    novo->email = (char*) malloc(100 * sizeof(char));
    ler_texto(novo->email, 100);
    novo->email = (char*) realloc(novo->email, strlen(novo->email) + 1);

    printf("Telefone: ");
    ler_texto(novo->telefone, 20);

    do {
        printf("Data Nasc (DD/MM/AAAA): ");
        ler_texto(novo->data_nasc, 12);
        if (!validar_data(novo->data_nasc)) printf("Formato invalido!\n");
        else break;
    } while (1);

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
        printf("CPF: ");
        imprimir_cpf_formatado(atual->cpf); 
        
        printf(" | Nome: %s | Email: %s | Tel: %s | Nasc: %s\n", 
               atual->nome, 
               atual->email, 
               atual->telefone, 
               atual->data_nasc); 
               
        atual = atual->prox;
    }
}

Cliente* buscar_cliente_ptr(ListaClientes *lista, char *cpf_busca) {
    char cpf_limpo[20];
    limpar_cpf(cpf_limpo, cpf_busca);

    Cliente *atual = lista->head;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf_limpo) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void editar_cliente(ListaClientes *lista) {
    char cpf[20];
    char buffer[100]; 
    printf("CPF para editar: ");
    ler_texto(cpf, 20);
    
    Cliente *q = buscar_cliente_ptr(lista, cpf);
    if (q != NULL) {
        printf("--- Editando Cliente (Deixe em branco e aperte Enter para manter o atual) ---\n");

        printf("Nome atual [%s] - Novo: ", q->nome);
        ler_texto(buffer, 100);
        
        if (strlen(buffer) > 0) {
            formatar_nome(buffer);
            q->nome = (char*) realloc(q->nome, strlen(buffer) + 1);
            strcpy(q->nome, buffer);
        }

        printf("Email atual [%s] - Novo: ", q->email);
        ler_texto(buffer, 100);
        if (strlen(buffer) > 0) {
            q->email = (char*) realloc(q->email, strlen(buffer) + 1);
            strcpy(q->email, buffer);
        }

        printf("Telefone atual [%s] - Novo: ", q->telefone);
        ler_texto(buffer, 20);
        if (strlen(buffer) > 0) {
            strcpy(q->telefone, buffer);
        }

        do {
            printf("Data Nasc atual [%s] - Nova (DD/MM/AAAA): ", q->data_nasc);
            ler_texto(buffer, 12);
            if (strlen(buffer) == 0) break; 
            
            if (!validar_data(buffer)) {
                printf("Formato invalido!\n");
            } else {
                strcpy(q->data_nasc, buffer);
                break;
            }
        } while (1);

        printf("Dados atualizados com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
}

void remover_cliente(ListaClientes *lista) {
    char cpf_busca[20];
    char cpf_limpo[15];
    printf("CPF para remover: ");
    ler_texto(cpf_busca, 20);
    limpar_cpf(cpf_limpo, cpf_busca);

    Cliente *atual = lista->head, *anterior = NULL;
    while (atual != NULL && strcmp(atual->cpf, cpf_limpo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return;
    if (anterior == NULL) lista->head = atual->prox;
    else anterior->prox = atual->prox;
    
    ItemCarrinho *item = atual->carrinho;
    while (item != NULL) {
        ItemCarrinho *temp = item;
        item = item->prox;
        free(temp);
    }
    
    free(atual->nome);
    free(atual->email);
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
    char buffer[100];
    printf("Digite o Codigo do produto para editar: ");
    scanf("%d", &cod);
    getchar(); 

    Produto *p = buscar_produto_ptr(lista, cod);

    if (p != NULL) {
        printf("--- Editando Produto (Aperte Enter para manter o atual) ---\n\n");
        
        printf("Nome atual '%s' - Novo: ", p->nome);
        ler_texto(buffer, 100);
        if (strlen(buffer) > 0) {
            p->nome = (char*) realloc(p->nome, strlen(buffer) + 1);
            strcpy(p->nome, buffer);
        }

        printf("Preco atual 'R$ %.2f' - Novo: ", p->preco);
        ler_texto(buffer, 20);
        if (strlen(buffer) > 0) {
            p->preco = atof(buffer); 
        }

        printf("Estoque atual '%d' - Novo: ", p->qtd);
        ler_texto(buffer, 20);
        if (strlen(buffer) > 0) {
            p->qtd = atoi(buffer); 
        }

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
    char cpf[20];
    char cpf_limpo[15];
    printf("\n--- Adicionar Produtos ao Carrinho ---\n");
    printf("Digite o CPF do Cliente comprador: ");
    ler_texto(cpf, 20);
    limpar_cpf(cpf_limpo, cpf);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf_limpo);
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

    prod->qtd -= qtd;

    novo_item->prox = cli->carrinho;
    cli->carrinho = novo_item;

    printf("Produto adicionado ao carrinho de %s!\n", cli->nome);
}

void ver_carrinho(ListaClientes *lista_c) {
    char cpf[20];
    char cpf_limpo[15];
    printf("\n--- Ver Carrinho ---\n");
    printf("Digite o CPF do Cliente: ");
    ler_texto(cpf, 20);
    limpar_cpf(cpf_limpo, cpf);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf_limpo);
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
        
        printf("- COD: %d | %s | Qtd: %d | Unit: R$ %.2f | Sub: R$ %.2f\n", 
               item->produto->cod, item->produto->nome, item->qtd_compra, item->produto->preco, subtotal);
        
        total += subtotal;
        total_itens += item->qtd_compra;
        item = item->prox;
    }
    printf("--------------------------------------------------\n");
    printf("TOTAL DE ITENS: %d\n", total_itens);
    printf("VALOR TOTAL DA COMPRA: R$ %.2f\n", total);
}

void remover_do_carrinho(ListaClientes *lista_c) {
    char cpf[20];
    char cpf_limpo[15];
    printf("\n--- Remover Item do Carrinho ---\n");
    printf("Digite o CPF do Cliente: ");
    ler_texto(cpf, 15);
    limpar_cpf(cpf_limpo, cpf);

    Cliente *cli = buscar_cliente_ptr(lista_c, cpf_limpo);
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

    atual->produto->qtd += atual->qtd_compra;

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

void liberar_sistema(ListaClientes *lista_c, ListaProdutos *lista_p) {
    Cliente *atual_c = lista_c->head;
    while (atual_c != NULL) {
        Cliente *temp_c = atual_c;
        atual_c = atual_c->prox;

        ItemCarrinho *item = temp_c->carrinho;
        while (item != NULL) {
            ItemCarrinho *temp_i = item;
            item = item->prox;
            free(temp_i);
        }

        free(temp_c->nome);
        free(temp_c->email);
        free(temp_c);
    }
    free(lista_c); 

    Produto *atual_p = lista_p->head;
    while (atual_p != NULL) {
        Produto *temp_p = atual_p;
        atual_p = atual_p->prox;
        
        free(temp_p->nome); 
        free(temp_p);       
    }
    free(lista_p); 

    printf("Memoria liberada com sucesso. Sistema encerrado.\n");
}