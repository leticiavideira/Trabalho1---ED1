#ifndef COMANDOS_H
#define COMANDOS_H

#include "fila.h"
#include "pilha.h"
#include "leitorGeo.h"

void pdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree);

void lcExecutar (carregadorSt **carregador, int *contCarregador, CHAO chao, PILHA pilhaFree, FILE *txtFile);

void atchExecutar (carregadorSt **carregador, int *contCarregador, disparadorSt **disparador, int *contDisparos, PILHA pilhaFree);

void shftExecutar (disparadorSt **disparador, int *contDisparos, carregadorSt *carregador, int *contCarregador, FILE *txtFile);

void dspExecutar (disparadorSt **disparador, int *contDisparos, PILHA arena, PILHA pilhaFree, FILE *txtFile);

void rjdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, PILHA arena, carregadorSt *carregador, int *contCarregador, FILE *txtFile);

void calcExecutar (PILHA arena, CHAO chao, FILE *txtFile);


#endif