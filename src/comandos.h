#ifndef COMANDOS_H
#define COMANDOS_H

#include "fila.h"
#include "pilha.h"
#include "leitorGeo.h"
#include "auxiliares.h"

void pdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, Estatisticas *stats);

void lcExecutar (carregadorSt **carregador, int *contCarregador, CHAO chao, PILHA pilhaFree, FILE *txtFile, Estatisticas *stats);

void atchExecutar (carregadorSt **carregador, int *contCarregador, disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, Estatisticas *stats);

void shftExecutar (disparadorSt **disparador, int *contDisparos, carregadorSt *carregador, int *contCarregador, FILE *txtFile, Estatisticas *stats);

void dspExecutar (disparadorSt **disparador, int *contDisparos, PILHA arena, PILHA pilhaFree, FILE *txtFile, Estatisticas *stats);

void rjdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, PILHA arena, carregadorSt *carregador, int *contCarregador, FILE *txtFile, Estatisticas *stats);

void calcExecutar (PILHA arena, CHAO chao, FILE *txtFile, Estatisticas *stats);


#endif