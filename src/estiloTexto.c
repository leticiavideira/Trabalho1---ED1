 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estiloTexto.h"


 typedef struct {
    char* fFamily;
    char* fWeight;
    int fSize;

} EstiloTexto;

ESTILO_TEXTO criaEstiloTexto (char* fFamily, char* fWeight, int fSize){
    if (fFamily == NULL)
        return NULL;

    EstiloTexto *ts  = malloc (sizeof(EstiloTexto));

    if (ts == NULL)
        return NULL;

    ts->fFamily = (char *) malloc (strlen(fFamily) + 1);

    if (ts->fFamily == NULL)
        return NULL;

    strcpy(ts->fFamily, fFamily);


    ts->fWeight = (char *) malloc (strlen(fWeight) + 1);

    if (ts->fWeight == NULL)
        return NULL;

    strcpy(ts->fWeight, fWeight);


    ts->fSize = fSize;

    return ts;
}

char* getfFamily_T (ESTILO_TEXTO ts){
    if (ts == NULL)
        return NULL;

    EstiloTexto *ts1 = ((EstiloTexto *)ts);
    return (ts1->fFamily);
}

char* getfWeight_T (ESTILO_TEXTO ts){
    if (ts == NULL)
        return NULL;

    EstiloTexto *ts1 = ((EstiloTexto *)ts);
    return (ts1->fWeight);
}

int getfSize_T (ESTILO_TEXTO ts){
    if (ts == NULL)
        return -1;

    EstiloTexto *ts1 = ((EstiloTexto *)ts);
    return (ts1->fSize);
}

void killEstiloTexto (ESTILO_TEXTO ts){
    EstiloTexto *ts1 = ((EstiloTexto *)ts);
    free(ts1->fFamily);
    free(ts1->fWeight);
    free(ts1);
}