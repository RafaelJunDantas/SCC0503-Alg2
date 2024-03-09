#include "fileHandler.h"
#include <stdio.h>

void recebeEntradas(FILE *arq_bin, DADOS_Aluno aluno)
{
    char charBuffer = 0;

    scanf("%d", &aluno.nUSP);
    scanf("%*c");

    for(int i=0; i < STRING_MAXSIZE; i++)
    {
        scanf("%c", &charBuffer);
        if(charBuffer == VIRGULA)
        {
            aluno.Nome_Completo[i] = '\0';
            break;
        }
        aluno.Nome_Completo[i] = charBuffer;
    }
    //scanf(" %[^(\r|\n)]s", aluno.Nome_Completo);

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

    jogaEntradasNumBinario(arq_bin, aluno);
}

void jogaEntradasNumBinario(FILE *arq_bin, DADOS_Aluno aluno)
{
    fseek(arq_bin, 0, SEEK_CUR);

    fwrite(&aluno.nUSP, sizeof(int), 1, arq_bin);
    fwrite(aluno.Nome_Completo, sizeof(char), STRING_MAXSIZE, arq_bin);
    fwrite(aluno.Curso, sizeof(char), STRING_MAXSIZE, arq_bin);
    fwrite(&aluno.Nota, sizeof(float), 1, arq_bin);
}

void printaRegistrosDeArquivo(FILE *arq_bin)
{
    DADOS_Aluno aluno;

    fseek(arq_bin, 0, SEEK_SET);

    fread(&aluno.nUSP, sizeof(int), 1, arq_bin);
    fread(aluno.Nome_Completo, sizeof(char), STRING_MAXSIZE, arq_bin);
    fread(aluno.Curso, sizeof(char), STRING_MAXSIZE, arq_bin);
    fread(&aluno.Nota, sizeof(float), 1, arq_bin);

    printf("\nnUSP: %d", aluno.nUSP);
    printf("\nNome: %s", aluno.Nome_Completo);
    printf("\nCurso: %s", aluno.Curso);
    printf("\nNota: %.2f\n", aluno.Nota);
}

int ContaAlunosDeArquivo(FILE *arquivo)
{
    if(arquivo != NULL)
    {
        //para garantir que o cursor estará na primeira posição do arquivo
        fseek(arquivo, 0, SEEK_SET);

        int contadorDeAlunos = contaAlunosNoFile(arquivo);

        return contadorDeAlunos;
    }

    printf("Erro ao abrir arquivo");
    return 0;
}

//esta função é basicamente o core do código (seria uma gambiarra?)
void abreArquivoParaPrograma()
{
    char nomeDoArquivo[FILENAME_MAXSIZE];
    scanf(" %[^(\r|\n)]s", nomeDoArquivo);

    FILE *arquivo = fopen(nomeDoArquivo, "rb");
    int quantidadeDeAlunos = contaAlunosNoFile(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    escolheAcao(arquivo, quantidadeDeAlunos);
    fclose(arquivo);
}

void escolheAcao(FILE *arquivo, int quantidadeDeAlunos)
{
    int acao;
    scanf("%d", &acao);

    switch (acao)
    {
        int inicio;
        int fim;

        //exibe todos os alunos
        case 1:
            exibeTudo(arquivo, quantidadeDeAlunos);
            break;

            //primeira metade
        case 2:
            exibeFaixa(arquivo, 0, quantidadeDeAlunos/2);
            break;

            //segunda metade
        case 3:
            exibeFaixa(arquivo, (quantidadeDeAlunos/2), quantidadeDeAlunos - 1);
            break;

            //faixa de registros
        case 4:
            scanf("%d", &inicio);
            scanf("%d", &fim);
            exibeFaixa(arquivo, inicio - 1, fim);
            break;

            //registro específico
        case 5:
            scanf("%d", &inicio);
            fim = inicio;
            inicio--;//mini gambiarra para sair na função da faixa
            exibeFaixa(arquivo, inicio, fim);
            break;
    }
}