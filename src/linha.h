#ifndef LINHA_H
#define LINHA_H

typedef void* LINHA;

LINHA criaLinha (int i, float x1, float y1, float x2, float y2, char* cor);

int getId_L (LINHA l);

float getX1_L (LINHA l);

float getY1_L (LINHA l);

float getX2_L (LINHA l);

float getY2_L (LINHA l);

char* getCor_L (LINHA l);

float calcularArea_L (LINHA l);


void setId_L (LINHA l, int i);

void setX1_L (LINHA l, float x1);

void setY1_L (LINHA l, float y1);

void setX2_L (LINHA l, float x2);

void setY2_L (LINHA l, float y2);

void setCor_L (LINHA l, char* cor);


void kill_L (LINHA l);

#endif