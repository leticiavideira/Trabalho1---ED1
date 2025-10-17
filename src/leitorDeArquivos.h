#ifndef LEITOR_DE_ARQUIVOS_H
#define LEITOR_DE_ARQUIVOS_H

#include "fila.h"

typedef void* DadosArquivo;

DadosArquivo criarDadosArq (char * arqPath);


char* getPathArq (DadosArquivo arqData);

char* getNomeArq (DadosArquivo arqData);

FILA getFilaLinhasArq (DadosArquivo arqData);


void destruirDadosArq (DadosArquivo arqData);

#endif