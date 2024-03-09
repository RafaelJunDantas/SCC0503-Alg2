#include "fileHandler.h"
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------*/
int retornaCodigoComando(char comando[10]){

  if(strcmp(comando, "insert") == 0){
    return INSERT;
  }

  else if(strcmp(comando, "search") == 0){
    return SEARCH;
  }

  else if(strcmp(comando, "delete") == 0){
    return DELETE;
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
3)escreve os indices no arquivo de indices
*/
void recebeEntradas(FILE *arqDados, FILE *arqIndice)
{
    DADOS_Aluno aluno;

    char charBuffer = 0;

    scanf("%d", &aluno.nUSP);
    scanf("%*c");

    for(int i = 0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if(charBuffer == VIRGULA)
        {
            aluno.Nome[i] = '\0';
            break;
        }
        aluno.Nome[i] = charBuffer;
    }
    //scanf(" %[^(\r|\n)]s", aluno.Nome);

    for(int i=0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if(charBuffer == VIRGULA)
        {
            aluno.SobreNome[i] = '\0';
            break;
        }
        aluno.SobreNome[i] = charBuffer;
    }
    //scanf(" %[^(\r|\n)]s", aluno.SobreNome);

    for(int i=0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if(charBuffer == VIRGULA)
        {
            aluno.Curso[i] = '\0';
            break;
        }
        aluno.Curso[i] = charBuffer;
    }
    //scanf(" %[^(\r|\n)]s", aluno.Curso);

    scanf("%f", &aluno.Nota);
    //scanf("%*c");

    if(chaveExiste(arqIndice, aluno.nUSP) == NAO_EXISTE){
        jogaEntradasNumBinario(arqDados, arqIndice, aluno);
    }

    else{
        printf("Registro ja existe!\n");
    }
}

void jogaEntradasNumBinario(FILE *arqDados, FILE *arqIndice, DADOS_Aluno aluno)
{
    fseek(arqDados, 0, SEEK_END);

    escreveIndice(arqIndice, aluno.nUSP, ftell(arqDados));

    fwrite(&aluno.nUSP, sizeof(int), 1, arqDados);
    fwrite(aluno.Nome, sizeof(char), STRING_MAXSIZE, arqDados);
    fwrite(aluno.SobreNome, sizeof(char), STRING_MAXSIZE, arqDados);
    fwrite(aluno.Curso, sizeof(char), STRING_MAXSIZE, arqDados);
    fwrite(&aluno.Nota, sizeof(float), 1, arqDados);

    /*teste
    printaAluno(aluno);
    */

}

void escreveIndice(FILE *arqIndice, int chaveRegistro, int posicaoRegistro){

    fseek(arqIndice, 0, SEEK_END);

    fprintf(arqIndice, "%d", chaveRegistro);
    fprintf(arqIndice, "|");
    fprintf(arqIndice, "%d", posicaoRegistro);
    fprintf(arqIndice, "|");

  /*teste
  printf("%d %d\n", chaveRegistro, posicaoRegistro);
  */
}

/*------------------------------------------------------------------*/
/*funcao SEARCH*/
/*
Dividida em 2 funcoes:
1)verifica se a chave existe ou se foi apagada
2)receve a chave e le do arquivo de dados
*/
int chaveExiste(FILE *arqIndice, int chave){

    fseek(arqIndice, 0, SEEK_SET);

    while(!feof(arqIndice)){
        int chaveLida;
        fscanf(arqIndice, "%d", &chaveLida);

        char buffer;
        fscanf(arqIndice, "%c", &buffer);

        int posicaoRegistro;
        fscanf(arqIndice, "%d", &posicaoRegistro);

        fscanf(arqIndice, "%c", &buffer);

        if(chaveLida == chave){
            return posicaoRegistro;
        }
    }

    return NAO_EXISTE;
}

void procuraAluno(FILE *arqDados, FILE *arqIndice){

    int chaveProcurada;
    scanf("%d", &chaveProcurada);

    int posicaoRegistro = chaveExiste(arqIndice, chaveProcurada);

    if(posicaoRegistro == APAGADO || posicaoRegistro == NAO_EXISTE){
        printf("Registro nao encontrado!\n");
    }

    else{
        fseek(arqDados, posicaoRegistro, SEEK_SET);

        DADOS_Aluno aluno;

        fread(&aluno.nUSP, sizeof(int), 1, arqDados);
        fread(aluno.Nome, sizeof(char), STRING_MAXSIZE, arqDados);
        fread(aluno.SobreNome, sizeof(char), STRING_MAXSIZE, arqDados);
        fread(aluno.Curso, sizeof(char), STRING_MAXSIZE, arqDados);
        fread(&aluno.Nota, sizeof(float), 1, arqDados);

        printaAluno(aluno);
    }
}

/*------------------------------------------------------------------*/
/*funcao DELETE*/


/*------------------------------------------------------------------*/
void escolheAcao(FILE *arqDados, FILE *arqIndice, int codigoComando)
{
    switch(codigoComando){

        case INSERT:
            recebeEntradas(arqDados, arqIndice);
            break;

        case SEARCH:
            procuraAluno(arqDados, arqIndice);
            break;

        case DELETE:
            break;

        case EXIT:
            break;
      }
}
