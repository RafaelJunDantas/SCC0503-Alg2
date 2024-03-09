#include <stdio.h>
#include <stdlib.h>
#include "bTree.h"

int main()
{
    FILE *dados = inicializeFile("Banco_de_Dados.bin");
    if(dados == NULL){
        return 0;
    }

    FILE *bTree = inicializeBTree("B_Tree.bin");
    if(bTree == NULL){
        return 0;
    }

    int controle = TRUE;
    while(controle != EXIT)
    {
        char escolha[STRING_MAXSIZE];
        scanf(" %s", escolha);
        controle = retornaCodigoComando(escolha, 0);
        escolheAcao(dados, bTree, controle);
    }

    //teste
    //printArqDados(dados);
    //printBTree(bTree);

    fclose(bTree);
    fclose(dados);

    return 0;
}
