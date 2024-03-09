#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>

#define STRING_MAXSIZE 50

typedef struct dados_st DADOS_Aluno;

struct dados_st
{
    int nUSP;
    char Nome_Completo[STRING_MAXSIZE];
    char Curso[STRING_MAXSIZE];
    float Nota;
};

int contaAlunosNoFile(FILE* arquivo);
void exibeTudo(FILE*, int);
void exibeFaixa(FILE*, int, int);
int posicaoFinalArquivo(FILE*);

#endif //ALUNO_H
