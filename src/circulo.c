#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circulo.h"

#define pi 3.141592653589793

typedef struct{
    int i;
    double x;
    double y;
    double r;
    char *corb;
    char *corp;
} circulo;

CIRCULO criaCirculo (int i, double x, double y, double r, char* corb, char* corp){
    circulo *c = (circulo*) malloc (sizeof(circulo));

    if (c == NULL){
        printf ("Erro ao alocar memoria para criacao do circulo.\n");
            exit(1);
    }

    c->i = i;
    c->x = x;
    c->y = y;
    c->r = r;

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

int getId_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->i);

}

double getX_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->x);

}

double getY_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->y);

}

double getR_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->r);

}

double calcularArea_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->r * c1->r * pi);

}

char* getCorB_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->corb);

}

char* getCorP_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    return (c1->corp);

}




void setId_C (CIRCULO c, int i){
    circulo *c1 = ((circulo*) c);
    c1->i = i;
}

void setX_C (CIRCULO c, double x){
    circulo *c1 = ((circulo*) c);
    c1->x = x;
}

void setY_C (CIRCULO c, double y){
    circulo *c1 = ((circulo*) c);
    c1->y = y;
}

void setR_C (CIRCULO c, double r){
    circulo *c1 = ((circulo*) c);
    c1->r = r;
}

void setCorB_C (CIRCULO c, char* cb){
    circulo *c1 = ((circulo*) c);

    free (c1->corb);

    c1->corb = (char*) malloc (sizeof(char) * (strlen(cb) + 1));

    if (c1->corb == NULL){
        printf ("Erro ao alocar memoria.\n");
        exit(1);
    }
    
    strcpy (c1->corb, cb);

}

void setCorP_C (CIRCULO c, char* cp){
    circulo *c1 = ((circulo*) c);

    free (c1->corp);

    c1->corp = (char*) malloc (sizeof(char) * (strlen(cp) + 1));

    if (c1->corp == NULL) {
        printf ("Erro ao alocar memoria. \n");
        exit(1);
    }

    strcpy (c1->corp, cp);
}

void kill_C (CIRCULO c){
    circulo *c1 = ((circulo*) c);
    free (c1->corb);
    free (c1->corp);
    free (c1);
}
