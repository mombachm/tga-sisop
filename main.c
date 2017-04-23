#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "menu.h"

struct Menu menuPrincipal;



int main(int argc, char argv[]){
	montaMenuPrincipal();
	executaMenuPrincipal();

	return EXIT_SUCCESS;
}

void sig_handler(int signo);


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

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\nNão consegui pegar o SIGINT\n");

    system("clear");
    resposta = exibeMenu(menuPrincipal);
    switch (resposta){
        case 1: //Web Browser
			printf("Digite o site que gostaria de visitar: \n");
			char* s;
			scanf("%s", s);
			execl("/usr/bin/firefox", "firefox", s, NULL);
			pid_t firefox = fork(); // não tá funcionando
			printf("(executando, pid=%d)\n", firefox);
			break;
        case 2: //Text Editor
			execl("/usr/bin/gedit", "gedit", NULL);
			pid_t gedit = fork(); // não tá funcionando
			printf("(executando, pid=%d)\n", gedit);
			break;
        case 3: //Terminal
			system("gnome-terminal");
			pid_t terminal = fork(); // não tá funcionando
			printf("(executando, pid=%d)\n", terminal);
			break;
        case 4: //Finalizar Processo
			printf("Qual processo deseja terminar?\n");
			printf("1) Web Browser\n");
			printf("2) Text Editor\n");
			printf("3) Terminal\n");

			int proc;
			scanf("%d", &proc);
			if (proc == 1)
				kill(firefox, SIGTERM);
			if (proc == 2)
				kill(gedit, SIGTERM);
			if (proc == 3)
				kill(terminal, SIGTERM);

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

void sig_handler(int signo) {
	if (signo == SIGINT)
		printf("Relebeu sinal.");
}

