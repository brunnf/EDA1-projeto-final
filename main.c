#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

int main() {
    ListaClientes *meus_clientes = criar_lista_clientes();
    ListaProdutos *meus_produtos = criar_lista_produtos();

    menu_principal(meus_clientes, meus_produtos);

    liberar_sistema(meus_clientes, meus_produtos);

    return 0;
}