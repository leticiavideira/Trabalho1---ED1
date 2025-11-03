#include <stdio.h>
#include <stdlib.h>

#include "leitorGeo.h"
#include "leitorQry.h"
#include "argumentos.h"
#include "leitorDeArquivos.h"

int main (int arg, char *argVet[]){

    //Validação inicial dos parâmetros
    if (arg < 5) {
        printf("Uso: ./ted [-e <dir_base>] -f <arq.geo> [-q <arq.qry>] -o <dir_saida>\n");
        return 1;
    }


    //Leitura dos parâmentros de linha de comando
    char *entradaBasePath = getValorOpt(arg, argVet, "e");
    char *saidaPath = getValorOpt (arg, argVet, "o");
    char *entradaGeoPath = getValorOpt (arg, argVet, "f");
    char *entradaQryPath = getValorOpt (arg, argVet, "q");
    char *sufixoCmd = getSufixoCmd (arg, argVet);

        if (entradaGeoPath == NULL || saidaPath == NULL){
            printf ("Erro: -f e -o sao necessarios.\n");
            exit (1);
        }

    
    // --- Monta os caminhos completos dos arquivos de entrada ---
    char geoPath[1024];
    char qryPath[1024];

    // Monta o caminho do arquivo .geo com base em -e (se fornecido)
    if (entradaBasePath != NULL) {
        snprintf(geoPath, sizeof(geoPath), "%s/%s", entradaBasePath, entradaGeoPath);
    } else {
        snprintf(geoPath, sizeof(geoPath), "%s", entradaGeoPath);
    }

    // Monta o caminho do arquivo .qry (se fornecido)
    if (entradaQryPath != NULL) {
        if (entradaBasePath != NULL) {
            snprintf(qryPath, sizeof(qryPath), "%s/%s", entradaBasePath, entradaQryPath);
        } else {
            snprintf(qryPath, sizeof(qryPath), "%s", entradaQryPath);
        }
    }


    // --- Leitura e processamento do arquivo .geo ---
    DadosArquivo arqGeo = criarDadosArq (geoPath);

        if (arqGeo == NULL){
            printf ("ERRO ao criar dados do arquivo.\n");
            exit (1);
        }

    // Cria o "chão" e processa o conteúdo do arquivo .geo
    CHAO chao = processarGeo (arqGeo, saidaPath, sufixoCmd);


    // --- Leitura e processamento do arquivo .qry ---
    if (entradaQryPath != NULL){
        DadosArquivo arqQry = criarDadosArq (qryPath);
        if (arqQry == NULL){
            printf ("Erro ao criar DadosArquivo para .qry\n");
            destruirDadosArq (arqGeo);
            killGeo (chao);
            exit (1);

        }
        // Executa os comandos do .qry e gera as saídas correspondentes
        QRY qry = exeQryCmd (arqQry, arqGeo, chao, saidaPath);
        // Libera memória associada ao .qry
        destruirDadosArq (arqQry);
        killQry (qry);
    }


    // --- Liberação de memória e finalização ---
    destruirDadosArq (arqGeo);
    
    killGeo (chao);

    return 0;
}