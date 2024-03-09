#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include "aluno.h"

#define FILENAME_MAXSIZE 20
#define VIRGULA ','
#define INSERT 0
#define SEARCH 1
#define DELETE 2
#define EXIT -1
#define APAGADO -1
#define NAO_EXISTE -2

int retornaCodigoComando(char comando[10]);

/*funcao INSERT*/
void recebeEntradas(FILE *arqDados, FILE *arqIndice);
void jogaEntradasNumBinario(FILE *arqDados, FILE *arqIndice, DADOS_Aluno aluno);
void escreveIndice(FILE *arqIndice, int chaveRegistro, int posicaoRegistro);

/*funcao SEARCH*/
int chaveExiste(FILE *arqIndice, int chave);
void procuraAluno(FILE *arqDados, FILE *arqIndice);

/*funcao DELETE*/


void escolheAcao(FILE *arqDados,   FILE *arqIndice, int codigoComando);

#endif //FILEHANDLER_H

