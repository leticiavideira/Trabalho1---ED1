#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "linha.h"

typedef struct{
    int i;
    double x1, y1;
    double x2, y2;
    char* cor;
} linha;

LINHA criaLinha (int i, double x1, double y1, double x2, double y2, char* cor){
    linha *l = (linha*) malloc (sizeof(linha));

    if (l == NULL){
        printf ("Erro ao alocar memoria para criacao da linha");
        exit(1);
    }

    l->i = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = (char*) malloc (sizeof(char) * strlen(cor) + 1);

        if(l->cor == NULL){
            printf("Erro ao alocar memoria para cor da linha.\n");
                exit (1);
        }
    
    strcpy (l->cor, cor);

    return (linha*) l;
}

int getId_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->i);
}

double getX1_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->x1);
}

double getY1_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->y1);
}

double getX2_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->x2);
}

double getY2_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->y2);
}

char* getCor_L (LINHA l){
    linha *l1 = ((linha*) l);
    return (l1->cor);
}

double calcularArea_L (LINHA l){
    linha *l1 = ((linha*) l);
    
    double a = (l1->x2) - (l1->x1);
    double b = (l1->y2) - (l1->y1);

    return ( 2 * sqrt(pow(a, 2) + pow(b, 2)));
}


void setId_L (LINHA l, int i){
    linha *l1 = ((linha*) l);
    l1->i = i;
}

void setX1_L (LINHA l, double x1){
    linha *l1 = ((linha*) l);
    l1->x1 = x1;
}

void setY1_L (LINHA l, double y1){
    linha *l1 = ((linha*) l);
    l1->y1 = y1;
}

void setX2_L (LINHA l, double x2){
    linha *l1 = ((linha*) l);
    l1->x2 = x2;
}

void setY2_L (LINHA l, double y2){
    linha *l1 = ((linha*) l);
    l1->y2 = y2;
}

void setCor_L (LINHA l, char* cor){
    linha *l1 = ((linha*) l);

    free(l1->cor);

    l1->cor = (char*) malloc (sizeof(char) * strlen(cor) + 1);

    if(l1->cor == NULL){
        printf("Erro ao alocar memoria.\n");
        exit (1);
    }

    strcpy (l1->cor, cor);
}


void kill_L (LINHA l){
    linha *l1 = ((linha*) l);
    free(l1->cor);
    free(l1);
}
