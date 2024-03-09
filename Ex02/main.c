#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileHandler.h"

int main()
{
    FILE *arqDados = fopen("arquivoBinario.bin", "wb+");

    if(arqDados != NULL){

        FILE *arqIndice = fopen("arquivoIndice.txt", "wb+");

        if(arqIndice != NULL){
            fseek(arqDados, 0, SEEK_SET);

            int codigoComando = 0;

            while(codigoComando != EXIT)
            {
                char comando[10];
                scanf("%s", comando);

                codigoComando = retornaCodigoComando(comando);
                escolheAcao(arqDados, arqIndice, codigoComando);
            }
        }

        else{
            printf("ERRO ao abrir\n\n");
        }
    }

    else{
        printf("ERRO ao abrir\n\n");
    }

    fclose(arqDados);

    return 0;
}
