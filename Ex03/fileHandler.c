#include <stdio.h>
#include <string.h>
#include "fileHandler.h"
#include "registro.h"

/*------------------------------------------------------------------*/
int retornaCodigoComando(char comando[10], int contador){

  if(strcmp(comando, "insert") == 0){
    return INSERT;
  }

  else if(strcmp(comando, "search") == 0){
      if(contador > 0)
      {
          printf("\n");
      }
    return SEARCH;
  }

  else if(strcmp(comando, "update") == 0){
      if(contador > 0)
      {
          printf("\n");
      }
      return UPDATE;
  }

  else{
    return EXIT;
  }
}

/*------------------------------------------------------------------*/
/*funcao INSERT*/
/*
Dividida em 3 funcoes:
1)recebe os dados
2)escreve os dados no arquivo de dados
3)escreve no arquivo da bTree
*/
void recebeEntradas(FILE *arqDados, FILE *arqIndice, bool update)
{
    REGISTRO aluno = regInsert();

    //teste
    //regPrint(&aluno);
    if(update == FALSE)
        jogaEntradasNumBinario(arqDados, arqIndice, &aluno);

    else
    {
        long regRRN = searchRRNbTree(arqIndice, arqDados, aluno.nUSP);

        if(regRRN != NAO_EXISTE)
        {
            fseek(arqDados, regRRN, SEEK_SET);
            fwrite(&aluno, sizeof(REGISTRO), 1, arqDados);
        }
    }
}

void jogaEntradasNumBinario(FILE *arqDados, FILE *arqIndice, REGISTRO *aluno)
{
    keyAndRRNOnPage keyRRN;
    keyRRN.key = aluno->nUSP;

    fseek(arqDados, 0, SEEK_END);
    keyRRN.RRN = ftell(arqDados);

    fwrite(aluno, sizeof(REGISTRO), 1, arqDados);
    insertNewReg(arqIndice, keyRRN);
}

void escolheAcao(FILE *arqDados, FILE *arqIndice, int codigoComando)
{
    switch(codigoComando){
        case INSERT:
            recebeEntradas(arqDados, arqIndice, FALSE);
            break;
        case SEARCH:
            searchBTree(arqIndice, arqDados, FALSE);
            break;
        case UPDATE:
            recebeEntradas(arqDados, arqIndice, TRUE);
            break;
        case EXIT:
            return;
    }
}

long fileSize(FILE *arq){           //retorna o tamanho do arquivo

    fseek(arq, 0, SEEK_END);

    return ftell(arq);
}


void printArqDados(FILE *arq){      //printa o arquivo de dados

    long fim = fileSize(arq);

    fseek(arq, 0, SEEK_SET);

    while(ftell(arq) != fim){
        REGISTRO aluno;
        fread(&aluno, sizeof(REGISTRO), 1, arq);
        regPrint(&aluno);
    }
}

FILE *inicializeFile(char *fileName){       //inicializa arquivo

    FILE *arq = fopen(fileName, "wb+");

    return arq;
}

REGISTRO findReg_ByItsRRN(FILE *arqDados, long RRN)
{
    REGISTRO registro;

    fseek(arqDados, RRN, SEEK_SET);
    fread(&registro, sizeof(REGISTRO), 1, arqDados);

    return registro;
}
