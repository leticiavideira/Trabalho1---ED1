#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retangulo.h"

typedef struct {
    int i;
    float x, y;
    float w, h;
    float area;
    char* corb;
    char* corp;
} retangulo;

float calculaAreaRet (float w, float h){
    return (w * h);
}

RETANGULO criaRetangulo (int i, float x, float y, float w, float h, char* corb, char* corp){
    retangulo *r = (retangulo*) malloc (sizeof(retangulo));
        if (r == NULL){
            printf ("Erro ao alocar memoria para criacao do retangulo.\n");
                exit(1);
        }
    
    r->i = i;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->area = calculaAreaRet (w, h);

    r->corb = (char*) malloc (sizeof(char) * strlen(corb) + 1);
        if (r->corb == NULL){
            printf("Erro ao alocar memoria para cor de borda.\n");
                exit(1);
        }

    r->corp = (char*) malloc (sizeof(char) * strlen(corp) + 1);
        if(r->corp == NULL){
            printf("Erro ao alocar memoria para cor de preenchimento.\n");
                exit(1);
        }

    strcpy (r->corb, corb);
    strcpy (r->corp, corp);

     return ((retangulo*)r);
}