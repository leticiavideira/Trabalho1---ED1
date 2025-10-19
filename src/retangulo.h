#ifndef RETANGULO_H
#define RETANGULO_H

typedef void* RETANGULO;

RETANGULO criaRetangulo (int i, float x, float y, float w, float h, char* corb, char* corp);


int getId_R (RETANGULO r);

float getX_R (RETANGULO r);

float getY_R (RETANGULO r);

float getW_R (RETANGULO r);

float getH_R (RETANGULO r);

float calcularArea_R (RETANGULO r);

char* getCorB_R (RETANGULO r);

char* getCorP_R (RETANGULO r);


void setId_R (RETANGULO r, int i);

void setX_R (RETANGULO r, float x);

void setY_R (RETANGULO r, float y);

void setW_R (RETANGULO r, float w);

void setH_R (RETANGULO r, float h);

void setCorB_R (RETANGULO r, char* cb);

void setCorP_R (RETANGULO r, char* cp);


void kill_R (RETANGULO r);

#endif