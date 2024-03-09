#include <stdio.h>
#include <stdlib.h>
#include "fileHandler.h"

int main()
{
    DADOS_Aluno aluno;
    FILE *arq_bin = fopen("arquivoBinario.bin", "wb+");

    fseek(arq_bin, 0, SEEK_SET);

    while(!feof(stdin))
    {
        recebeEntradas(arq_bin, aluno);
    }

    int numeroDeAlunos = contaAlunosNoFile(arq_bin);

    exibeFaixa(arq_bin, numeroDeAlunos-11, numeroDeAlunos);

    fclose(arq_bin);
    return 0;
}