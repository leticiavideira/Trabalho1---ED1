#ifndef CIRCULO_H
#define CIRCULO_H

typedef void* CIRCULO;

CIRCULO criaCirculo (int i, float x, float y, float r, char* corb, char* corp);


int getId_C (CIRCULO c);

float getX_C (CIRCULO c);

float getY_C (CIRCULO c);

float getR_C (CIRCULO c);

float calcularArea_C (CIRCULO c);

char* getCorB_C (CIRCULO c);

char* getCorP_C (CIRCULO c);


void setId_C (CIRCULO c, int i);

void setX_C (CIRCULO c, float x);

void setY_C (CIRCULO c, float y);

void setR_C (CIRCULO c, float r);

void setCorB_C (CIRCULO c, char* cb);

void setCorP_C (CIRCULO c, char* cp);


void kill_C (CIRCULO c);

#endif