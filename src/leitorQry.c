#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "leitorQry.h"
#include "fila.h"
#include "pilha.h"
#include "leitorGeo.h"
#include "formas.h"

#include "comandos.h"
#include "auxiliares.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estiloTexto.h"


typedef struct{
    PILHA arena;
    PILHA pilhaFree;
} QrySt;

void resultadoQry (DadosArquivo arqDataQry, DadosArquivo arqDataGeo, CHAO chao, PILHA arena, char *saidaPath);

void killQry (QRY qry){
    QrySt *qry1 = (QrySt *)qry;

    while (!pilhaVazia (qry1->pilhaFree)){
        ItemFree *item = (ItemFree *) popPilha (qry1->pilhaFree);

            if (item != NULL && item->p != NULL){
                if (item->tp == ARRAYDISPARADORF || item->tp == ARRAYCARREGADORF || item->tp == POSICAOFORMAF){
                    free(item->p);
                } else if (item->tp == PILHAF){
                    PILHA *pilhaF = (PILHA *) item->p;
                        if (pilhaF != NULL && *pilhaF != NULL){
                            killPilha (*pilhaF);
                        }
                    free (item->p);
                }

                free (item);
            }
    }
    killPilha (qry1->arena);
    killPilha (qry1->pilhaFree);
    free (qry1);
}


QRY exeQryCmd (DadosArquivo arqDataQry, DadosArquivo arqDataGeo, CHAO chao, char *saidaPath){
    QrySt *qry = malloc (sizeof (QrySt));
        if (qry == NULL){
            printf ("Erro ao alocar memoria para qry.\n");
            exit (1);
        }
    
    Estatisticas *stats = malloc (sizeof (Estatisticas));
        *stats = (Estatisticas) {0, 0, 0, 0, 0.0};

    qry->arena = criaPilha ();
    qry->pilhaFree = criaPilha ();

    disparadorSt *disparador = NULL;
    int contDisparos = 0;
    carregadorSt *carregador = NULL;
    int contCarregador = 0;


    size_t tamGeo = strlen (getNomeArq (arqDataGeo));
    size_t tamQry = strlen (getNomeArq (arqDataQry));
    char *geoBase = malloc (tamGeo + 1);
    char *qryBase = malloc (tamQry + 1);
        
        if (geoBase == NULL || qryBase == NULL){
            printf ("Erro ao alocar memoria para nome do arquivo.\n");
            free (geoBase);
            free (qryBase);
            return NULL;
        }
    strcpy (geoBase, getNomeArq (arqDataGeo));
    strcpy (qryBase, getNomeArq (arqDataQry));
        strtok (geoBase, ".");
        strtok (qryBase, ".");
    size_t tamPath = strlen (saidaPath);


    size_t tamNomeP = strlen (geoBase) + 1 + strlen (qryBase);
    size_t tamTotal = tamPath + 1 + tamNomeP + 4 + 1;
    char *saidaTxtPath = malloc (tamTotal);
        if (saidaTxtPath == NULL){
            printf ("Erro na alocacao de memoria");
            free (geoBase);
            free (qryBase);
            return NULL;
        }
    int res = snprintf (saidaTxtPath, tamTotal, "%s/%s-%s.txt", saidaPath, geoBase, qryBase);

        if (res < 0 || (size_t) res >= tamTotal){
            printf ("Erro na construcao do path.\n");
            free (saidaTxtPath);
            free (qryBase);
            free (geoBase);
            return NULL;
        }
    
    FILE *txtFile = fopen (saidaTxtPath, "w");
        free (geoBase);
        free (qryBase);
        free (saidaTxtPath);

    while (!filaVazia (getFilaLinhasArq (arqDataQry))){
        char *linha = (char *) popFila (getFilaLinhasArq (arqDataQry));
        char *cmd = strtok (linha, " \t\r\n");
            if (cmd == NULL || *cmd == '\0'){
                continue;
            }

        if (strcmp (cmd, "pd") == 0){
            pdExecutar (&disparador, &contDisparos, qry->pilhaFree, stats);
        } else if (strcmp (cmd, "lc") == 0){
            lcExecutar (&carregador, &contCarregador, chao, qry->pilhaFree, txtFile, stats);
        } else if (strcmp (cmd, "atch") == 0){
            atchExecutar (&carregador, &contCarregador, &disparador, &contDisparos, qry->pilhaFree, stats);
        } else if (strcmp (cmd, "shft") == 0){
            shftExecutar (&disparador, &contDisparos, carregador, &contCarregador, txtFile, stats);
        } else if (strcmp (cmd, "dsp") == 0){
            dspExecutar (&disparador, &contDisparos, qry->arena, qry->pilhaFree, txtFile, stats);
        } else if (strcmp (cmd, "rjd") == 0){
            rjdExecutar (&disparador, &contDisparos, qry->pilhaFree, qry->arena, carregador, &contCarregador, txtFile, stats);
        } else if (strcmp (cmd, "calc") == 0){
            calcExecutar (qry->arena, chao, txtFile, stats);
        } else {
            printf ("Comando nao reconhecido.\n");
        }
    }

    resultadoQry (arqDataQry, arqDataGeo, chao, qry->arena, saidaPath);

    
    fprintf (txtFile, "\n[Resumo Final]\n");
    fprintf (txtFile, "Pontuação final: %.2lf\n", stats->areaEsmagadaTotal);
    fprintf (txtFile, "Total de instruções executadas: %d\n", stats->instrucoesExecutadas);
    fprintf (txtFile, "Total de disparos: %d\n", stats->disparos);
    fprintf (txtFile, "Total de formas esmagadas: %d\n", stats->formasEsmagadas);
    fprintf (txtFile, "Total de formas clonadas: %d\n", stats->formasClonadas);
    fprintf (txtFile, "\n");

    fclose (txtFile);
    free (stats);
    return (QRY) qry;
}

void resultadoQry (DadosArquivo arqDataQry, DadosArquivo arqDataGeo, CHAO chao, PILHA arena, char *saidaPath){
    char *nomeSrcGeo = getNomeArq (arqDataGeo);
    char *nomeSrcQry = getNomeArq (arqDataQry);

    size_t tamGeo = strlen (nomeSrcGeo);
    size_t tamQry = strlen (nomeSrcQry);

    char *baseGeo = malloc (tamGeo + 1);
    char *baseQry = malloc (tamQry + 1);
        if (baseGeo == NULL || baseQry == NULL){
            printf ("Erro: erro ao alocar memoria para nome do arquivo.\n");
            free (baseGeo);
            free (baseQry);
            return;
        }
    strcpy (baseGeo, nomeSrcGeo);
    strcpy (baseQry, nomeSrcQry);
    strtok (baseGeo, ".");
    strtok (baseQry, ".");


    size_t tamPath = strlen (saidaPath);
    size_t tamNomeProcessado = strlen (baseGeo) + 1 + strlen (baseQry);
    size_t tamTotal = tamPath + 1 + tamNomeProcessado + 4 + 1;

    char *saidaPathArq = malloc (tamTotal);
        if (saidaPathArq == NULL){
            printf ("Erro na alocacao de memoria.\n");
            free (baseGeo);
            free (baseQry);
            return;
        }

    int resultado = snprintf (saidaPathArq, tamTotal, "%s/%s-%s.svg", saidaPath, baseGeo, baseQry);
        if (resultado < 0 || (size_t) resultado >= tamTotal){
            printf ("Erro na construcao do path.\n");
            free (saidaPathArq);
            free (baseGeo);
            free (baseQry);
            return;
        }

    FILE *arq = fopen (saidaPathArq, "w");
        if (arq == NULL){
            printf ("Erro: falha ao abrir o arquivo: %s.\n", saidaPathArq);
            free (saidaPathArq);
            free (baseGeo);
            free (baseQry);
            return;
        }
    fprintf (arq, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf (arq, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 "
        "1000\">\n");
    
    FILA filaChao = getFChao (chao);
    FILA tempF = criaFila ();

    while (!filaVazia (filaChao)){
        FormaSt *forma = (FormaSt *) popFila (filaChao);
        if (forma != NULL){
            if (forma->tipoF == CIRCLE){
                CIRCULO circulo = (CIRCULO) forma->data;
                fprintf (arq, "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s' fill-opacity='0.6' stroke-opacity='0.9'/>\n", 
                    getX_C (circulo), getY_C (circulo), getR_C (circulo), getCorP_C (circulo), getCorB_C (circulo)
                );

            } else if (forma->tipoF == RECTANGLE){
                RETANGULO retangulo = (RETANGULO) forma->data;
                fprintf (arq,  "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' "
                    "stroke='%s' fill-opacity='0.6' stroke-opacity='0.9'/>\n",
                    getX_R (retangulo), getY_R (retangulo), getW_R (retangulo), getH_R (retangulo), getCorP_R (retangulo), getCorB_R (retangulo)
                );
            
            } else if (forma->tipoF == LINE){
                LINHA linha = (LINHA) forma->data;
                fprintf (arq, "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                    getX1_L (linha), getY1_L (linha), getX2_L (linha), getY2_L (linha), getCor_L (linha)
                );
            
            } else if (forma->tipoF == TEXT){
                TEXTO texto = (TEXTO) forma->data;
                char ancora = getA_T (texto);
                char *ancoraT = "start";
                    if (ancora == 'm' || ancora == 'M'){
                        ancoraT = "middle";

                    } else if (ancora == 'f' || ancora == 'F'){
                        ancoraT = "end";

                    } else if (ancora == 'i' || ancora == 'I'){
                        ancoraT = "start";
                    }
                fprintf (arq,  "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' "
                    "text-anchor='%s'>%s</text>\n",
                    getX_T (texto), getY_T (texto), getCorp_T (texto), getCorb_T (texto), ancoraT, getTxto_T (texto)
                );

            }
        }

        pushFila (tempF, forma);
    }

    while (!filaVazia (tempF)){
        pushFila (filaChao, popFila (tempF));
    }
    killFila (tempF);

    PILHA tempP = criaPilha ();
    while (!pilhaVazia (arena)){
        PosicaoFormaASt *f = (PosicaoFormaASt *) popPilha (arena);
        if (f != NULL && f->iA){
            fprintf (arq, "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='red' "
              "stroke-dasharray='4,2' stroke-width='1'/>\n",
                f->disparadorX, f->disparadorY, f->x, f->y
            );

            fprintf (arq, "<circle cx='%.2f' cy='%.2f' r='3' fill='none' stroke='red' "
              "stroke-width='1'/>\n",
                f->x, f->y
            );

            double dx = f->x - f->disparadorX;
            double dy = f->y - f->disparadorY;
            double meioHx = f->disparadorX + dx * 0.5;
            double meioHy = f->disparadorY;
            double meioVx = f->disparadorX + dx;
            double meioVy = f->disparadorY + dy * 0.5;

            fprintf (arq,  "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='purple' "
              "stroke-dasharray='2,2' stroke-width='0.8'/>\n",
                f->disparadorX, f->disparadorY, f->x, f->disparadorY
            );

            fprintf (arq, "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='purple' "
              "stroke-dasharray='2,2' stroke-width='0.8'/>\n",
                f->x, f->disparadorY, f->x, f->y
            );

            fprintf (arq,  "<text x='%.2f' y='%.2f' fill='purple' font-size='12' "
              "text-anchor='middle'>%.2f</text>\n",
                meioHx, (meioHy - 5.0), dx
            );

            fprintf (arq, "<text x='%.2f' y='%.2f' fill='purple' font-size='12' "
              "text-anchor='middle' transform='rotate(-90 %.2f "
              "%.2f)'>%.2f</text>\n",
                (meioVx + 10.0), meioVy, (meioVx + 10.0), meioVy, dy
            );
        }

        pushPilha (tempP, f);
    }

    while (!pilhaVazia (tempP)){
        pushPilha (arena, popPilha (tempP));
    }

    killPilha (tempP);

    fprintf (arq, "</svg>\n");
    fclose (arq);
    free (saidaPathArq);
    free (baseGeo);
    free (baseQry);
}