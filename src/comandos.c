#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"
#include "auxiliares.h"
#include "leitorGeo.h"
#include "pilha.h"
#include "fila.h"

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



typedef enum {
    ARRAYDISPARADORF, ARRAYCARREGADORF, POSICAOFORMAF, PILHAF
} TIPOF;

typedef struct{
    void *p;
    TIPOF tp;
} ItemFree;

typedef struct{
    FormaSt *forma;
    double x, y;
    int iA; //bool
    double disparadorX;
    double disparadorY;
} PosicaoFormaASt;


//FUNCOES SUBSTITUTAS

void pdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree){
    char *iden = strtok (NULL, " ");
    char *posX = strtok (NULL, " ");
    char *posY = strtok (NULL, " ");

    *contDisparos +=1;

    *disparador = realloc (*disparador, *contDisparos * sizeof (disparadorSt));
        if (*disparador == NULL){
            printf ("Erro ao alocar memoria para disparadores");
            exit (1);
        }

    int disparadorMarcado = 0;
    int contTamPilha = tamanhoPilha (pilhaFree);

    for (int i = 0 ; i < contTamPilha ; i++){
        ItemFree *itemExiste = (ItemFree *) acharElemIdPilha (pilhaFree, i);

        if (itemExiste != NULL && itemExiste->tp == ARRAYDISPARADORF){
            itemExiste->p = *disparador;
            disparadorMarcado = 1;
            break;
        }
    }

    if (!disparadorMarcado){
        ItemFree *itemDisp = malloc (sizeof (ItemFree));
            if (itemDisp != NULL){
                itemDisp->p = *disparador;
                itemDisp->tp = ARRAYDISPARADORF;
                pushPilha (pilhaFree, itemDisp);
            }
    }

    (*disparador)[*contDisparos - 1] = (disparadorSt) {
        .id = atoi (iden),
        .x = atof (posX),
        .y = atof (posY),
        .emDisparo = NULL,
        .cargaDireita = NULL,
        .cargaEsquerda = NULL,
        .cargaDirId = -1,
        .cargaEsqId = -1
    };
}

void lcExecutar (carregadorSt **carregador, int *contCarregador, CHAO chao, PILHA pilhaFree, FILE *txtFile){
    char *iden = strtok (NULL, " ");
    char *primXFormas = strtok (NULL, " ");

    int carregadorId = atoi (iden);
    int contFormasN = atoi (primXFormas);

    fprintf (txtFile, "[lc]\n");
    fprintf (txtFile, "\tCarregador ID: %d\n", carregadorId);
    fprintf (txtFile, "\tNova quantidade de formas: %d\n", contFormasN);

    int carregadorJaExiste = -1;

    for (int i = 0 ; i < *contCarregador ; i++){
        if ((*carregador)[i].id == carregadorId){
            carregadorJaExiste = i;
            break;
        }
    }

        if (carregadorJaExiste == -1){
            *contCarregador += 1;
            *carregador = realloc (*carregador, *contCarregador * sizeof (carregadorSt));
                if (*carregador == NULL){
                    printf ("Erro ao alocar memoria para carregadores.\n");
                    exit (1);
                }
    
            int carregadorMarcado = 0;
            int contTamPilha = tamanhoPilha (pilhaFree);
            for (int i = 0 ; i < contTamPilha ; i++){
                ItemFree *itemExiste = (ItemFree *) acharElemIdPilha (pilhaFree, i);
                    if (itemExiste != NULL  && itemExiste->tp == ARRAYCARREGADORF){
                        itemExiste->p = *carregador;
                        carregadorMarcado = 1;
                        break;
                    }
            }

            if (!carregadorMarcado){
                ItemFree *itemCarr = malloc (sizeof (ItemFree));
                if (itemCarr != NULL){
                    itemCarr->p = *carregador;
                    itemCarr->tp = ARRAYCARREGADORF;
                    pushPilha (pilhaFree, itemCarr);
                }
            }
            (*carregador)[*contCarregador - 1] = (carregadorSt){
                .id = carregadorId,
                .formas = NULL
            };
            carregadorJaExiste = *contCarregador - 1;
        }

    if ((*carregador)[carregadorJaExiste].formas == NULL){
        (*carregador)[carregadorJaExiste].formas = malloc (sizeof (PILHA));

        if ((*carregador)[carregadorJaExiste].formas == NULL){
            printf ("Erro ao alocar memoria para pilha do carregador");
            exit (1);
        }

        ItemFree *itemPilha = malloc (sizeof (itemPilha));
            if (itemPilha != NULL){
                itemPilha->p = (*carregador)[carregadorJaExiste].formas;
                itemPilha->tp = PILHAF;
                pushPilha (pilhaFree, itemPilha);
            }
        *(*carregador)[carregadorJaExiste].formas = criaPilha ();
            if (*(*carregador)[carregadorJaExiste].formas == NULL){
                printf ("Erro ao alocar memoria.\n");
                exit (1);
            }
    }

    for (int i = 0 ; i < contFormasN ; i++){
        FormaSt *forma = popFila (getFChao (chao));
        if (forma != NULL){
            if (!pushPilha (*(*carregador)[carregadorJaExiste].formas, forma)){
                printf ("Erro ao colocar forma na pilha do carregador");
                exit (1);
            }
        }
    }
}

void atchExecutar (carregadorSt **carregador, int *contCarregador, disparadorSt **disparador, int *contDisparos, PILHA pilhaFree){
    char *disparadorId = strtok (NULL, " ");
    char *carregadorDirId = strtok (NULL, " ");
    char *carregadorEsqId = strtok (NULL, " ");

    int disparadorIdInt = atoi (disparadorId);
    int carregadorDirIdInt = atoi (carregadorDirId);
    int carregadorEsqIdInt = atoi (carregadorEsqId);

    int disparadorIndex = getDisparadorIndexPorId (disparador, *contDisparos, disparadorIdInt);
        if (disparadorIndex != -1){
            carregadorSt *carregadorDireitoPtr = NULL;
            carregadorSt *carregadorEsquerdoPtr = NULL;

            for (int j = 0 ; j < *contCarregador ; j++){
                if ((*carregador)[j].id == carregadorEsqIdInt){
                    carregadorEsquerdoPtr = &(*carregador)[j];
                }
                if ((*carregador)[j].id == carregadorDireitoPtr){
                    carregadorDireitoPtr = &(*carregador)[j];
                }
            }

            if (carregadorEsquerdoPtr == NULL){
                *contCarregador += 1;
                *carregador = realloc (*carregador, *contCarregador * sizeof (carregadorSt));
                if (*carregador == NULL){
                    printf ("Erro ao alocar memoria para carregadores.\n");
                    exit (1);
                }

                int carregadorMarcado = 0;
                int contTamPilha = tamanhoPilha (pilhaFree);
                for (int i = 0 ; i < contTamPilha ; i++){
                    ItemFree *itemExiste = (ItemFree *) acharElemIdPilha (pilhaFree, i);
                    if (itemExiste != NULL && itemExiste->tp == ARRAYCARREGADORF){
                        itemExiste->p = *carregador;
                        carregadorMarcado = 1;
                        break;
                    }
                }

                if (!carregadorMarcado){
                    ItemFree *itemCarr = malloc (sizeof (ItemFree));
                    if (itemCarr != NULL){
                        itemCarr->p = *carregador;
                        itemCarr->tp = ARRAYCARREGADORF;
                        pushPilha (pilhaFree, itemCarr);
                    }
                }

                (*carregador)[*contCarregador - 1] = (carregadorSt){
                    .id = carregadorEsqIdInt,
                    .formas = NULL
                };

                (*carregador)[*contCarregador - 1].formas = malloc (sizeof (PILHA));
                    if ((*carregador)[*contCarregador - 1].formas == NULL){
                        printf ("Erro ao alocar memoria.\n");
                        exit (1);
                    }
                
                ItemFree *itemPilha = malloc (sizeof (ItemFree));

                if (itemPilha !=  NULL){
                    itemPilha->p = (*carregador)[*contCarregador - 1].formas;
                    itemPilha->tp = PILHAF;
                    pushPilha (pilhaFree, itemPilha);
                }

                *(*carregador)[*contCarregador - 1].formas = criaPilha ();
                    if (*(*carregador)[*contCarregador - 1].formas == NULL){
                        printf ("Erro ao criar pilha para o carregador.\n");
                        exit (1);
                    }
                carregadorEsquerdoPtr = &(*carregador)[*contCarregador - 1];
            }

            if (carregadorDireitoPtr == NULL){
                *contCarregador += 1;
                *carregador = realloc (*carregador, *contCarregador * sizeof (carregadorSt));
                    if (*carregador == NULL){
                        printf ("Erro ao alocar memoria para carregador.\n");
                        exit (1);
                    }
                
                int carregadorMarcado = 0;
                int contTamPilha = tamanhoPilha (pilhaFree);

                    for (int i = 0 ; i < contTamPilha ; i++){
                        ItemFree *itemExiste = (ItemFree *) acharElemIdPilha (pilhaFree, i);
                        if (itemExiste != NULL && itemExiste->tp == ARRAYCARREGADORF){
                            itemExiste->p = *carregador;
                            carregadorMarcado = 1;
                            break;
                        }
                    }
                
                if (!carregadorMarcado){
                    ItemFree *itemCarr = malloc (sizeof (ItemFree));
                    if (itemCarr != NULL){
                        itemCarr->p = *carregador;
                        itemCarr->tp = ARRAYCARREGADORF;
                        pushPilha (pilhaFree, itemCarr);
                    }
                }

                (*carregador)[*contCarregador - 1] = (carregadorSt){
                    .id = carregadorDirIdInt,
                    .formas = NULL
                };

                (*carregador)[*contCarregador - 1].formas = malloc (sizeof (PILHA));
                    if ((*carregador)[*contCarregador - 1].formas == NULL){
                        printf ("Erro ao alocar memoria para pilha do carregador.\n");
                        exit (1);
                    }
                
                ItemFree *itemPilha = malloc (sizeof (ItemFree));
                if (itemPilha != NULL){
                    itemPilha->p = (*carregador)[*contCarregador - 1].formas;
                    itemPilha->tp = PILHAF;
                    pushPilha (pilhaFree, itemPilha);
                }

                *(*carregador)[*contCarregador - 1].formas = criaPilha ();
                    if (*(*carregador)[*contCarregador - 1].formas == NULL){
                        printf ("Erro ao criar pilha para o carregador.\n");
                        exit (1);
                    }
                carregadorDireitoPtr = &(*carregador)[*contCarregador - 1];
            }

            (*disparador)[disparadorIndex].cargaEsquerda = carregadorEsquerdoPtr;
            (*disparador)[disparadorIndex].cargaDireita = carregadorDireitoPtr;
            (*disparador)[disparadorIndex].cargaEsqId = carregadorEsqIdInt;
            (*disparador)[disparadorIndex].cargaDirId = carregadorDirIdInt;
        } else {
            printf ("Erro: disparador com id &d nao encontrado.\n", disparadorIdInt);
        }
}

void shftOperacao (disparadorSt **disparador, int contDisparos, int disparadorId, char *direcao, int vezes, carregadorSt *carregador, int contCarregador){
    int disparadorIndex = getDisparadorIndexPorId (disparador, contDisparos, disparadorId);
        if (disparadorIndex == -1){
            printf ("Erro disparador com ID %d nao encontrado", disparadorId);
            return;
        }
    
    disparadorSt *disp = &(*disparador)[disparadorIndex];
    
    carregadorSt *rEsquerda = NULL;
    carregadorSt *rDireita = NULL;
        if (disp->cargaEsqId != -1){
            for (int i = 0 ; i < contCarregador ; i++){
                if (carregador[i].id == disp->cargaEsqId){
                    rEsquerda = &carregador[i];
                    break;
                }
            }
        }
    
        if (disp->cargaDirId != -1){
            for (int i = 0 ; i < contCarregador ; i++){
                if (carregador[i].id == disp->cargaDirId){
                    rDireita = &carregador[i];
                    break;
                }
            }
        }
    
    disp->cargaDireita = rDireita;
    disp->cargaEsquerda = rEsquerda;

    for (int i = 0 ; i < vezes ; i++){
        if (strcmp (direcao, "e") == 0){
            if (disp->cargaEsquerda == NULL || pilhaVazia (*(disp->cargaEsquerda->formas))){
                continue;
            }

            if (disp->emDisparo != NULL && disp->cargaDireita != NULL){
                pushPilha (*(disp->cargaDireita->formas), disp->emDisparo);
            }

            disp->emDisparo = popPilha (*(disp->cargaEsquerda->formas));
        }

        if (strcmp (direcao, "d") == 0){
            if (disp->cargaDireita == NULL || pilhaVazia (*(disp->cargaDireita->formas))){
                continue;
            }

            if (disp->emDisparo != NULL && disp->cargaEsquerda != NULL){
                pushPilha (*(disp->cargaEsquerda->formas), disp->emDisparo);
            }

            disp->emDisparo = popPilha (*(disp->cargaDireita->formas));
        }
    }
}

void shftExecutar (disparadorSt **disparador, int *contDisparos, carregadorSt *carregador, int *contCarregador, FILE *txtFile){
    char *disparadorId = strtok (NULL, " ");
    char *botaoDirEsq = strtok (NULL, " ");
    char *vezesP = strtok (NULL, " ");
    fprintf (txtFile, "[shft]");

    int disparadorIdInt = atoi (disparadorId);
    int vezesPInt = atoi (vezesP);

    fprintf (txtFile, "\tDisparador ID: %d", disparadorIdInt);
    fprintf (txtFile, "\tBotao: %s", botaoDirEsq);
    fprintf (txtFile, "\tQuantidade de vezes pressionado: %d", vezesPInt);
    fprintf (txtFile, "\n");

    shftOperacao (disparador, *contDisparos, disparadorIdInt, botaoDirEsq, vezesPInt, carregador, *contCarregador);
}

void dspOperacao (disparadorSt **disparador, int contDisparos, int disparadorId, double dx, double dy, char *anota, PILHA arena, PILHA pilhaFree){
    int disparadorIndex = getDisparadorIndexPorId (disparador, contDisparos, disparadorId);
        if (disparadorIndex == -1){
            printf ("Erro: disparador com ID %d nao encontrado.\n", disparadorId);
            return;
        }
    
    disparadorSt *disp = &(*disparador)[disparadorIndex];

    if (disp->emDisparo == NULL){
        return;
    }

    double formaXArena = disp->x + dx;
    double formaYArena = disp->y + dy;

    FormaSt *forma = (FormaSt *)disp->emDisparo;
    formaTipo formaTp = forma->tipoF;

    PosicaoFormaASt *posicaoFormaArena = malloc (sizeof (PosicaoFormaASt));
        if (posicaoFormaArena == NULL){
            printf ("Erro ao alocar memoria para a posicao da forma na arena.\n");
            exit (1);
        }
    
    posicaoFormaArena->forma = forma;
    posicaoFormaArena->x = formaXArena;
    posicaoFormaArena->y = formaYArena;
    posicaoFormaArena->iA = strcmp (anota, "v") == 0;
    posicaoFormaArena->disparadorX = disp->x;
    posicaoFormaArena->disparadorY = disp->y;

    disp->emDisparo = NULL;

    pushPilha (arena, (void *)posicaoFormaArena);
    ItemFree *formaItem = malloc (sizeof (ItemFree));
        if (formaItem != NULL){
            formaItem->p = posicaoFormaArena;
            formaItem->tp = POSICAOFORMAF;
            pushPilha (pilhaFree, formaItem);
        }
}
 
void dspExecutar (disparadorSt **disparador, int *contDisparos, PILHA arena, PILHA pilhaFree, FILE *txtFile){
    char *disparadorId = strtok (NULL, " ");
    char *dx = strtok (NULL, " ");
    char *dy = strtok (NULL, " ");
    char *anotaDimensoes = strtok (NULL, " ");

    int disparadorIdInt = atoi (disparadorId);
    double dxDouble = atof (dx);
    double dyDouble = atof (dy);

    fprintf (txtFile, "[dsp]\n");
    fprintf (txtFile, "\tDisparador ID: %d", disparadorIdInt);
    fprintf (txtFile, "\tDX: %f\n", dxDouble);
    fprintf (txtFile, "\tDY: %f\n", dyDouble);
    fprintf (txtFile, "\tAnotação das dimensões: %s\n", anotaDimensoes);

    dspOperacao (disparador, *contDisparos, disparadorIdInt, dxDouble, dyDouble, anotaDimensoes, arena, pilhaFree);
}

void rjdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, PILHA arena, carregadorSt *carregador, int *contCarregador, FILE *txtFile){
    char *disparadorId = strtok (NULL, " ");
    char *botaoDirEsq = strtok (NULL, " ");
    char *dx = strtok (NULL, " ");
    char *dy = strtok (NULL, " ");
    char *incX = strtok (NULL, " ");
    char *incY = strtok (NULL, " ");

    int disparadorIdInt = atoi (disparadorId);
    double dxDouble = atof (dx);
    double dyDouble = atof (dy);
    double incXDouble = atof (incX);
    double incYDouble = atof (incY);

    int disparadorIndex = getDisparadorIndexPorId (disparador, *contDisparos, disparadorIdInt);
        if (disparadorIndex == -1){
            printf ("Erro: disparador de ID %d nao encontrado.\n", disparadorIdInt);
            return;
        }

    disparadorSt *disp = &(*disparador)[disparadorIndex];
    carregadorSt *carr = NULL;

    if (strcmp (botaoDirEsq, "e") == 0){
        int alvoId = (*disparador)[disparadorIndex].cargaEsqId;
        if (alvoId != -1){
            for (int i = 0 ; i < *contCarregador ; i++){
                if (carregador[i].id == alvoId){
                    (*disparador)[disparadorIndex].cargaEsquerda = &carregador[i];
                    break;
                }
            }
        }
    } else if (strcmp (botaoDirEsq, "d") == 0){
        int alvoId = (*disparador)[disparadorIndex].cargaDirId;
        if (alvoId != -1){
            for (int i = 0 ; i < *contCarregador ; i++){
                if (carregador[i].id == alvoId){
                    (*disparador)[disparadorIndex].cargaDireita = &carregador[i];
                    break;
                }
            }
        }
    }

    if (strcmp (botaoDirEsq, "e") == 0){
        carr = disp->cargaEsquerda;
    } else if (strcmp (botaoDirEsq, "d") == 0){
        carr = disp->cargaDireita;
    } else {
        printf ("Erro: botao invalido (deveria ser 'e' ou 'd').\n");
        return;
    }

    if (carr == NULL || carr->formas == NULL){
        printf ("Erro: Carregador nao encontrado ou pilha de formas = NULL.\n");
        return;
    }

    int vezes = 1;

    fprintf (txtFile, "[rjd]\n");
    fprintf (txtFile, "\tDisparador ID: %d\n", disparadorIdInt);
    fprintf (txtFile, "\tBotão: %s\n", botaoDirEsq);
    fprintf (txtFile, "\tDX: %f\n", dxDouble);
    fprintf (txtFile, "\tDY: %f\n", dyDouble);
    fprintf (txtFile, "\tIncrementa X: %f\n", incXDouble);
    fprintf (txtFile, "\tIncrementa Y: %f\n", incYDouble);
    fprintf (txtFile, "\n");

    while (!pilhaVazia (*(carr->formas))){
        shftOperacao (disparador, *contDisparos, disparadorIdInt, botaoDirEsq, 1, carregador, *contCarregador);

        dspOperacao (disparador, *contDisparos, disparadorIdInt, (vezes * incXDouble + dxDouble), (vezes * incYDouble + dyDouble), "i", arena, pilhaFree);

        vezes++;
    }
}

void calcExecutar (PILHA arena, CHAO chao, FILE *txtFile){
    PILHA temp = criaPilha ();

    while (!pilhaVazia (arena)){
        pushPilha (temp, popPilha (arena));
    }

    double areaTotalEsmagada = 0.0;

    while (!pilhaVazia (temp)){
        PosicaoFormaASt *I = (PosicaoFormaASt *) popPilha (temp);
        if (pilhaVazia (temp)){
            FormaSt *Ipos = clonarComPosicao (I->forma, I->x, I->y, chao);
            if (Ipos != NULL){
                pushFila (getFChao (chao), Ipos);
            }
            continue;
        }
        PosicaoFormaASt *J = (PosicaoFormaASt *) popPilha (temp);

        int sobreposicao = sobreposicaoFormas (I, J);

        if (sobreposicao){
            double areaI = getAreaForma (I->forma->tipoF, I->forma->data);
            double areaJ = getAreaForma (J->forma->tipoF, J->forma->data);

            areaTotalEsmagada += (areaI < areaJ) ? areaI : areaJ;

            if (areaI < areaJ){
                //I destroi, J volta pro chao
                FormaSt *Jpos = clonarComPosicao (J->forma, J->x, J->y, chao);
                if (Jpos != NULL){
                    pushFila (getFChao (chao), Jpos);
                }
            } else if (areaI >= areaJ){
                //I muda cor de borda de J para preencher cor de I
                char *preencheCorI = NULL;
                switch (I->forma->tipoF){
                    case CIRCLE:
                        preencheCorI = getCorP_C ((CIRCULO) I->forma->data);
                        break;
                    case RECTANGLE:
                        preencheCorI = getCorP_R ((RETANGULO) I->forma->data);
                        break;
                    case TEXT:
                        preencheCorI = getCorp_T ((TEXTO) I->forma->data);
                        break;
                    case LINE:
                    case TEXT_STYLE:
                        preencheCorI = NULL;
                        break;
                }

                FormaSt *JpPos = NULL;

                if (preencheCorI != NULL){
                    JpPos = clonarEmComCorB (J->forma, preencheCorI, J->x, J->y, chao);            
                } else {
                    JpPos = clonarComPosicao (J->forma, J->x, J->y, chao);
                }


                FormaSt *Ipos = clonarComPosicao (I->forma, I->x, I->y, chao);
                if (Ipos != NULL){
                    pushFila (getFChao (chao), Ipos);
                }
                if (JpPos != NULL){
                    pushFila (getFChao (chao), JpPos);
                }


                //clona I trocando borda com preenchimento, na posicao de I
                FormaSt *IcPos = clonarEmComCoresTrocadas (I->forma, I->x, I->y, chao);

                if (IcPos != NULL){
                    pushFila (getFChao (chao), IcPos);
                }
            } else {
                FormaSt *Ipos = clonarComPosicao (I->forma, I->x, I->y, chao);
                FormaSt *Jpos = clonarComPosicao (J->forma, J->x, J->y, chao);

                if (Ipos != NULL){
                    pushFila (getFChao (chao), Ipos);
                }
                if (Jpos != NULL){
                    pushFila (getFChao (chao), Jpos);
                }
            }
        } else {
            //Sem sobreposicao
            FormaSt *Ipos = clonarComPosicao (I->forma, I->x, I->y, chao);
            FormaSt *Jpos = clonarComPosicao (J->forma, J->x, J->y, chao);

                if (Ipos != NULL){
                    pushFila (getFChao (chao), Ipos);
                }
                if (Jpos != NULL){
                    pushFila (getFChao (chao), Jpos);
                }
        }
    }

    //Saida com o resultado calculado
    fprintf (txtFile, "[calc]\n");
    fprintf (txtFile, "\tResultado: %.2lf\n", areaTotalEsmagada);
    fprintf (txtFile, "\n");

    killPilha (temp);
}









