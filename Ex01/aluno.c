#include "aluno.h"
#include <stdio.h>

int contaAlunosNoFile(FILE *arquivo)
{
    int contadorDeAlunos = 0;
    DADOS_Aluno aluno;

    fseek(arquivo, 0, SEEK_SET);

    while(!feof(arquivo))
    {
        fread(&aluno.nUSP, sizeof(int), 1, arquivo);
        fread(aluno.Nome_Completo, sizeof(char), 50, arquivo);
        fread(aluno.Curso, sizeof(char), 50, arquivo);
        fread(&aluno.Nota, sizeof(float), 1, arquivo);

        contadorDeAlunos++;
    }

    return contadorDeAlunos;
}

void exibeTudo(FILE* arquivo, int quantidadeDeAlunos)
{
    DADOS_Aluno aluno;

    for(int i=1; i < quantidadeDeAlunos; i++)
    {
        //para pular uma linha a cada aluno printado
        if(i != 1)
        {
            printf("\n\n");
        }

        fread(&aluno.nUSP, sizeof(int), 1, arquivo);
        fread(aluno.Nome_Completo, sizeof(char), 50, arquivo);
        fread(aluno.Curso, sizeof(char), 50, arquivo);
        fread(&aluno.Nota, sizeof(float), 1, arquivo);

        printf("nUSP: %d\n", aluno.nUSP);
        printf("Nome: %s\n", aluno.Nome_Completo);
        printf("Curso: %s\n", aluno.Curso);
        printf("Nota: %.2f", aluno.Nota);
    }
}
void exibeFaixa(FILE *arquivo, int inicio, int fim)
{
    DADOS_Aluno aluno;
    int posicaoFinal = posicaoFinalArquivo(arquivo);

    if(fim > posicaoFinal)
    {
        fim = posicaoFinal;
    }

    //até o fim da faixa contanto que ela ou té o fim do arquivo, o que chegar primeiro
    for(int i=0; i < fim; i++)
    {
        //para pular uma linha a cada aluno printado
        if (i > inicio)
        {
            printf("\n\n");
        }

        fread(&aluno.nUSP, sizeof(int), 1, arquivo);
        fread(aluno.Nome_Completo, sizeof(char), 50, arquivo);
        fread(aluno.Curso, sizeof(char), 50, arquivo);
        fread(&aluno.Nota, sizeof(float), 1, arquivo);

        if ((i >= inicio) && (i < fim))
        {
            printf("nUSP: %d\n", aluno.nUSP);
            printf("Nome: %s\n", aluno.Nome_Completo);
            printf("Curso: %s\n", aluno.Curso);
            printf("Nota: %.2f", aluno.Nota);
        }

    }
}

int posicaoFinalArquivo(FILE *arquivo)
{
    int posFinal;
    fseek(arquivo, 0, SEEK_END);
    posFinal = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    //de bytes para numero de iterações - peguei dica com colega futura dupla a partir dos proximos exercicios
    posFinal = (posFinal/108);
    return posFinal;
}