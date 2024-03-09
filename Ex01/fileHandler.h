#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include "aluno.h"

#define FILENAME_MAXSIZE 20
#define VIRGULA ','

void recebeEntradas(FILE *arq_bin, DADOS_Aluno aluno);
void jogaEntradasNumBinario(FILE *arq_bin, DADOS_Aluno aluno);
void printaRegistrosDeArquivo(FILE *arq_bin);

int ContaAlunosDeArquivo(FILE*);
void abreArquivoParaPrograma();
void escolheAcao(FILE*, int);

#endif //FILEHANDLER_H
