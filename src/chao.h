#ifndef CHAO_H
#define CHAO_H

#include "formas.h"

typedef struct stChao CHAO;

CHAO *criaChao ();

int chaoVazio (CHAO *c);

void colocarNoChao (CHAO *c, formaTipo *f);

formaTipo *retirarDoChao (CHAO *c);

void killChao (CHAO *c);

#endif