#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "formas.h"
#include "fila.h"
#include "pilha.h"

typedef void* DISPARADOR;

DISPARADOR criarDisparador (int id, double x, double y);

void posicionarDisparador (DISPARADOR d, double x, double y);

void dispararForma (DISPARADOR d, double dx, double dy, FILA arena);

void shiftCarga (DISPARADOR d, char botao, int n);

void rajadaDisparos (DISPARADOR d, char botao, double dx, double dy, double ix, double iy, FILA arena);

void anexarCarregadores (DISPARADOR d, PILHA carregadorEsquerda, PILHA carregadorDireita);

void killDisparador (DISPARADOR d);


int getId_disparador (DISPARADOR d);

double getX_disparador (DISPARADOR d);

double getY_disparador (DISPARADOR d);

FormaSt *getEmDisparo (DISPARADOR d);

#endif