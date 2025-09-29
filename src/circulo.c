#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circulo.h"

#define pi 3.141592653589793

typedef struct{
    int i;
    float x;
    float y;
    float r;
    float area;
    char *corb;
    char *corp;
} circulo;

float calculaAreaCirc(float r){
    return pi * r * r;
}

CIRCULO criaCirculo (int i, float x, float y, float r, char* corb, char* corp){
    circulo *c = (circulo*) malloc (sizeof(circulo));

    if (c == NULL){
        printf ("Erro ao alocar memoria para criacao do circulo.\n");
            exit(1);
    }

    c->i = i;
    c->x = x;
    c->y = y;
    c->r = r;
    c->area = calculaArea(r);

    c->corb = (char*) malloc (sizeof(char) * strlen(corb) + 1);
        if (c->corb == NULL){
            printf("Erro ao alocar memoria para cor de borda.\n");
                exit(1);
        }

    c->corp = (char*) malloc (sizeof(char) * strlen(corp) + 1);
        if(c->corp == NULL){
            printf("Erro ao alocar memoria para cor de preenchimento.\n");
                exit(1);
        }

    strcpy (c->corb, corb);
    strcpy (c->corp, corp);

    return ((circulo*)c);
}