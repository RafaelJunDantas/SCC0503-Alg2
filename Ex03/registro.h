#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

typedef struct registro_st REGISTRO;

//soma dos bytes usados em um registro = 102.
struct registro_st
{
    int nUSP;                           // 4 bytes
    char Nome[STRING_MAXSIZE];         // 30 bytes
    char Sobrenome[STRING_MAXSIZE];    // 30 bytes
    char Curso[STRING_MAXSIZE];        // 30 bytes
    float Nota;                         // 8 bytes
};

REGISTRO regInsert();
bool regPrint(REGISTRO *registro);


/*-------------------Fora do Arquivo, mas não deletadas----------------------*/
//int reg_memAllocator(REGISTRO **registro);
//int reg_memFree(REGISTRO **registro);

#endif //REGISTRO_H
