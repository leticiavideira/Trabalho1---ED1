#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retangulo.h"

typedef struct {
    int i;
    double x, y;
    double w, h;
    char* corb;
    char* corp;
} retangulo;

RETANGULO criaRetangulo (int i, double x, double y, double w, double h, char* corb, char* corp){
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

int getId_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->i);
}

double getX_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->x);
}

double getY_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->y);
}

double getW_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->w);
}

double getH_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->h);
}

double calcularArea_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->w * r1->h);
}

char* getCorB_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->corb);
}

char* getCorP_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    return (r1->corp);
}



void setId_R (RETANGULO r, int i){
    retangulo *r1 = ((retangulo*) r);
    r1->i = i;
}

void setX_R (RETANGULO r, double x){
    retangulo *r1 = ((retangulo*) r);
    r1->x = x;
}

void setY_R (RETANGULO r, double y){
    retangulo *r1 = ((retangulo*) r);
    r1->y = y;
}

void setW_R (RETANGULO r, double w){
    retangulo *r1 = ((retangulo*) r);
    r1->w = w;
}

void setH_R (RETANGULO r, double h){
    retangulo *r1 = ((retangulo*) r);
    r1->h = h;
}

void setCorB_R (RETANGULO r, char* cb){
    retangulo *r1 = ((retangulo*) r);

    free(r1->corb);

    r1->corb = (char*) malloc (sizeof(char) * strlen(cb) + 1);

    if (r1->corb == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy (r1->corb, cb);
}

void setCorP_R (RETANGULO r, char* cp){
    retangulo *r1 = ((retangulo*) r);

    free(r1->corp);

    r1->corp = (char*) malloc (sizeof(char) * strlen(cp) + 1);

    if (r1->corp == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy (r1->corp, cp);
}


void kill_R (RETANGULO r){
    retangulo *r1 = ((retangulo*) r);
    free (r1->corb);
    free (r1->corp);
    free (r1);
}