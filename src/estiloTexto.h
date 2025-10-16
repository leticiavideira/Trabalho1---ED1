#ifndef ESTILOTEXTO_H
#define ESTILOTEXTO_H

typedef void* ESTILO_TEXTO;

ESTILO_TEXTO criaEstiloTexto (char* fFamily, char* fWeight, int fSize);

char* getfFamily_T (ESTILO_TEXTO ts);

char* getfWeight_T (ESTILO_TEXTO ts);

int getfSize_T (ESTILO_TEXTO ts);

void killEstiloTexto (ESTILO_TEXTO ts);

#endif