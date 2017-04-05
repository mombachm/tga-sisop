/*
 * menu.h
 *
 *  Created on: 04/04/2017
 *      Author: matheus
 */

#ifndef MENU_H_
#define MENU_H_

#define DESTAQUE "-----------"
#define RESPOSTA_INVALIDA -1

struct Menu{
    char titulo[100];
    char** items;
    unsigned int nItems;
};

/**
Função utilizada para exibição do menu a partir da estrutura passada por parâmetro.
Esta função valida a entrada do usuário para a opção escolhida do menu e retorna -1
se um item inválido foi escolhido se não, retorna o número do item escolhido.
*/
int exibeMenu(struct Menu menu){
    printf("\n\t%s %s %s\n", DESTAQUE, menu.titulo, DESTAQUE);
    int i;
    for(i = 0; i < menu.nItems; i++){
        printf("\t%d - %s\n", i+1, menu.items[i]);
    }
    printf("\n\tSelecione uma das opções acima:");
    char* resposta[5];
    gets(resposta);
    int valReposta = atoi(resposta);
    if(valReposta <= 0 || valReposta > menu.nItems){
        return RESPOSTA_INVALIDA;
    }
    return valReposta;
};

#endif /* MENU_H_ */
