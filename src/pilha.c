#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct elementoPilha {
    void *valor;
    struct elementoPilha *prox;
}elemPilha;


typedef struct {
    elemPilha *topo;
    int tamanho;
} Pilha;

PILHA criaPilha (){
    Pilha *p = (Pilha*) malloc (sizeof (Pilha));

    if (p == NULL){
        printf("Erro ao alocar memoria para criacao de pilha.\n");
            return NULL;
    }

    p->topo = NULL;
    p->tamanho = 0;
    return (Pilha*)p;
}