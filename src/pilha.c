#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct elementoPilha {
    void *conteudo;
    struct elementoPilha *prox;
}elementoPilha;


typedef struct {
    elementoPilha *topo;
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

int pushPilha (PILHA p, void *conteudo){
    if (p == NULL)  
        return 0;

    Pilha *p1 = ((Pilha*) p);

    elementoPilha *novo = (elementoPilha *) malloc (sizeof(elementoPilha));

    if (novo == NULL){
        printf ("Erro ao alocar novo elemento,\n");
        return 0;
    }

    novo->conteudo = conteudo;
    novo->prox = p1->topo;
    p1->topo = novo;
    p1->tamanho++;
    
    return 1;
}

void *popPilha (PILHA p){
    if (p == NULL) 
        return 0;

    Pilha *p1 = ((Pilha*) p);

    elementoPilha *remover = p1->topo;
    void *conteudo = remover->conteudo;

    p1->topo = remover->prox;
    free (remover);
    p1->tamanho--;

    return (conteudo);
}

void *topoPilha (PILHA p){
    if (p == NULL)  
        return 0;
    
    Pilha *p1 = ((Pilha*) p);

    return (p1->topo->conteudo);

}

void *acharElemPilha (PILHA p, int index){
    if (p == NULL || pilhaVazia(p) || index < 0){
        return NULL;
    }

    Pilha *p1 = (Pilha *) p; 
    
    if (index >= p1->tamanho){
        return NULL;
    }

    elementoPilha *atual = p1->topo;

    for (int i = 0 ; i < index ; i++){
        if (atual == NULL){
            return NULL;
        }
        atual = atual->prox;
    }

    return (atual->conteudo);
}

int tamanhoPilha (PILHA p){
    if (p == NULL)  
        return 0;

    Pilha *p1 = ((Pilha *) p);

    return(p1->tamanho);
}

int pilhaVazia (PILHA p){
    if (p == NULL)  
        return 1;
    
    Pilha *p1 = ((Pilha *) p);

    return (p1->tamanho == 0);

}


void limpaPilha (PILHA p){
    if (p == NULL)  
        return;

    Pilha *p1 = ((Pilha *) p);

    while (p1->tamanho > 0){
        popPilha (p1);
    }

}

void killPilha (PILHA p){
    if (p == NULL)  
        return;
    
    Pilha *p1 = ((Pilha *) p);

    limpaPilha (p1);
    free(p1);
}
