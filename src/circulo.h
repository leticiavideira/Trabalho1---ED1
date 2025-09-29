#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdlib.h>

typedef void* CIRCULO;

CIRCULO criaCirculo (int i, float x, float y, float r, char* corb, char* corp);


int getCircI (CIRCULO c);

float getCircX (CIRCULO c);

float getCircY (CIRCULO c);

float getCircR (CIRCULO c);

char* getCircCorB (CIRCULO c);

char* getCircCorP (CIRCULO c);

#endif