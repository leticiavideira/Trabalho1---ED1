#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdlib.h>

typedef void* RETANGULO;

RETANGULO criaRetangulo (int i, float x, float y, float w, float h, char* corb, char* corp);


int getRectI (RETANGULO r);

float getRectX (RETANGULO r);

float getRectY (RETANGULO r);

float getRectR (RETANGULO r);

char* getRectCorB (RETANGULO r);

char* getRectCorP (RETANGULO r);

#endif