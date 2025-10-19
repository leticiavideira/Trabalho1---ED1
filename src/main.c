#include <stdio.h>
#include <stdlib.h>

#include "leitorGeo.h"
#include "argumentos.h"
#include "leitorDeArquivos.h"

int main (int arg, char *argVet[]){
    if (arg > 10) {
        printf ("Erro: muitos argumentos.\n");
        exit (1);
    }

    char *saidaPath = getValorOpt (arg, argVet, "o");
    char *entradaGeoPath = getValorOpt (arg, argVet, "f");
    char *sufixoCmd = getSufixoCmd (arg, argVet);

        if (entradaGeoPath == NULL || saidaPath == NULL){
            printf ("Erro: -f e -o sao necessarios.\n");
            exit (1);
        }

    DadosArquivo arqGeo = criarDadosArq (entradaGeoPath);

        if (arqGeo == NULL){
            printf ("ERRO ao criar dados do arquivo.\n");
            exit (1);
        }

    CHAO ch = processarGeo (arqGeo, saidaPath, sufixoCmd);

    destruirDadosArq (arqGeo);
    
    killGeo (ch);

    printf ("Processamento concluido com sucesso.\n");

    return 0;
}