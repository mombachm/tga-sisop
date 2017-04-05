#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu.h"

struct Menu menuPrincipal;

int main(int argc, char argv[]){
	montaMenuPrincipal();
	executaMenuPrincipal();

	return EXIT_SUCCESS;
}

/**
Função que inicializa o menu principal, montando o título e seus menus.
*/
void montaMenuPrincipal(){
    unsigned char nItemsMenuPrincipal = 5;
    char** itemsMenuPrincipal = malloc(nItemsMenuPrincipal * sizeof(char*));
    itemsMenuPrincipal[0] = "Web Browser";
    itemsMenuPrincipal[1] = "Text Editor";
    itemsMenuPrincipal[2] = "Terminal";
    itemsMenuPrincipal[3] = "Finalizar Processo";
    itemsMenuPrincipal[4] = "Sair";

    strcpy(menuPrincipal.titulo, "Applications Menu");
    menuPrincipal.items = itemsMenuPrincipal;
    menuPrincipal.nItems = nItemsMenuPrincipal;
};


/**
Função que controla o menu principal da aplicação.
Nesta função são tratados as ações de acordo com a opção escolhida pelo usuário.
*/
void executaMenuPrincipal(){
    int resposta;
    unsigned int id;

    system("clear");
    resposta = exibeMenu(menuPrincipal);
    switch (resposta){
        case 1: //Web Browser

            break;
        case 2: //Text Editor

            break;
        case 3: //Terminal

            break;
        case 4: //Finalizar Processo

            break;
        case 5: //Sair

            break;
        default:
            printf("\n\tOpção inválida!\n");
            break;
    }
    printf("\n\n");
    printf("\tPressione uma tecla para continuar...");
    getchar();
    return executaMenuPrincipal();
}
