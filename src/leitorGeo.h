#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H

#include "fila.h"
#include "pilha.h"
#include "leitorDeArquivos.h"

typedef void* CHAO;

CHAO processarGeo (DadosArquivo arqData, char *saidaPath, char *sufixoCmd);

FILA getFChao (CHAO chao);

PILHA getPFormasChaoFree (CHAO chao);

void killGeo (CHAO chao);

#endif