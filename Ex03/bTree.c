#include "bTree.h"

void sortAuxVector(keyAndRRNOnPage *auxVector, keyAndRRNOnPage newReg);
int promote (FILE *bTree, PAGE splitedPage, keyAndRRNOnPage toBePromoted, long sonRRN);
long searchBTreeAux(FILE *bTree, int key, long RRN);


FILE *inicializeBTree(char *fileName){          //inicializa a arvore b
    FILE *bTree = inicializeFile(fileName);

    if(bTree == NULL){
        return NULL;
    }

    setDefaultHeader(bTree);                    //seta o cabeçalho inicial. v---v

    /*
    PAGE *page = createPage(8);
    writePage(bTree, page);
    free(page);
    */

    return bTree;
}

void printBTree(FILE *bTree){                                   //printa bTree na ordem
                                                                //que as paginas
    fseek(bTree, 0, SEEK_SET);                                  //foram inseridas no arquivo

    printHeader(bTree, FALSE);
    long maxRRN = getHigherRRN_header(bTree);

    for(int i=1; i<=maxRRN; i++)
    {
        printPage_ByItsRRN(bTree, i);
    }
}

/*-------------------------------Funções do Header-------------------------------*/

//configura um header no inicio do programa com RRNroot = -1
void setDefaultHeader(FILE *bTree)
{
    HEADER header;
    header.RRNdaRaiz = NAO_EXISTE;
    header.maiorRRN = 0;

    setHeaderEmptySpaces(&header);

    fseek(bTree, 0, SEEK_SET);
    fwrite(&header, sizeof(HEADER), 1, bTree);          //escreve header default
    fseek(bTree, 0, SEEK_SET);                          //volta o ponteiro para o inicio do arq por segurança
}

//atualiza o header para uma nova raiz da árvore
void atualizaHeader(FILE *bTree, long newRootRRN, bool newInsertion)
{
    HEADER header = getHeader(bTree);                //define o header
    header.RRNdaRaiz = newRootRRN;

    if(newInsertion == TRUE)
    {
        header.maiorRRN++;
    }

    fseek(bTree, 0, SEEK_SET);                      //escreve novo header
    fwrite(&header, sizeof(HEADER), 1, bTree);
    fseek(bTree, 0, SEEK_SET);                      //volta o ponteiro para o inicio do arq por segurança
}

// garante que o header vai ter 4088 bytes vazios para completar a página
void setHeaderEmptySpaces(HEADER *header)
{
    for(int i=0; i<sizeof(header->espacoVazio); i++)
    {
        header->espacoVazio[i] = '\0';                   //escreve 4088 bytes de /0 (espaço vazio restante de uma pag - long)
    }
}

//função que printa o header na tela.
void printHeader(FILE *bTree, int printEmptySpace)
{
    HEADER header;
    fseek(bTree, 0, SEEK_SET);
    fread(&header, sizeof(HEADER), 1, bTree);

    printf("-------------------------------\n");
    printf("HEADER:\n");
    printf("Root RRN: %ld\n", header.RRNdaRaiz);

    if(printEmptySpace == TRUE)
    {
        for(int i=0; i<sizeof(header.espacoVazio); i++)
        {
            printf("%c ", header.espacoVazio[i]);
        }
    }

    printf("-------------------------------\n");
}

//retorna o header da B Tree;
HEADER getHeader(FILE *bTree)
{
    HEADER header;
    fseek(bTree, 0, SEEK_SET);
    fread(&header, sizeof(HEADER), 1, bTree);
    fseek(bTree, 0, SEEK_SET);

    return header;
}

//retorna o RRN da raiz da árvore que será lido no header.
long getRootRRN_header(FILE *bTree)
{
    HEADER header = getHeader(bTree);
    return header.RRNdaRaiz;
}

//retorna o maior RRN da árvore que será lido no header.
long getHigherRRN_header(FILE *bTree)
{
    HEADER header = getHeader(bTree);
    return header.maiorRRN;
}
/*-------------------------------------------------------------------------------*/

/*-------------------------------Funções de Página-------------------------------*/

//função genérica de criação de nova página VAZIA + ATUALIZA HEADER
//SE CHEGOU ATÉ AQUI, é porque nova página PRECISA ser criada
PAGE cria_Pagina(FILE *bTree)
{
    long newHigherRRN = getHigherRRN_header(bTree);                 //recebe o RRN da ultima página
    newHigherRRN++;                                                 //incrementa, para resultar no novo RRN mais alto
                                                                    //separa espaço no arquivo da B Tree para a nova página
    PAGE page = allocNewPage(bTree, newHigherRRN);                              //inclusive, atualizando o maior RRN no Header
    //atualizaHeader(bTree, getRootRRN_header(bTree), TRUE);

    return page;
}

//Separa o espaço no arquivo para a nova página (aloca os próximos 4K bytes)
PAGE allocNewPage(FILE *bTree, long RRN)
{
    PAGE page = setEmptyPageParameters(RRN);           // (RRN header = 0)

    printPageOnFile(bTree, page, page.pageRRN);

    HEADER header;                                   //Atualiza o header se necessário
    header = getHeader(bTree);
    if(header.RRNdaRaiz == NAO_EXISTE)
    {
        atualizaHeader(bTree, RRN, FALSE);
    }

    atualizaHeader(bTree, getRootRRN_header(bTree), TRUE);

    return page;
}

//printa uma página no arquivo da B Tree
void printPageOnFile(FILE *bTree, PAGE page, long RRN)
{
    fseek(bTree, PAGESIZE*RRN, SEEK_SET);
    fwrite(&page, sizeof(PAGE), 1, bTree);
}

//retorna page com parametros de uma página nova recem criada
PAGE setEmptyPageParameters(long pageRRN)
{
    PAGE page;
    page.pageRRN = pageRRN;
    page.keyCount = 0;

    page.filhos[0] = NAO_EXISTE;
    for(int i=0; i < MAXKEY; i++)
    {
        page.filhos[i+1] = NAO_EXISTE;
        page.keyRRN[i].key = NAO_EXISTE;
        page.keyRRN[i].RRN = NAO_EXISTE;
    }

    page.folha = TRUE;

    return page;
}

//retorna indice do primeiro espaço vazio no vetor de chaves para registros
int getFirstEmptySpaceIndex(PAGE page)
{
    if(page.keyCount == 0)
    {
        //teste
        //printf(" AQUI ");
        return 0;
    }

    for(int i = 0; i < page.keyCount + 1; i++)
    {
        if(page.keyRRN[i].key == NAO_EXISTE)
        {
            return i;
        }
    }

    return NAO_EXISTE;
}

//retorna uma página dado o seu RRN
PAGE getPage(FILE *bTree, long pageRRN)
{
    PAGE page;

    fseek(bTree, PAGESIZE * pageRRN, SEEK_SET);
    fread(&page, sizeof(PAGE), 1, bTree);

    return page;
}

PAGE sortPage(PAGE page){
    for(int j = page.keyCount; j > 0; j--){
        for(int i = 0; i < j - 1; i++){
            if(page.keyRRN[i].key > page.keyRRN[i + 1].key){
                keyAndRRNOnPage aux = page.keyRRN[i];
                page.keyRRN[i] = page.keyRRN[i + 1];
                page.keyRRN[i + 1] = aux;
            }
        }
    }

    return page;
}

void printPage(PAGE page)
{
    printf("-------------------------------\n");
    printf("Page (RRN): %ld\n", page.pageRRN);
    printf("Number of Keeping Primary Keys: %d\n", page.keyCount);
    printf("Is Leaf?  (0 = False | 1 = True): %d\n", page.folha);
    printf("--------------\n");
    for(int i=0; i<MAXKEY; i++)
    {
        printf("RRN do %dº filho: %ld\n", i+1, page.filhos[i]);
        printf("Chave do %dº registro: %d  | RRN do registro no Arquivo de Dados: %ld\n", i+1, page.keyRRN[i].key, page.keyRRN[i].RRN);
    }
    printf("RRN do %dº filho: %ld\n", MAXKEY, page.filhos[MAXKEY]);
    printf("-------------------------------\n");
}

void printPage_ByItsRRN(FILE *bTree, long pageRRN)
{
    PAGE page;

    fseek(bTree, PAGESIZE*pageRRN, SEEK_SET);
    fread(&page, sizeof(PAGE), 1, bTree);

    printf("-------------------------------\n");
    printf("Page (RRN): %ld\n", page.pageRRN);
    printf("Number of Keeping Primary Keys: %d\n", page.keyCount);
    printf("Is Leaf?  (0 = False | 1 = True): %d\n", page.folha);
    printf("-------------------------------\n");
    for(int i=0; i<MAXKEY; i++)
    {
        printf("RRN do %dº filho: %ld\n", i+1, page.filhos[i]);
        printf("Chave do %dº registro: %d  | RRN do registro no Arquivo de Dados: %ld\n", i+1, page.keyRRN[i].key, page.keyRRN[i].RRN);
    }
    printf("RRN do %dº filho: %ld\n", MAXKEY, page.filhos[MAXKEY]);
    printf("-------------------------------\n");

    fseek(bTree, 0, SEEK_SET);
}

bool isFull(PAGE page)
{
    if(page.keyCount == MAXKEY)
    {
        return TRUE;
    }

    return FALSE;
}

bool isLeaf(PAGE page)
{
    return page.folha;
}

//encontra nó folha onde será (ou seria) inserido novo registro
PAGE getLeaf_toInsert(FILE *bTree, PAGE pageRoot, int key)
{
    if(isLeaf(pageRoot))
    {
        return pageRoot;
    }

    else
    {
        bool flag = FALSE;

        //compara as keys para achar a PAGE subarvore filha
        for(int i=0; i < MAXKEY; i++)
        {
            if(key <= pageRoot.keyRRN[i].key)
            {
                pageRoot = getLeaf_toInsert(bTree, getPage(bTree, pageRoot.filhos[i]), key);
                flag = TRUE;
                break;
            }
        }

        if(!flag)
            pageRoot = getLeaf_toInsert(bTree, getPage(bTree, pageRoot.filhos[MAXKEY]), key);

        return pageRoot;
    }
}

//retorna o RRN do pai de um nó
//deve-se chamar a função com father = pageRoot
long getFatherPageRRN(FILE *bTree, PAGE father, PAGE pageRoot, int key)
{
    //quando não tiver pai
    if(isLeaf(father))
    {
        return NAO_EXISTE;
    }

    //caso seja folha e tenha um pai
    if(isLeaf(pageRoot))
    {
        return father.pageRRN;
    }

    bool flag;
    long fatherRRN;

    //caso não seja folha e tenha um pai
    for(int i=0; i < MAXKEY; i++)
    {
        if(key <= pageRoot.keyRRN[i].key)
        {
            fatherRRN = getFatherPageRRN(bTree, pageRoot, getPage(bTree, pageRoot.filhos[i]), key);
            flag = TRUE;
            break;
        }
    }

    if(!flag)
        fatherRRN = getFatherPageRRN(bTree, pageRoot, getPage(bTree, pageRoot.filhos[MAXKEY]), key);

    return fatherRRN;
}

/*-------------------------------------------------------------------------------*/

/*-------------------------------Funções de Árvore-------------------------------*/

//insere novo registro
void insertNewReg(FILE *bTree, keyAndRRNOnPage regData)
{
    HEADER header = getHeader(bTree);
    //printHeader(bTree, FALSE);

    if(searchBTreeAux(bTree, regData.key, header.RRNdaRaiz) != NAO_EXISTE){
        printf("-------------------------------\n");
        printf("O registro ja existe!\n");
        printf("-------------------------------\n");
        return;
    }

    PAGE page;

    //cria primeira página em branco
    if(header.RRNdaRaiz == NAO_EXISTE)
    {
        page = cria_Pagina(bTree);                                          //cria_Pagina atualiza o header.

        //printHeader(bTree, FALSE);
        //printPage_ByItsRRN(bTree, 1);

        header = getHeader(bTree);
    }

    page = getPage(bTree, header.RRNdaRaiz);
    page = getLeaf_toInsert(bTree, page, regData.key);

    if(isFull(page))
    {
        splitNode(bTree, page, regData);
    }

    else
    {
        int emptySpaceIndex = getFirstEmptySpaceIndex(page);

        page.keyRRN[emptySpaceIndex].key = regData.key;
        page.keyRRN[emptySpaceIndex].RRN = regData.RRN;
        page.keyCount++;

        page = sortPage(page);

        fseek(bTree, PAGESIZE*page.pageRRN, SEEK_SET);                      //reescreve a página com novos valores
        fwrite(&page, sizeof(PAGE), 1, bTree);

        //printPage_ByItsRRN(bTree, page.pageRRN);
    }
}

long searchRRNbTree(FILE *bTree, FILE *arqDados, int key)
{
    HEADER header = getHeader(bTree);

    long regRRN = searchBTreeAux(bTree, key, header.RRNdaRaiz);

    if(regRRN == NAO_EXISTE){
        //printf("-------------------------------\n");
        printf("Registro nao encontrado!\n");
        //printf("-------------------------------\n");
    }

    else{
        //printf("-------------------------------\n");
        //printf("Registro encontrado!\n");
        //printf("-------------------------------\n");

        return regRRN;
    }

    return NAO_EXISTE;
}

void searchBTree(FILE *bTree, FILE *arqDados, bool update){
    HEADER header = getHeader(bTree);

    int key = 0;
    scanf("%d", &key);

    long regRRN = searchBTreeAux(bTree, key, header.RRNdaRaiz);

    if(regRRN == NAO_EXISTE){
        //printf("-------------------------------\n");
        printf("Registro nao encontrado!\n");
        //printf("-------------------------------\n");
    }

    else{
        //printf("%ld\n",regRRN);
        //printf("-------------------------------\n");
        //printf("Registro encontrado!\n");
        //printf("-------------------------------\n");

        REGISTRO registro = findReg_ByItsRRN(arqDados, regRRN);
        regPrint(&registro);
    }
}

long searchBTreeAux(FILE *bTree, int key, long RRN)
{
    if(RRN == NAO_EXISTE){                                                                      //verifica se há folhas
        return NAO_EXISTE;
    }

    PAGE page = getPage(bTree, RRN);

    if(key < page.keyRRN[0].key){
        return searchBTreeAux(bTree, key, page.filhos[0]);
    }

    for(int i = 0; i < page.keyCount; i++){
        if(page.keyRRN[i].key == key){
            return page.keyRRN[i].RRN;
        }
        else if(key > page.keyRRN[i].key){
            if(page.keyRRN[i + 1].key != NAO_EXISTE && key < page.keyRRN[i + 1].key){
                return searchBTreeAux(bTree, key, page.filhos[i + 1]);
            }
            else if(page.keyRRN[i + 1].key == NAO_EXISTE){
                return searchBTreeAux(bTree, key, page.filhos[i]);
            }

        }
    }

    return NAO_EXISTE;
}

//faz o split e promove
void splitNode(FILE *bTree, PAGE pageRoot, keyAndRRNOnPage newReg)
{
    HEADER header = getHeader(bTree);
    PAGE newPage = cria_Pagina(bTree);
    PAGE newRootPage = setEmptyPageParameters(header.maiorRRN+1);
    keyAndRRNOnPage auxVector[ORDEM];

    //novo reg entra por ultimo
    for(int i=0; i < MAXKEY; i++)
    {
        auxVector[i] = pageRoot.keyRRN[i];
    }
    auxVector[MAXKEY] = newReg;

    //ordena a page antiga
    //porém, não atualiza os filhos
    for(int i=0; i<MAXKEY; i++)
    {
        pageRoot.keyRRN[i] = auxVector[i];
    }

    keyAndRRNOnPage toBePromoted;

    //splita de fato e joga os regs na nova page
    for(int i=(MAXKEY/2), j=0; i < MAXKEY; i++, j++)
    {
        //primeira iteração
        if(j == 0)
        {
            toBePromoted = auxVector[i];                                            //check
            newPage.filhos[j] = pageRoot.filhos[i];                                 //check
            pageRoot.filhos[i+1] = newPage.pageRRN;

            //caso necessite de nova raiz
            newRootPage.filhos[j] = pageRoot.pageRRN;
            newRootPage.keyRRN[j] = toBePromoted;
            newRootPage.filhos[j+1] = newPage.pageRRN;
            newRootPage.keyCount++;
        }

        //adiciona no novo nó
        newPage.keyRRN[j] = auxVector[i+1];                                         //check
        newPage.filhos[j+1] = pageRoot.filhos[i+1];                                 //check
        newPage.keyCount++;                                                         //check

        //apaga do nó antigo
        pageRoot.keyRRN[j] = auxVector[j];                                          //check
        pageRoot.keyRRN[i+1].key = NAO_EXISTE;                                      //check
        pageRoot.keyRRN[i+1].RRN = NAO_EXISTE;                                      //check
        pageRoot.keyCount--;
    }

    /*
    //garantia
    pageRoot = sortPage(pageRoot);
    newPage = sortPage(newPage);
    */

    //-----Print final no arquivo-----//
    printPageOnFile(bTree, pageRoot, pageRoot.pageRRN);
    printPageOnFile(bTree, newPage, newPage.pageRRN);

    //caso necessite de nova raiz
    int promovido = promote(bTree, pageRoot, toBePromoted, newPage.pageRRN);
    if(promovido == FALSE)
    {
        newRootPage.pageRRN = header.maiorRRN+1;
        printPageOnFile(bTree, newRootPage, header.maiorRRN);
        atualizaHeader(bTree, newRootPage.pageRRN, TRUE);
        //printHeader(bTree, TRUE);
    }
}

void sortAuxVector(keyAndRRNOnPage *auxVector, keyAndRRNOnPage newReg)
{
    for(int i=0; i<ORDEM; i++)
    {
        for(int j=(i+1); j<ORDEM; j++)
        {
            if(auxVector[j].key > auxVector[i].key)
            {
                keyAndRRNOnPage auxKaRRN = auxVector[i];
                auxVector[i] = auxVector[j];
                auxVector[j] = auxKaRRN;
            }
        }
    }
}

int promote (FILE *bTree, PAGE splitedPage, keyAndRRNOnPage toBePromoted, long sonRRN)
{
    long fatherRRN = getFatherPageRRN(bTree, splitedPage, splitedPage, toBePromoted.key);

    if(fatherRRN == NAO_EXISTE)
    {
        return FALSE;
    }

    PAGE fatherPage = getPage(bTree, fatherRRN);

    if(isFull(fatherPage))
    {
        splitNode(bTree, fatherPage, toBePromoted);
    }

    int emptySpaceIndex = getFirstEmptySpaceIndex(fatherPage);
    fatherPage.keyRRN[emptySpaceIndex] = toBePromoted;
    fatherPage.filhos[emptySpaceIndex+1] = sonRRN;
    fatherPage.keyCount++;
    //só de garantia
    fatherPage.filhos[emptySpaceIndex] = splitedPage.pageRRN;

    fatherPage = sortPage(fatherPage);

    printPageOnFile(bTree, fatherPage, fatherPage.pageRRN);

    return TRUE;
}
/*-------------------------------------------------------------------------------*/
