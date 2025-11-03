#include <stdio.h>

#include "cor.h"

// Função auxiliar interna: converte um único dígito hexadecimal em seu valor, retorna -1 em caso de erro
int valorHex (char c){
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'f')
        return 10 + (c - 'a');

    if (c >= 'A' && c <= 'F')
        return 10 + (c - 'A');

    return -1;
}


// Auxiliar interno: analisa #RRGGBB em r,g,b (0-255). Retorna 0 em caso de sucesso.
int analisarCorHex (char *s, int *r, int *g, int *b){
    if (s == NULL || s[0] != '#')
        return -1;
    
    if (strlen(s) != 7)
        return -1;

    int v[6];
    for (int i = 0; i < 6; i++) {
        int hv = valorHex(s[1 + i]);
        if (hv < 0)
            return -1;

        v[i] = hv;
    }
    *r = v[0] * 16 + v[1];
    *g = v[2] * 16 + v[3];
    *b = v[4] * 16 + v[5];
    return 0;
}


// Auxiliar interno: mapeia um conjunto limitado de cores nomeadas para RGB
int corRgbNome (char *nome, int *r, int *g, int *b){
    if (nome == NULL)
        return -1;

    if (strcmp(nome, "black") == 0) {
        *r = 0;
        *g = 0;
        *b = 0;
        return 0;

    } else if (strcmp(nome, "white") == 0) {
        *r = 255;
        *g = 255;
        *b = 255;
        return 0;

    } else if (strcmp(nome, "red") == 0) {
        *r = 255;
        *g = 0;
        *b = 0;
        return 0;

    } else if (strcmp(nome, "green") == 0) {
        *r = 0;
        *g = 128;
        *b = 0;
        return 0;

    } else if (strcmp(nome, "blue") == 0) {
        *r = 0;
        *g = 0;
        *b = 255;
        return 0;

    } else if (strcmp(nome, "yellow") == 0) {
        *r = 255;
        *g = 255;
        *b = 0;
        return 0;

    } else if (strcmp(nome, "pink") == 0) {
        *r = 255;
        *g = 192;
        *b = 203;
        return 0;

    } else if (strcmp(nome, "cyan") == 0) {
        *r = 0;
        *g = 255;
        *b = 255;
        return 0;

    } else if (strcmp(nome, "orange") == 0) {
        *r = 255;
        *g = 165;
        *b = 0;
        return 0;

    } else if (strcmp(nome, "teal") == 0) {
        *r = 0;
        *g = 128;
        *b = 128;
        return 0;

    } else if (strcmp(nome, "purple") == 0) {
        *r = 128;
        *g = 0;
        *b = 128;
        return 0;

    }

    return -1;
}

char *inverterCor (char *cor) {
    if (cor == NULL)
        return NULL;

    int r = 0, g = 0, b = 0;
    int ok = analisarCorHex (cor, &r, &g, &b);

    if (ok != 0){
        if (corRgbNome (cor, &r, &g, &b) != 0){
            
            //duplica string
            if (cor == NULL)
                return NULL;

            size_t tam = strlen (cor) + 1;
            char *dup = malloc (tam);
                if (dup != NULL){
                    strcpy (dup, cor);
                }
            return dup;
        }
    }

    int ir = 255 - r;
    int ig = 255 - g;
    int ib = 255 - b;

    char *saida = (char *) malloc (8);
        if (saida == NULL)
            return NULL;

    int n = snprintf (saida, 8, "#%02X%02X%02X", ir, ig, ib);
    if (n < 0 || n >= 8){
        free (saida);
        return NULL;
    }

    return saida;
}