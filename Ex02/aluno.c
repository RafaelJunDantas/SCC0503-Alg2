#include "aluno.h"
#include <stdio.h>

/*------------------------------------------------------------------*/
void printaAluno(DADOS_Aluno aluno)
{
    printf("-------------------------------");
    printf("\nUSP number: %d", aluno.nUSP);
    printf("\nName: %s", aluno.Nome);
    printf("\nSurname: %s", aluno.SobreNome);
    printf("\nCourse: %s", aluno.Curso);
    printf("\nTeste grade: %.2f\n", aluno.Nota);
    printf("-------------------------------\n");
}

