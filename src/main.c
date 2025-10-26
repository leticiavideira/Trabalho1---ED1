#include <stdio.h>
#include <stdlib.h>

#include "leitorGeo.h"
#include "leitorQry.h"
#include "argumentos.h"
#include "leitorDeArquivos.h"

int main (int arg, char *argVet[]){
    if (arg > 10) {
        printf ("Erro: muitos argumentos.\n");
        exit (1);
    }

    char *saidaPath = getValorOpt (arg, argVet, "o");
    char *entradaGeoPath = getValorOpt (arg, argVet, "f");
    char *entradaQryPath = getValorOpt (arg, argVet, "q");
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

    CHAO chao = processarGeo (arqGeo, saidaPath, sufixoCmd);

    if (entradaQryPath != NULL){
        DadosArquivo arqQry = criarDadosArq (entradaQryPath);
        if (arqQry == NULL){
            printf ("Erro ao criar DadosArquivo para .qry\n");
            killGeo (chao);
            exit (1);

        }

        QRY qry = exeQryCmd (arqQry, arqGeo, chao, saidaPath);
        destruirDadosArq (arqQry);
        killQry (qry);
    }

    destruirDadosArq (arqGeo);
    
    killGeo (chao);

    return 0;
}