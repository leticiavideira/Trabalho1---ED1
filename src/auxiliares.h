#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "fila.h"
#include "pilha.h"
#include "leitorGeo.h"
#include "leitorQry.h"
#include "struct.c"

int getDisparadorIndexPorId (disparadorSt **disparador, int contDisparos, int id);

void killForma (FormaSt *f);

FormaSt *encapsularForma (formaTipo tp, void *data);

double getAreaForma (formaTipo tp, void *formaData);

bBox criarBBoxParaForma (PosicaoFormaASt *f);

//bool
int sobreposicaoBBox (bBox a, bBox b);
//bool
int sobreposicaoFormas (PosicaoFormaASt *a, PosicaoFormaASt *b);


FormaSt *clonarCorb (FormaSt *src, char *novaCorB);

FormaSt *clonarCoresTrocadas (FormaSt *src);


FormaSt *clonarComPosicao (FormaSt *src, double x, double y, CHAO chao);

FormaSt *clonarEmComCorB (FormaSt *src, char *novaCorB, double x, double y, CHAO chao);

FormaSt *clonarEmComCoresTrocadas (FormaSt *src, double x, double y, CHAO chao);

#endif