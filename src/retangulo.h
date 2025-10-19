#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* RETANGULO;

RETANGULO criaRetangulo (int i, double x, double y, double w, double h, char* corb, char* corp);


int getId_R (RETANGULO r);

double getX_R (RETANGULO r);

double getY_R (RETANGULO r);

double getW_R (RETANGULO r);

double getH_R (RETANGULO r);

double calcularArea_R (RETANGULO r);

char* getCorB_R (RETANGULO r);

char* getCorP_R (RETANGULO r);


void setId_R (RETANGULO r, int i);

void setX_R (RETANGULO r, double x);

void setY_R (RETANGULO r, double y);

void setW_R (RETANGULO r, double w);

void setH_R (RETANGULO r, double h);

void setCorB_R (RETANGULO r, char* cb);

void setCorP_R (RETANGULO r, char* cp);


void kill_R (RETANGULO r);

#endif