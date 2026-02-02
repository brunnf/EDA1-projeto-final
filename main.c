#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

int main() {
    ListaClientes *meus_clientes = criar_lista_clientes();
    menu_clientes(meus_clientes);
    free(meus_clientes);
    return 0;
}