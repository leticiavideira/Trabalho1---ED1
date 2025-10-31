#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "formas.h"
#include "pilha.h"

typedef struct{
    formaTipo tipoF;
    void* data;
} FormaSt;

typedef struct{
    int id;
    PILHA *formas;
}carregadorSt;

typedef struct {
    int id;
    double x, y;
    carregadorSt *cargaEsquerda;
    carregadorSt *cargaDireita;
    FormaSt *emDisparo;
    int cargaEsqId;
    int cargaDirId;
} disparadorSt;

typedef struct{
    FormaSt *forma;
    double x, y;
    int iA; //bool
    double disparadorX;
    double disparadorY;
} PosicaoFormaASt;

typedef enum {
    ARRAYDISPARADORF, ARRAYCARREGADORF, POSICAOFORMAF, PILHAF
} TIPOF;

typedef struct{
    void *p;
    TIPOF tp;
} ItemFree;


typedef struct {
    double minX, minY;
    double maxX, maxY;
} bBox;

typedef struct {
    int instrucoesExecutadas;
    int disparos;
    int formasEsmagadas;
    int formasClonadas;
    double areaEsmagadaTotal;
} Estatisticas;