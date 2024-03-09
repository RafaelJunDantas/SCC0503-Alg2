#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include "registro.h"
#include "bTree.h"

//#define FILENAME_MAXSIZE 20


int retornaCodigoComando(char comando[10], int contador);

/*funcao INSERT*/
void recebeEntradas(FILE *arqDados, FILE *arqIndice, bool update);
void jogaEntradasNumBinario(FILE *arqDados, FILE *arqIndice, REGISTRO *aluno);

void escolheAcao(FILE *arqDados, FILE *arqIndice, int codigoComando);

long fileSize(FILE *arq);

void printArqDados(FILE *arq);

FILE *inicializeFile(char *fileName);

REGISTRO findReg_ByItsRRN(FILE *arqDados, long RRN);

#endif //FILEHANDLER_H

