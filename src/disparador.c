#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disparador.h"
#include "pilha.h"
#include "fila.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct {
    int id;
    double x, y;
    PILHA cargaEsquerda;
    PILHA cargaDireita;
    FormaSt *emDisparo;
} disparadorSt;


DISPARADOR criarDisparador (int id, double x, double y){
    disparadorSt *d = (disparadorSt *) malloc (sizeof (disparadorSt));
        if (d == NULL){
            printf ("Erro ao alocar memoria para o disparador.\n");
            return NULL;
        }
    
    d->id = id;
    d->x = x;
    d->y = y;
    d->cargaDireita = criaPilha ();
    d->cargaEsquerda = criaPilha ();
    d->emDisparo = NULL;

        if (d->cargaDireita == NULL || d->cargaEsquerda == NULL){
            killPilha (d->cargaDireita);
            killPilha (d->cargaEsquerda);
            free (d);
            return NULL;
        }

    return ((DISPARADOR) d);
}

void posicionarDisparador (DISPARADOR d, double x, double y){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;

    d1->x = x;
    d1->y = y;
}

void dispararForma (DISPARADOR d, double dx, double dy, FILA arena){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL || d1->emDisparo == NULL)
            return;

    FormaSt *formaDisparada = d1->emDisparo;
    void *dataForma = formaDisparada->data;

    double localFinalX = d1->x + dx;
    double localFinalY = d1->y + dy;

        switch (formaDisparada->tipoF){
            case CIRCLE:
                setX_C (dataForma, localFinalX);
                setY_C (dataForma, localFinalY);
                break;
            case RECTANGLE:
                setX_R (dataForma, localFinalX);
                setY_R (dataForma, localFinalY);
                break;
            case TEXT:
                setX_T (dataForma, localFinalX);
                setY_T (dataForma, localFinalY);
                break;
            case LINE: {
                double x1 = getX1_L (dataForma);
                double y1 = getY1_L (dataForma);
                double x2 = getX2_L (dataForma);
                double y2 = getY2_L (dataForma);

                double moveX = localFinalX - x1;
                double moveY = localFinalY - y1;

                setX1_L (dataForma, x1 + moveX);
                setY1_L (dataForma, y1 + moveY);
                setX2_L (dataForma, x2 + moveX);
                setY2_L (dataForma, y2 + moveY);
                break;
            }
            default:
                break;
        }
    
    pushFila (arena, formaDisparada);
    d1->emDisparo = NULL;

}

void shiftCarga (DISPARADOR d, char botao, int n){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;

    for (int i = 0 ; i < n ; i++){
        FormaSt *newForma = NULL;

        if (botao == 'd'){
            if (pilhaVazia (d1->cargaDireita))
                break;
            
            newForma = (FormaSt *) popPilha (d1->cargaDireita);

            if (d1->emDisparo != NULL) {
                pushPilha (d1->cargaEsquerda, d1->emDisparo);
            }

        } else if (botao == 'e'){
            if (pilhaVazia (d1->cargaEsquerda))
                break;

            newForma = (FormaSt *) popPilha (d1->cargaEsquerda);

            if (d1->emDisparo != NULL){
                pushPilha (d1->cargaDireita, d1->emDisparo);
            }

        } else {
            break;

        }

        d1->emDisparo = newForma;
    }
}

void rajadaDisparos (DISPARADOR d, char botao, double dx, double dy, double ix, double iy, FILA arena){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;
    
    PILHA cargaSelecionada = (botao == 'd') ? d1->cargaDireita : d1->cargaEsquerda;

    while (!pilhaVazia (cargaSelecionada)){
        shiftCarga (d, botao, 1);
        dispararForma (d, dx, dy, arena);

        dx += ix;
        dy += iy;
    }    
}

void anexarCarregadores (DISPARADOR d, PILHA carregadorEsquerda, PILHA carregadorDireita){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;

    killPilha (d1->cargaDireita);
    killPilha (d1->cargaEsquerda);

    d1->cargaDireita = carregadorDireita;
    d1->cargaEsquerda = carregadorEsquerda;
}

void killDisparador (DISPARADOR d){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;

    killPilha (d1->cargaDireita);
    killPilha (d1->cargaEsquerda);
    free (d1);
}


int getId_disparador (DISPARADOR d){
    disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return -1;
    
    return (d1 != NULL) ? d1->id : -1;
}

double getX_disparador (DISPARADOR d){
     disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return 0.0;
    
    return (d1 != NULL) ? d1->x : 0.0;
}

double getY_disparador (DISPARADOR d){
     disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return 0.0;
    
    return (d1 != NULL) ? d1->y : 0.0;
}

FormaSt *getEmDisparo (DISPARADOR d){
     disparadorSt *d1 = (disparadorSt *) d;
        if (d1 == NULL)
            return;
    
    return (d1 != NULL) ? d1->emDisparo : NULL;
}
