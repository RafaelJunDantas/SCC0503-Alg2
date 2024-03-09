#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>

#define STRING_MAXSIZE 50
#define TAMANHO_REGISTRO 108

typedef struct dados_st
{
    int nUSP;
    char Nome[STRING_MAXSIZE];
    char SobreNome[STRING_MAXSIZE];
    char Curso[STRING_MAXSIZE];
    float Nota;
}DADOS_Aluno;

void printaAluno(DADOS_Aluno aluno);

#endif //ALUNO_H
