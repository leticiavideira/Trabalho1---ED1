#ifndef LINHA_H
#define LINHA_H

typedef void* LINHA;

LINHA criaLinha (int i, double x1, double y1, double x2, double y2, char* cor);

int getId_L (LINHA l);

double getX1_L (LINHA l);

double getY1_L (LINHA l);

double getX2_L (LINHA l);

double getY2_L (LINHA l);

char* getCor_L (LINHA l);

double calcularArea_L (LINHA l);


void setId_L (LINHA l, int i);

void setX1_L (LINHA l, double x1);

void setY1_L (LINHA l, double y1);

void setX2_L (LINHA l, double x2);

void setY2_L (LINHA l, double y2);

void setCor_L (LINHA l, char* cor);


void kill_L (LINHA l);

#endif