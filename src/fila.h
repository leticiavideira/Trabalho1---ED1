#ifndef FILA_H
#define FILA_H

typedef void* FILA;

FILA criaFila ();

int pushFila (FILA f, void *conteudo);

FILA popFila (FILA f);

FILA primeiroElemFila (FILA f);

int tamanhoFila (FILA f);

int filaVazia (FILA f);

void limpaFila (FILA f);

void killFila (FILA f);

#endif