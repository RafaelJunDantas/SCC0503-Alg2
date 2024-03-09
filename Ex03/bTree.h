#ifndef BTREE_H
#define BTREE_H

#include "fileHandler.h"
#include "util.h"

#define PAGESIZE 4096               //valor em bytes do tamanho de cada página
//TODO: o valor da ordem deve ser atualizado para 204!!!!!!!!!!!!!!!!!!!!!!!
#define ORDEM 204                   //numero de ponteiros RRN filhos
#define MAXKEY (ORDEM - 1)          //numero max de chaves

//As chaves utilizadas são inteiros (número USP)

typedef struct keyRRNPage_st keyAndRRNOnPage;

struct keyRRNPage_st{       //struct com a chave e RRN do registro
    int key;
    long RRN;
};

typedef struct header_st HEADER;

struct header_st
{
    long RRNdaRaiz;                                     //RRN do nó raíz da arvore.
    long maiorRRN;                                      //RRN da ultima página criada
    char espacoVazio[PAGESIZE - (2*sizeof(long))];      //Controle: 4080 bytes de espaço livre para fecharem uma página.
                                                        //só garante que nada será escrito ali.
};

typedef struct page_st PAGE;

//TODO: adicionar espaço livre caso necessário (em char).
//120 bytes de tamanho
struct page_st
{
    long pageRRN;                           //RRN da pagina.
    short keyCount;                         //Contador de registros da página.
    bool folha;                             //booleano que diz se a página é ou não um nó folha.
    keyAndRRNOnPage keyRRN[MAXKEY];         //chave de um regsitro e 'seu' RRN no banco de dados.
    long filhos[ORDEM];                     //vetor que guarda o valor do RRN dos filhos da página.
};

FILE *inicializeBTree(char *fileName);

/*-------------------------------Funções do Header-------------------------------*/
void setDefaultHeader(FILE *bTree);
void atualizaHeader(FILE *bTree, long newRootRRN, bool newInsertion);
void setHeaderEmptySpaces(HEADER *header);
void printHeader(FILE *bTree, int printEmptySpace);

HEADER getHeader(FILE *bTree);
long getRootRRN_header(FILE *bTree);
long getHigherRRN_header(FILE *bTree);
/*-------------------------------------------------------------------------------*/


/*-------------------------------Funções de Página-------------------------------*/
PAGE cria_Pagina(FILE *bTree);
PAGE allocNewPage(FILE *bTree, long RRN);
void printPageOnFile(FILE *bTree, PAGE page, long RRN);
PAGE setEmptyPageParameters(long pageRRN);
int getFirstEmptySpaceIndex(PAGE page);
PAGE getPage(FILE *bTree, long pageRRN);
PAGE sortPage(PAGE page);
void printPage(PAGE page);
void printPage_ByItsRRN(FILE *bTree, long pageRRN);
bool isFull(PAGE page);
bool isLeaf(PAGE page);
PAGE getLeaf_toInsert(FILE *bTree, PAGE pageRoot, int key);
long getFatherPageRRN(FILE *bTree, PAGE father, PAGE pageRoot, int key);
/*-------------------------------------------------------------------------------*/


/*-------------------------------Funções de Árvore-------------------------------*/
void insertNewReg(FILE *bTree, keyAndRRNOnPage regData);
void searchBTree(FILE *bTree, FILE *arqDados, bool update);
long searchRRNbTree(FILE *bTree, FILE *arqDados, int key);
void printBTree(FILE *bTree);
void splitNode(FILE *bTree, PAGE pageRoot, keyAndRRNOnPage newReg);
/*-------------------------------------------------------------------------------*/
#endif //BTREE_H
