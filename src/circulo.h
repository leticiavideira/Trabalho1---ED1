#ifndef CIRCULO_H
#define CIRCULO_H

typedef void* CIRCULO;

CIRCULO criaCirculo (int i, double x, double y, double r, char* corb, char* corp);


int getId_C (CIRCULO c);

double getX_C (CIRCULO c);

double getY_C (CIRCULO c);

double getR_C (CIRCULO c);

double calcularArea_C (CIRCULO c);

char* getCorB_C (CIRCULO c);

char* getCorP_C (CIRCULO c);


void setId_C (CIRCULO c, int i);

void setX_C (CIRCULO c, double x);

void setY_C (CIRCULO c, double y);

void setR_C (CIRCULO c, double r);

void setCorB_C (CIRCULO c, char* cb);

void setCorP_C (CIRCULO c, char* cp);


void kill_C (CIRCULO c);

#endif