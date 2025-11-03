#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorDeArquivos.h"
#include "fila.h"
#include "pilha.h"


struct DadosArquivo {
    char *arqPath;
    char *arqNome;
    FILA filaLinhas;
    PILHA linhasLiberar;
};

struct filaEPilhaLinhas{
    FILA filaLinhas;
    PILHA linhasLiberar;    
};


static struct filaEPilhaLinhas *leArqFilaPilha(char *arqPath);

//Funções privadasc definidas no meio do arquivo
char *duplicaString (char *st);
static char *leLinha (FILE *arquivo, char *buffer, size_t tam);


DadosArquivo criarDadosArq (char * arqPath){
    struct DadosArquivo *arquivo = malloc (sizeof(struct DadosArquivo));
        if (arquivo == NULL){
            printf ("Erro ao alocar memoria para dados do arquivo.\n");
            return NULL;
        }

    arquivo->arqPath = arqPath;
    arquivo->arqNome = strrchr(arqPath, '/') ? strrchr(arqPath, '/') + 1 : arqPath;

    struct filaEPilhaLinhas *filaPilha = leArqFilaPilha (arqPath);

        if (filaPilha == NULL || filaPilha->linhasLiberar == NULL || filaPilha->filaLinhas == NULL){
            printf ("Erro ao ler as linhas do arquivo.88\n");

            if (filaPilha != NULL)
                free(filaPilha);

            return NULL;
        }
    
        arquivo->filaLinhas = filaPilha->filaLinhas;
        arquivo->linhasLiberar = filaPilha->linhasLiberar;
        free (filaPilha);

    return ((DadosArquivo) arquivo);
}



static struct filaEPilhaLinhas *leArqFilaPilha (char *arqPath){
    struct filaEPilhaLinhas *filaPilha = malloc (sizeof (struct filaEPilhaLinhas));

    if (filaPilha == NULL){
        printf ("Erro ao alocar memoria fila e pilha de linhas.\n");
        return NULL;
    }

    FILA fila = criaFila ();
    PILHA linhasLiberar = criaPilha ();
    FILE *arquivo = fopen (arqPath, "r");

        if (arquivo == NULL){
            if (fila != NULL)
                killFila (fila);
            
            if (linhasLiberar != NULL)
                killPilha (linhasLiberar);

            free (filaPilha);
            return NULL;
        }

    char buffer [1024];
        while (leLinha (arquivo, buffer, sizeof (buffer)) != NULL){
            char *linha = duplicaString (buffer);
            pushFila (fila, linha);
            pushPilha (linhasLiberar, linha);
        }
    
    fclose (arquivo);

    filaPilha->filaLinhas = fila;
    filaPilha->linhasLiberar = linhasLiberar;

    return filaPilha;
}



/**
**************************
* Funções Privadas
**************************
*/

//Lê uma linha do arquivo usando fgets
static char *leLinha (FILE *arquivo, char *buffer, size_t tam){
    if ((fgets(buffer, tam, arquivo) != NULL)){
        size_t t = strlen(buffer);

        if (t > 0 && buffer[t - 1] == '\n')
            buffer[t - 1] = '\0';
        
        return (buffer);
    }
    return NULL;
}

/**
 * Duplica uma string usando malloc
 * @param st string para duplicar
 * @return Nova string ou NULL em caso de erro
 */
char *duplicaString (char *st){
    if (st == NULL)
        return NULL;

    size_t t = strlen(st) + 1;

    char *duplica = malloc (t);
        if (duplica != NULL)
            strcpy (duplica, st);

    return (duplica);
}

/**
**************************
* Fim das Funções Privadas
**************************
*/



char* getPathArq (DadosArquivo arqData){
    if (arqData == NULL)
        return NULL;

    struct DadosArquivo *arquivo = (struct DadosArquivo *) arqData;

    return (arquivo->arqPath);
}

char* getNomeArq (DadosArquivo arqData){
    if (arqData == NULL)
        return NULL;
    
    struct DadosArquivo *arquivo = (struct DadosArquivo *) arqData;

    return (arquivo->arqNome);    
}

FILA getFilaLinhasArq (DadosArquivo arqData){
    if (arqData == NULL)
        return NULL;
    
    struct DadosArquivo *arquivo = (struct DadosArquivo *) arqData;

    return (arquivo->filaLinhas);  
}


void destruirDadosArq (DadosArquivo arqData){
    if (arqData != NULL){
        struct DadosArquivo *arquivo = ((struct DadosArquivo *) arqData);

        while (!pilhaVazia(arquivo->linhasLiberar)){
            void *linha = popPilha(arquivo->linhasLiberar);
            linha != NULL ? free (linha) : NULL;
        }

        killPilha (arquivo->linhasLiberar);

        killFila (arquivo->filaLinhas);

        free (arqData);
    }
}





