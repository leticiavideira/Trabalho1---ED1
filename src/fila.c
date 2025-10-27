#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

typedef struct elementoFila {
    void *conteudo;
    struct elementoFila *prox;
}elementoFila;


typedef struct {
    elementoFila *inicio;
    elementoFila *fim;
    int tamanho;
} Fila;

FILA criaFila (){
    Fila *f = (Fila *) malloc (sizeof (Fila));

    if (f == NULL){
        printf ("Erro ao alocar memoria para criacao da fila.\n");
        return NULL;
    }

    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return (Fila *)f;
}

int pushFila (FILA f, void *conteudo){
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    elementoFila *novo = (elementoFila *) malloc (sizeof (elementoFila));

    if (novo == NULL){
        printf ("Erro ao alocar memoria para novo elemento da fila.\n");
        return 0;
    }

    novo->conteudo = conteudo;
    novo->prox = NULL;

    if (f1->fim == NULL){
        f1->inicio = novo;

    } else {
        f1->fim->prox = novo;
    }

    f1->fim = novo;
    f1->tamanho++;

    return 1;
}

void *popFila (FILA f){
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    elementoFila *remover = f1->inicio;
    void *conteudo = remover->conteudo;

    if (f1->inicio == f1->fim){
        f1->fim = NULL;
    }

    f1->inicio = remover->prox;
    free(remover);
    f1->tamanho--;
    
    return (conteudo);
}

void *primeiroElemFila (FILA f){
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    return (f1->inicio->conteudo);
}

int tamanhoFila (FILA f){
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    return (f1->tamanho);
}

int filaVazia (FILA f){
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    return (f1->tamanho == 0);
}

void limpaFila (FILA f){
    if (f == NULL)
        return;
    
    Fila *f1 = ((Fila *) f);

    while (f1->tamanho > 0){
        popFila (f1);
    }
}

void killFila (FILA f){
    if (f == NULL)
        return;
    
    Fila *f1 = ((Fila *) f);

    limpaFila (f1);
    free (f1);
}