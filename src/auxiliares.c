#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliares.h"
#include "cor.h"
#include "pilha.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estiloTexto.h"

typedef struct{
    formaTipo tipoF;
    void* data;
} FormaSt;

typedef struct{
    int id;
    PILHA *formas;
}carregadorSt;

typedef struct {
    int id;
    double x, y;
    carregadorSt *cargaEsquerda;
    carregadorSt *cargaDireita;
    FormaSt *emDisparo;
    int cargaEsqId;
    int cargaDirId;
} disparadorSt;

typedef struct{
    FormaSt *forma;
    double x, y;
    int iA; //bool
    double disparadorX;
    double disparadorY;
} PosicaoFormaASt;

typedef struct {
    double minX, minY;
    double maxX, maxY;
} bBox;


int getDisparadorIndexPorId (disparadorSt **disparador, int contDisparos, int id){
    for (int i = 0 ; i < contDisparos ; i++){
        if ((*disparador)[i].id == id){
            return i;
        }
    }

    return -1;
}

void killForma (FormaSt *f){
    if (f == NULL){
        return;
    }

    switch (f->tipoF){
        case CIRCLE: {
            kill_C ((CIRCULO) f->data);
            break;
        }
        case RECTANGLE: {
            kill_R ((RETANGULO) f->data);
            break;
        }
        case LINE: {
            kill_L ((LINHA) f->data);
            break;
        }
        case TEXT: {
            kill_T ((TEXTO) f->data);
            break;
        }
        case TEXT_STYLE: 
            break;
    }

    free (f);
}


FormaSt *encapsularForma (formaTipo tp, void *data){
    FormaSt *f = (FormaSt *) malloc (sizeof (FormaSt));
        if (f == NULL){
            printf ("Erro ao alocar memoria para encapsular forma.\n");
            exit (1);
        }
    
    f->tipoF = tp;
    f->data = data;
    
    return f;
}

double getAreaForma (formaTipo tp, void *formaData){
    switch (tp){
        case CIRCLE: {
            double a = calcularArea_C ((CIRCULO) formaData);
            return a;
        }
        case RECTANGLE: {
            double a = calcularArea_R ((RETANGULO) formaData);
            return a;
        }
        case TEXT: {
            double a = calcularArea_T ((TEXTO) formaData);
            return a;
        }
        case LINE: {
            double a = calcularArea_L ((LINHA) formaData);
            return a;
        }
        case TEXT_STYLE:
            return 0.0;
    
    }

    return 0.0;
}


bBox criarBBoxParaForma (PosicaoFormaASt *f){
    bBox box;

    switch (f->forma->tipoF){
        case CIRCLE: {
            double r = getR_C ((CIRCULO) f->forma->data);
            box.minX = f->x - r;
            box.maxX = f->x + r;
            box.minY = f->y - r;
            box.maxY = f->y + r;
            break;
        }
        case RECTANGLE: {
            double w = getW_R ((RETANGULO) f->forma->data);
            double h = getH_R ((RETANGULO) f->forma->data);
            box.minX = f->x;
            box.minY = f->y;
            box.maxX = f->x + w;
            box.maxY = f->y + h;
            break;
        }
        case LINE: {
            double x1 = getX1_L ((LINHA) f->forma->data);
            double y1 = getY1_L ((LINHA) f->forma->data);
            double x2 = getX2_L ((LINHA) f->forma->data);
            double y2 = getY2_L ((LINHA) f->forma->data);
            double dx = x2 - x1;
            double dy = y2 - y1;
            double minLocalX = (dx < 0.0) ? dx : 0.0;
            double maxLocalX = (dx > 0.0) ? dx : 0.0;
            double minLocalY = (dy < 0.0) ? dy : 0.0;
            double maxLocalY = (dy > 0.0) ? dy : 0.0;

            box.minX = f->x + minLocalX - 1.0;
            box.maxX = f->x + maxLocalX + 1.0;
            box.minY = f->y + minLocalY - 1.0;
            box.maxY = f->y + maxLocalY + 1.0;

            break;
        }
        case TEXT: {
            TEXTO t = (TEXTO) f->forma->data;
            char *txt = getTxto_T (t);
            int tam = (int) strlen (txt);
            double segTam = 10.0 * (double)tam;
            char ancora = getA_T (t);

            double x1 = f->x;
            double x2 = f->x;
            double y1 = f->y;
            double y2 = f->y;

            if (ancora == 'i' || ancora == 'I'){
                x2 = f->x + segTam;
                y2 = f->y;

            } else if (ancora == 'f' || ancora == 'F' || ancora == 'e' || ancora == 'E'){
                x1 = f->x - segTam;
                y1 = f->y;

            } else if (ancora == 'm' || ancora == 'M'){
                x1 = f->x - segTam * 0.5;
                y1 = f->y;
                x2 = f->x + segTam * 0.5;
                y2 = f->y;

            } else {
                x2 = f->x + segTam;
                y2 = f->y;
            }

            double dx = x2 - x1;
            double dy = y2 - y1;
            double minLocalX = (dx < 0.0) ? dx : 0.0;
            double maxLocalX = (dx > 0.0) ? dx : 0.0;
            double minLocalY = (dy < 0.0) ? dy : 0.0;
            double maxLocalY = (dy > 0.0) ? dy : 0.0;

            box.minX = x1 + minLocalX - 1.0;
            box.maxX = x1 + maxLocalX + 1.0;
            box.minY = y1 + minLocalY - 1.0;
            box.maxY = y1 + maxLocalY + 1.0;

            break;
        }
        case TEXT_STYLE: {
            box.minX = box.maxX = f->x;
            box.minY = box.maxY = f->y;
            break;
        }
    }

    return box;
}

//bool
int sobreposicaoBBox (bBox a, bBox b){
    if (a.maxX < b.minX)
        return 0;
    if (b.maxX < a.minX)
        return 0;
    if (a.maxY < b.minY)
        return 0;
    if (b.maxY < a.minY)
        return 0;

    return 1;
}

int sobreposicaoFormas (PosicaoFormaASt *a, PosicaoFormaASt *b){
    bBox aa = criarBBoxParaForma (a);
    bBox bb = criarBBoxParaForma (b);

    return sobreposicaoBBox (aa, bb);
}


FormaSt *clonarCorb (FormaSt *src, char *novaCorB){
    switch (src->tipoF){
        case CIRCLE: {
            CIRCULO c = (CIRCULO) src->data;
            int id = getId_C (c);
            double x = 0.0, y = 0.0;
            
            x = getX_C (c);
            y = getY_C (c);

            double r = getR_C (c);
            char *preenchimento = getCorP_C (c);

            CIRCULO novoC = criaCirculo (id, x, y, r, novaCorB, preenchimento);

            return encapsularForma (CIRCLE, novoC);
        }
        case RECTANGLE: {
            RETANGULO r = (RETANGULO) src->data;
            int id = getId_R (r);
            double x = getX_R (r);
            double y = getY_R (r);
            double w = getW_R (r);
            double h = getH_R (r);
            char *preenchimento = getCorP_R (r);

            RETANGULO novoR = criaRetangulo (id, x, y, w, h, novaCorB, preenchimento);

            return encapsularForma (RECTANGLE, novoR);
        }
        case LINE: {
            LINHA l = (LINHA) src->data;
            int id = getId_L (l);
            double x1 = getX1_L (l);
            double y1 = getY1_L (l);
            double x2 = getX2_L (l);
            double y2 = getY2_L (l);

            LINHA novaL = criaLinha (id, x1, y1, x2, y2, novaCorB);

            return encapsularForma (LINE, novaL);
        }
        case TEXT: {
            TEXTO t = (TEXTO) src->data;
            int id = getId_T (t);
            double x = getX_T (t);
            double y = getY_T (t);
            char *preenchimento = getCorp_T (t);
            char ancora = getA_T (t);
            char *txt = getTxto_T (t);

            TEXTO novoT = criaTexto (id, x, y, novaCorB, preenchimento, ancora, txt);

            return encapsularForma (TEXT, novoT);
        }
        case TEXT_STYLE: 
            return NULL;
    }
    
    return NULL;
}

FormaSt *clonarCoresTrocadas (FormaSt *src){
    switch (src->tipoF){
        case CIRCLE: {
            CIRCULO c = (CIRCULO) src->data;
            int id = getId_C (c);
            double x = getX_C (c);
            double y = getY_C (c);
            double r = getR_C (c);
            char *borda = getCorB_C (c);
            char *preenchimento = getCorP_C (c);

            CIRCULO novoC = criaCirculo (id, x, y, r, preenchimento, borda);

            return encapsularForma (CIRCLE, novoC);
        }
        case RECTANGLE: {
            RETANGULO r = (RETANGULO) src->data;
            int id = getId_R (r);
            double x = getX_R (r);
            double y = getY_R (r);
            double w = getW_R (r);
            double h = getH_R (r);
            char *borda = getCorB_R (r);
            char *preenchimento = getCorP_R (r);

            RETANGULO novoR = criaRetangulo (id, x, y, w, h, preenchimento, borda);

            return encapsularForma (RECTANGLE, novoR);
        }
        case LINE: {
            LINHA l = (LINHA) src->data;
            int id = getId_L (l);
            double x1 = getX1_L (l);
            double y1 = getY1_L (l);
            double x2 = getX2_L (l);
            double y2 = getY2_L (l);
            char *cor = getCor_L (l);
            char *invertida = inverterCor (cor);
                if (invertida == NULL){
                    return NULL;
                }
            
            LINHA novaL = criaLinha (id, x1, y1, x2, y2, invertida);

            free (invertida);

            return encapsularForma (LINE, novaL);
        }
        case TEXT: {
            TEXTO t = (TEXTO) src->data;
            int id = getId_T (t);
            double x = getX_T (t);
            double y = getY_T (t);
            char *borda = getCorb_T (t);
            char *preenchimento = getCorp_T (t);
            char ancora = getA_T (t);
            char *txt = getTxto_T (t);

            TEXTO novoT = criaTexto (id, x, y, preenchimento, borda, ancora, txt);

            return encapsularForma (TEXT, novoT);
        }
        case TEXT_STYLE: 
            return NULL;
    }

    return NULL;
}


FormaSt *clonarComPosicao (FormaSt *src, double x, double y, CHAO chao){
    if (src == NULL){
        return NULL;
    }

    FormaSt *clone = NULL;

    switch (src->tipoF){
        case CIRCLE: {
            CIRCULO c = (CIRCULO) src->data;
            int id = getId_C (c);
            double r = getR_C (c);
            char *borda = getCorB_C (c);
            char *preenchimento = getCorP_C (c);

            CIRCULO novoC = criaCirculo (id, x, y, r, borda, preenchimento);

            clone = encapsularForma (CIRCLE, novoC);

            break;
        }
        case RECTANGLE: {
            RETANGULO r = (RETANGULO) src->data;
            int id = getId_R (r);
            double w = getW_R (r);
            double h = getH_R (r);
            char *borda = getCorB_R (r);
            char *preenchimento = getCorP_R (r);

            RETANGULO novoR = criaRetangulo (id, x, y, w, h, borda, preenchimento);

            clone = encapsularForma (RECTANGLE, novoR);

            break;
        }
        case LINE: {
            LINHA l = (LINHA) src->data;
            int id = getId_L (l);
            double dx = getX2_L (l) - getX1_L (l);
            double dy = getY2_L (l) - getY1_L (l);
            char *cor = getCor_L (l);

            LINHA novaL = criaLinha (id, x, y, (x + dx), (y + dy), cor);

            clone = encapsularForma (LINE, novaL);

            break;
        }
        case TEXT: {
            TEXTO t = (TEXTO) src->data;
            int id = getId_T (t);
            char *borda = getCorb_T (t);
            char *preenchimento = getCorp_T (t);
            char ancora = getA_T (t);
            char *txt = getTxto_T (t);
            
            TEXTO novoT = criaTexto (id, x, y, borda, preenchimento, ancora, txt);

            clone = encapsularForma (TEXT, novoT);

            break;
        }
        case TEXT_STYLE:
            return NULL;
    }

    if (clone != NULL && chao != NULL){
        pushPilha (getPFormasChaoFree (chao), clone);
    }

    return clone;
}

FormaSt *clonarEmComCorB (FormaSt *src, char *novaCorB, double x, double y, CHAO chao){
    if (src == NULL){
        return NULL;
    }

    FormaSt *clone = NULL;

    switch (src->tipoF) {
        case CIRCLE: {
            CIRCULO c = (CIRCULO) src->data;
            int id = getId_C (c);
            double r = getR_C (c);
            char *preenchimento = getCorP_C (c);

            CIRCULO novoC = criaCirculo (id, x, y, r, novaCorB, preenchimento);

            clone = encapsularForma (CIRCLE, novoC);

            break;
        }
        case RECTANGLE: {
            RETANGULO r = (RETANGULO) src->data;
            int id = getId_R (r);
            double w = getW_R (r);
            double h = getH_R (r);
            char *preenchimento = getCorP_R (r);

            RETANGULO novoR = criaRetangulo (id, x, y, w, h, novaCorB, preenchimento);

            clone = encapsularForma (RECTANGLE, novoR);

            break;
        }
        case LINE: {
            LINHA l = (LINHA) src->data;
            int id = getId_L (l);
            double dx = getX2_L (l) - getX1_L (l);
            double dy = getY2_L (l) - getY1_L (l);

            LINHA novaL = criaLinha (id, x, y, (x + dx), (y + dy), novaCorB);

            clone = encapsularForma (LINE, novaL);

            break;
        }
        case TEXT: {
            TEXTO t = (TEXTO) src->data;
            int id = getId_T (t);
            char *preenchimento = getCorp_T (t);
            char ancora = getA_T (t);
            char *txt = getTxto_T (t);

            TEXTO novoT = criaTexto (id, x, y, novaCorB, preenchimento, ancora, txt);

            clone = encapsularForma (TEXT, novoT);

            break;
        }
        case TEXT_STYLE: 
            return NULL;
    }

    if (clone != NULL && chao != NULL){
        pushPilha (getPFormasChaoFree (chao), clone);
    }

    return clone;
}

FormaSt *clonarEmComCoresTrocadas (FormaSt *src, double x, double y, CHAO chao){
    if (src == NULL){
        return NULL;
    }

    FormaSt *clone = NULL;

    switch (src->tipoF){
        case CIRCLE: {
            CIRCULO c = (CIRCULO) src->data;
            int id = getId_C (c);
            double r = getR_C (c);
            char *borda = getCorB_C (c);
            char *preenchimento = getCorP_C (c);

            CIRCULO novoC = criaCirculo (id, x, y, r, preenchimento, borda);

            clone = encapsularForma (CIRCLE, novoC);

            break;
        }
        case RECTANGLE: {
            RETANGULO r = (RETANGULO) src->data;
            int id = getId_R (r);
            double w = getW_R (r);
            double h = getH_R (r);
            char *borda = getCorB_R (r);
            char *preenchimento = getCorP_R (r);
            
            RETANGULO novoR = criaRetangulo (id, x, y, w, h, preenchimento, borda);

            clone = encapsularForma (RECTANGLE, novoR);

            break;
        }
        case LINE: {
            LINHA l = (LINHA) src->data;
            int id = getId_L (l);
            double dx = getX2_L (l) - getX1_L (l);
            double dy = getY2_L (l) - getY1_L (l);
            char *cor = getCor_L (l);
            char *invertida = inverterCor (cor);
                if (invertida == NULL)
                    return NULL;
            
            LINHA novaL = criaLinha (id, x, y, (x + dx), (y + dy), invertida);

            free (invertida);

            clone = encapsularForma (LINE, novaL);

            break;
        }
        case TEXT: {
            TEXTO t = (TEXTO) src->data;
            int id = getId_T (t);
            char *borda = getCorb_T (t);
            char *preenchimento = getCorp_T (t);
            char ancora = getA_T (t);
            char *txt = getTxto_T (t);

            TEXTO novoT = criaTexto (id, x, y, preenchimento, borda, ancora, txt);

            clone = encapsularForma (TEXT, novoT);

            break;
        }
        case TEXT_STYLE: 
            return NULL;
    }

    if (clone != NULL && chao != NULL){
        pushPilha (getPFormasChaoFree (chao), clone);
    }

    return clone;
}
