#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"
#include "leitorDeArquivos.h"
#include "fila.h"
#include "pilha.h"

#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estiloTexto.h"


typedef struct{
    FILA filaFormas;
    PILHA pilhaFreeMemoria;
    FILA filaSVG;
} ChaoSt;

typedef struct{
    formaTipo tipoF;
    void* data;
} FormaSt;

void exeCmd_Retangulo (ChaoSt *chao);
void exeCmd_Circulo (ChaoSt *chao);
void exeCmd_Linha (ChaoSt *chao);
void exeCmd_Texto (ChaoSt *chao);
void exeCmd_EstiloTexto (ChaoSt *chao);

void criarFilaSVG (ChaoSt *chao, char *saidaPath, DadosArquivo arqData, char *sufixoCmd);




CHAO processarGeo (DadosArquivo arqData, char *saidaPath, char *sufixoCmd){
    ChaoSt *chao = malloc (sizeof (ChaoSt));

        if (chao == NULL){
            printf ("Erro ao alocar memoria.\n");
            exit (1);
        }

    chao->filaFormas = criaFila ();
    chao->pilhaFreeMemoria = criaPilha ();
    chao->filaSVG = criaFila ();

        while (!filaVazia (getFilaLinhasArq (arqData))){
            char *linha = (char *) popFila (getFilaLinhasArq (arqData));
            char *cmd = strtok (linha, " ");

            if (strcmp (cmd, "c") == 0) {
                exeCmd_Circulo (chao);

            } else if (strcmp (cmd, "r") == 0) {
                exeCmd_Retangulo (chao);

            } else if (strcmp (cmd, "l") == 0) {
                exeCmd_Linha (chao);

            } else if (strcmp (cmd, "t") == 0) {
                exeCmd_Texto (chao);

            } else if (strcmp (cmd, "ts") == 0) {
                exeCmd_EstiloTexto (chao);

            } else {
                printf ("Comando invalido para forma. \n");

            }
        }

    criarFilaSVG (chao, saidaPath, arqData, sufixoCmd);

    return chao;
}

FILA getFChao (CHAO chao){
    ChaoSt *chao1 = ((ChaoSt *) chao);

    return (chao1->filaFormas);
}

void killGeo (CHAO chao){
    ChaoSt *chao1 = ((ChaoSt *) chao);

    killFila (chao1->filaFormas);
    killFila (chao1->filaSVG);

        while (!pilhaVazia (chao1->pilhaFreeMemoria)){
            FormaSt *forma = popPilha (chao1->pilhaFreeMemoria);

            switch (forma->tipoF) {
                case CIRCLE: kill_C (forma->data);
                    break;
                case RECTANGLE: kill_R (forma->data);
                    break;
                case LINE: kill_L (forma->data);
                    break;
                case TEXT: kill_T (forma->data);
                    break;
                case TEXT_STYLE: killEstiloTexto (forma->data);
                    break;
            }
            free (forma);
        }
    killPilha (chao1->pilhaFreeMemoria);
    free (chao);
}


void exeCmd_Retangulo (ChaoSt *chao){
    char *id = strtok (NULL, " ");
    char *x = strtok (NULL, " ");
    char *y = strtok (NULL, " ");
    char *w = strtok (NULL, " ");
    char *h = strtok (NULL, " ");
    char *corb = strtok (NULL, " ");
    char *corp = strtok (NULL, " ");

    RETANGULO r = criaRetangulo (atoi (id), atof (x), atof (y), atof (w), atof(h), corb, corp);

    FormaSt *forma = malloc (sizeof (FormaSt));
        if (forma == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit (1);
        }

    forma->tipoF = RECTANGLE;
    forma->data = r;

    pushFila (chao->filaFormas, forma);
    pushPilha (chao->pilhaFreeMemoria, forma);
    pushFila (chao->filaSVG, forma);
}

void exeCmd_Circulo (ChaoSt *chao){
    char *id = strtok (NULL, " ");
    char *x = strtok (NULL, " ");
    char *y = strtok (NULL, " ");
    char *raio = strtok (NULL, " ");
    char *corb = strtok (NULL, " ");
    char *corp = strtok (NULL, " ");

    CIRCULO c = criaCirculo (atoi (id), atof (x), atof (y), atof (raio), corb, corp);

    FormaSt *forma = malloc (sizeof (FormaSt));
        if (forma == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit (1);
        }

    forma->tipoF = CIRCLE;
    forma->data = c;

    pushFila (chao->filaFormas, forma);
    pushPilha (chao->pilhaFreeMemoria, forma);
    pushFila (chao->filaSVG, forma);
}

void exeCmd_Linha (ChaoSt *chao){
    char *id = strtok (NULL, " ");
    char *x1 = strtok (NULL, " ");
    char *y1 = strtok (NULL, " ");
    char *x2 = strtok (NULL, " ");
    char *y2 = strtok (NULL, " ");
    char *cor = strtok (NULL, " ");

    LINHA l = criaLinha (atoi (id), atof (x1), atof (y1), atof (x2), atof (y2), cor);

    FormaSt *forma = malloc (sizeof (FormaSt));
        if (forma == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit (1);
        }

    forma->tipoF = LINE;
    forma->data = l;

    pushFila (chao->filaFormas, forma);
    pushPilha (chao->pilhaFreeMemoria, forma);
    pushFila (chao->filaSVG, forma);
}
void exeCmd_Texto (ChaoSt *chao){
    char *id = strtok (NULL, " ");
    char *x = strtok (NULL, " ");
    char *y = strtok (NULL, " ");
    char *corb = strtok (NULL, " ");
    char *corp = strtok (NULL, " ");
    char *a = strtok (NULL, " ");
    char *txto = strtok (NULL, " ");

    TEXTO t = criaTexto (atoi (id), atof (x), atof (y), corb, corp, *a, txto);

    FormaSt *forma = malloc (sizeof (FormaSt));
        if (forma == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit (1);
        }

    forma->tipoF = TEXT;
    forma->data = t;

    pushFila (chao->filaFormas, forma);
    pushPilha (chao->pilhaFreeMemoria, forma);
    pushFila (chao->filaSVG, forma);
}
void exeCmd_EstiloTexto (ChaoSt *chao){
    char *fF = strtok (NULL, " ");
    char *fW = strtok (NULL, " ");
    char *fS = strtok (NULL, " ");

    ESTILO_TEXTO ts = criaEstiloTexto (fF, fW, atof (fS));

    FormaSt *forma = malloc (sizeof (FormaSt));
        if (forma == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit (1);
        }

    forma->tipoF = TEXT_STYLE;
    forma->data = ts;

    pushFila (chao->filaFormas, forma);
    pushPilha (chao->pilhaFreeMemoria, forma);
    pushFila (chao->filaSVG, forma);
}

void criarFilaSVG (ChaoSt *chao, char *saidaPath, DadosArquivo arqData, char *sufixoCmd){

    char *nomeArqOr = getNomeArq (arqData);
    size_t nomeTam = strlen (nomeArqOr);
    char *nomeArq = malloc (nomeTam + 1);

        if (nomeArq == NULL){
            printf ("Erro ao alocar memoria para nome do arquivo.\n");
            return;
        }
    
    strcpy (nomeArq, nomeArqOr);
    strtok (nomeArq, ".");

        if (sufixoCmd != NULL){
            strcat (nomeArq, "-");
            strcat (nomeArq, sufixoCmd);
        }
    
    size_t pathTam = strlen (saidaPath);
    size_t nomeExeTam = strlen (nomeArq);
    size_t tamTotal = pathTam + 1 + nomeExeTam + 4 + 1;

    char *saidaPathArq = malloc (tamTotal);
        if (saidaPathArq == NULL){
            printf ("Erro ao alocar memoria. \n");
            return;
        }




    int resul = snprintf (saidaPathArq, tamTotal, "%s/%s.svg", saidaPath, nomeArq);
        if (resul < 0 || (size_t)resul >= tamTotal){
            printf ("Erro no path.\n");
            free (saidaPathArq);
                return;
        }

    FILE *arq = fopen (saidaPathArq, "w");
        if (arq == NULL){
            printf ("Erro ao abrir o arquivo SVG de saida.\n");
            free (saidaPathArq);
                return;
        }

        //fprintf (arq,  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        
        fprintf (arq, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 1000\">\n");

        while (!filaVazia (chao->filaSVG)){
            FormaSt *forma = popFila (chao->filaSVG);
                if (forma != NULL){
                    if (forma->tipoF == CIRCLE){
                        CIRCULO c = (CIRCULO) forma->data;

                        fprintf (arq, "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s'/>\n",
                            getX_C (c), getY_C (c), getR_C (c), getCorP_C (c), getCorB_C (c));

                    } else if (forma->tipoF == RECTANGLE){
                        RETANGULO r = (RETANGULO) forma->data;

                        fprintf (arq, "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' stroke='%s'/>\n",
                            getX_R (r), getY_R (r), getW_R (r), getH_R (r), getCorB_R (r), getCorP_R (r));

                    } else if (forma->tipoF == LINE){
                        LINHA l = (LINHA) forma->data;

                        fprintf (arq, "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                            getX1_L (l), getY1_L (l), getX2_L (l), getY2_L (l), getCor_L (l));

                    } else if (forma->tipoF == TEXT){
                        TEXTO t = (TEXTO) forma->data;

                        char ancora = getA_T (t);
                        char *txtA = "start";

                            if (ancora == 'm' || ancora == 'M') {
                                txtA = "middle";
                            } else if (ancora == 'f' || ancora == 'F') {
                                txtA = "end";
                            }

                        fprintf (arq, "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                            getX_T (t), getY_T (t), getCorp_T (t), getCorb_T (t), txtA, getTxto_T (t));
                    }
                }
        }
    
        fprintf (arq, "</svg>\n");
        fclose (arq);
        free (saidaPathArq);
        free (nomeArq);
}
