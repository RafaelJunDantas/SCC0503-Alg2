#include "registro.h"

/*
Este arquivo é encarregado de
implementar todas as funções
que dizem respeito ao gerenciamento
dos registros.
*/


/*-----------------------------------------*/
//As funções deste bloco
//recebem ponteiros para registro,
//assim sendo, pode trabalhar com
//registro alocados dinamica ou
//estaticamente.
//
//Retornam 1 caso faça corretamente.
//Retornam 0 e mensagem de erro se falhar.



//recebe os valores do registro
REGISTRO regInsert() {

    REGISTRO aluno;
    char charBuffer;

    scanf("%d", &aluno.nUSP);

    scanf("%c", &charBuffer);                    //para a vírgula
    scanf("%c", &charBuffer);                    //para o abre aspas

    for (int i = 0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if (charBuffer == ASPA) {
            aluno.Nome[i] = '\0';
            break;
        }
        aluno.Nome[i] = charBuffer;
    }

    scanf("%c", &charBuffer);                    //para a vírgula
    scanf("%c", &charBuffer);                    //para o abre aspas

    for (int i = 0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if (charBuffer == ASPA) {
            aluno.Sobrenome[i] = '\0';
            break;
        }
        aluno.Sobrenome[i] = charBuffer;
    }

    scanf("%c", &charBuffer);                    //para a vírgula
    scanf("%c", &charBuffer);                    //para o abre aspas

    for (int i = 0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if (charBuffer == ASPA) {
            aluno.Curso[i] = '\0';
            break;
        }
        aluno.Curso[i] = charBuffer;
    }

    scanf("%c", &charBuffer);                    //para a vírgula

    scanf("%f", &aluno.Nota);

    return aluno;
}

//printa na tela os valores do registro
bool regPrint(REGISTRO *registro)
{
    if(registro != NULL)
    {
        printf("-------------------------------\n");
        printf("nUSP: %d\n", registro->nUSP);
        printf("Nome: %s\n", registro->Nome);
        printf("Sobrenome: %s\n", registro->Sobrenome);
        printf("Curso: %s\n", registro->Curso);
        printf("Nota: %.2f\n", registro->Nota);
        printf("-------------------------------\n");

        return TRUE;
    }

    printf("Erro ao printar registro!\n");

    return FALSE;
}
/*-----------------------------------------*/


