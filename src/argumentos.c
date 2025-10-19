#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "argumentos.h"

char *getValorOpt (int arg, char *argVet[], char *nomeOpt){
    char fOpt [64];

    snprintf (fOpt, sizeof (fOpt), "-%s", nomeOpt);

    for (int i = 1 ; i < arg -1 ; ++i){
        if (strcmp (argVet[i], fOpt) == 0){
            if (argVet [i + 1] == NULL){
                return NULL;
            } else {
                return (argVet [i + 1]);
            }
        }
    }
    
    return NULL;
}

char *getSufixoCmd (int arg, char *argVet[]){
    char **argVetC = malloc (arg * sizeof (char *));
        if (argVetC == NULL)
            return NULL;

    for (int i = 0 ; i < arg ; i++) {
        argVetC [i] = argVet [i];
    }

    int newArg = arg;

    for (int i = 1 ; i < newArg - 1 ; i++){
        if (argVetC [i][0] == '-' && argVetC [i + 1][0] != '-'){
            for (int j = i ; j < newArg - 2 ; j++){
                argVetC [j] = argVetC [j + 2];
            }
            newArg -= 2;
            i--;
        }
    }

    char *sufixo = NULL;
        if (newArg == 2){
            sufixo = argVetC [newArg - 1];
        } else if (newArg > 2) {
            printf ("Erro: mais de um sufixo foi encontrado.\n");
            free (argVetC);
                exit (1);
        }
    
    free (argVetC);

    return (sufixo);
}
