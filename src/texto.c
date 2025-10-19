#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "texto.h"

typedef struct {
    int i;
    double x, y;
    char* corb;
    char* corp;
    char a;
    char* txto;
    
} texto;


TEXTO criaTexto (int i, double x, double y, char* corb, char* corp, char a, char* txto){
    texto *t = (texto*) malloc (sizeof(texto));

    if (t == NULL){
        printf ("Erro ao alocar memoria para criacao do texto.\n");
            exit(1);
    }

    t->i = i;
    t->x = x;
    t->y = y;

    t->corb = (char*) malloc (sizeof(char) * strlen(corb) + 1);
        if(t->corb == NULL){
            printf("Erro ao alocar memoria para cor de borda.\n");
                exit (1);
        }
    strcpy (t->corb, corb);

    t->corp = (char*) malloc (sizeof(char) * strlen(corp) + 1);
        if(t->corp == NULL){
            printf("Erro ao alocar memoria para cor de preenchimento.\n");
                exit (1);
        }
    strcpy (t->corp, corp);

    t->a = a;

    t->txto = (char*) malloc (sizeof(char) * strlen(txto) + 1);
        if(t->txto == NULL){
            printf("Erro ao alocar memoria.\n");
                exit (1);
        }
    strcpy (t->txto, txto);

    return (texto *) t;
}

int getId_T (TEXTO t){
    texto *t1 = ((texto*) t);
    return (t1->i);
}

double getX_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->x);
}

double getY_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->y);
}

char* getCorb_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->corb);
}

char* getCorp_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->corp);
}

char getA_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->a);
}

char* getTxto_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (t1->txto);
}

double comprimento_T (TEXTO t){
    texto *t1 = ((texto*) t);
    return (10 * strlen(t1->txto));
}

double calcX1_T (TEXTO t){
    texto *t1 = ((texto*) t);
    
    double x1;

        if (t1->a == 'i'){
            x1 = t1->x;

        } else if (t1->a == 'f'){
            x1 = (t1->x - comprimento_T(t1));

        } else if (t1->a == 'm'){
            x1 = (t1->x - (comprimento_T(t1) / 2));

        } else {
            printf ("Ancora nao reconhecida.\n");
        }
    
    return x1;
}

double calcX2_T (TEXTO t){
    texto *t1 = ((texto*) t);

    double x2;

        if (t1->a == 'i'){
            x2 = (t1->x + comprimento_T(t1));

        } else if (t1->a == 'f'){
            x2 = t1->x;

        } else if (t1->a == 'm'){
            x2 = (t1->x + (comprimento_T(t1) / 2));

        } else {
            printf ("Ancora nao reconhecida.\n");
        }

    return x2;

}



double calcularArea_T (TEXTO t){
     texto *t1 = ((texto*) t);
    return (20 * strlen(t1->txto));
}


void setId_T (TEXTO t, int i){
    texto *t1 = ((texto*) t);
    t1->i = i;
}

void setX_T (TEXTO t, double x){
    texto *t1 = ((texto*) t);
    t1->x = x;
}

void setY_T (TEXTO t, double y){
    texto *t1 = ((texto*) t);
    t1->y = y;
}

void setCorb_T (TEXTO t, char* cb){
    texto *t1 = ((texto*) t);
    
    free(t1->corb);

    t1->corb = (char*) malloc (sizeof(char) * strlen(cb) + 1);

        if(t1->corb == NULL){
            printf ("Erro ao alocar memoria./n");
                exit(1);
        }

    strcpy (t1->corb, cb);
}

void setCorp_T (TEXTO t, char* cp){
    texto *t1 = ((texto*) t);

    free(t1->corp);

    t1->corp = (char*) malloc (sizeof(char) * strlen(cp) + 1);

        if(t1->corp == NULL){
            printf ("Erro ao alocar memoria./n");
                exit(1);
        }

    strcpy (t1->corp, cp);
}

void setA_T (TEXTO t, char a){
    texto *t1 = ((texto*) t); 
    t1->a = a;
}

void setTxto_T (TEXTO t, char* txto){
    texto *t1 = ((texto*) t);

    free(t1->txto);

    t1->txto = (char*) malloc (sizeof(char) * strlen(txto) + 1);

        if(t1->txto == NULL){
            printf ("Erro ao alocar memoria./n");
                exit(1);
        }

    strcpy (t1->txto, txto);
}

void kill_T (TEXTO t){
    texto *t1 = ((texto*) t);

    free(t1->corb);
    free(t1->corp);
    free(t1->txto);
    free(t1);
}
