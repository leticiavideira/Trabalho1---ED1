#ifndef TEXTO_H
#define TEXTO_H

typedef void* TEXTO;

TEXTO criaTexto (int i, float x, float y, char* corb, char* corp, char a, char* txto, char* fFamily, char* fWeight, char* fSize);

int getId_T (TEXTO t);

float getX_T (TEXTO t);

float getY_T (TEXTO t);

char* getCorb_T (TEXTO t);

char* getCorp_T (TEXTO t);

char getA_T (TEXTO t);

char* getTxto_T (TEXTO t);

char* getfFamily_T (TEXTO t);

char* getfWeight_T (TEXTO t);

char* getfSize_T (TEXTO t);


float calcularArea_T (TEXTO t);


void setId_T (TEXTO t, int i);

void setX_T (TEXTO t, float x);

void setY_T (TEXTO t, float y);

void setCorb_T (TEXTO t, char* cb);

void setCorp_T (TEXTO t, char* cp);

void setA_T (TEXTO t, char a);

void setTxto_T (TEXTO t, char* txto);

void setfFamily_T (TEXTO t, char* fFamily);

void setfWeight_T (TEXTO t, char* fWeight);

void setfSize_T (TEXTO t, char* fSize);


void kill_T (TEXTO t);

#endif