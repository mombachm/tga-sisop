#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "menu.h"

#define _POSIX_SOURCE
#define TEMPO_ALARME 5

struct Menu menuPrincipal;


void sig_handler(int signo);
void init_sigaction(struct sigaction* conf_sinal);

pid_t pidGedit = 0, pidFirefox = 0, pidTerminal = 0;

int main(int argc, char argv[]){


//    if (signal(SIGALRM, sig_handler) == SIGCHLD)
  //      printf("\nErro ao tratar o sinal SIGCHLD\n");

    struct sigaction conf_sinal;
    init_sigaction(&conf_sinal);
    conf_sinal.sa_handler = &sig_handler; //acao customizada pelo processo


    if(sigaction(SIGINT, &conf_sinal, NULL)){
        err_exit("erro ao instalar tratador do SIGINT.");
    }


    //conf_sinal.sa_handler = ;
    if(sigaction(SIGALRM, &conf_sinal, NULL)){
        err_exit("erro ao instalar tratador do SIGALARM.");
    }

    //alarm(TEMPO_ALARME);

	//montaMenuPrincipal();

    //if (signal(SIGCHLD, sig_handler) == SIGCHLD)
    //    printf("\nErro ao tratar o sinal SIGCHLD\n");

	//executaMenuPrincipal();
    while(1){
        printf("teste");
        sleep(2);
        printf("teste");
    }

	return EXIT_SUCCESS;
}

void init_sigaction(struct sigaction* conf_sinal) {
    memset(conf_sinal, 0, sizeof(struct sigaction));
    conf_sinal->sa_flags = 0;
    conf_sinal->sa_restorer = NULL;
    sigemptyset(&conf_sinal->sa_mask);
    conf_sinal->sa_handler = NULL;
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


    system("clear");
    resposta = exibeMenu(menuPrincipal);

    int teste;

    switch (resposta){
        case 1: //Web Browser
			printf("Digite o site que gostaria de visitar: \n");
			char strUrl[50];
			scanf("%s", &strUrl);
            pidFirefox = fork();
			if (pidFirefox == 0) { //child process
                execl("/usr/bin/firefox", "firefox", strUrl, NULL);
			} else if (pidFirefox < 0) { //Fork error
                printf("Failed to fork.");
                exit(1);
			} else { //parent process
                printf("(executando, pid=%d)\n", pidFirefox);
			}


			break;
        case 2: //Text Editor
            pidGedit = fork();
			if (pidGedit == 0) { //child process
                execl("/usr/bin/gedit", "gedit", NULL);
			} else if (pidGedit < 0) { //Fork error
                printf("Failed to fork.");
                exit(1);
			} else { //parent process
                printf("(executando, pid=%d)\n", pidGedit);
			}


			break;
        case 3: //Terminal
            pidTerminal = fork();
			if (pidTerminal == 0) { //child process
                execl("/usr/bin/gnome-terminal", "gnome-terminal", NULL);
			} else if (pidTerminal < 0) { //Fork error
                printf("Failed to fork.");
                exit(1);
			} else { //parent process
                printf("(executando, pid=%d)\n", pidTerminal);
			}
			break;
        case 4: //Finalizar Processo
			printf("\n\tQual processo deseja terminar?\n");
			printf("\t1) Web Browser\n");
			printf("\t2) Text Editor\n");
			printf("\t3) Terminal\n");
			scanf(" %d", &teste);
            switch (teste) {
                case 1:
                    killProc(pidFirefox);
                    break;
                case 2:
                    killProc(pidGedit);
                    break;
                case 3:
                    killProc(pidTerminal);
                    break;
                default:
                    printf("\n\tOpção inválida.\n");
                    break;
            }
            getchar();
			break;
        case 5: //Sair
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("\n\tOpção inválida!\n");
            break;
    }
    printf("\n\n");
    printf("\tPressione uma tecla para continuar...");
    getchar();
    executaMenuPrincipal();
}

void sig_handler(int signo) {
    /*if (signo != SIGALRM) alarm(0); //desarma o alarme se foi acionado pelo Ctrl+C
	if (signo == SIGINT)
		executaMenuPrincipal();

    if (signo == SIGCHLD)
		executaMenuPrincipal();*/

    printf("alarme");
}

void err_exit(char* msgerro){
    perror(msgerro);
    exit(EXIT_FAILURE);
}

void killProc(pid_t pid) {
    if (pid > 0) {
        if (kill(pid, SIGTERM) < 0)
            printf("\n\tFalha ao finalizar o processo.\n");
        else
            printf("\n\tProcesso terminado com sucesso.\n");
    } else
        printf("\n\tProcesso inválido.\n");
}

