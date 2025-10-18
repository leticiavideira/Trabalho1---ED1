#include "chao.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct stChao {
    FILA *filaChao;
}chao;

chao *criaChao() {
    chao *c = (chao*) malloc (sizeof(chao));
    if (c == NULL) {
        printf("Erro ao criar o chao!\n");
        return NULL;
    }
    c -> filaChao = criaFila();

    printf("Chão criado com sucesso!\n");

    return c;
}

int chaoVazio(chao *c) {
    if (estaVazia(c -> filaChao)) {
        return 1;
    }

    return 0;
}

void colocarNoChao(chao *c, formaTipo *f) {
    if (f == NULL || c == NULL) {
        return;
    }

    enqueue(c -> filaChao, f);
}

formaTipo *retirarDoChao(chao *c) {
    if (c == NULL) {
        return NULL;
    }

    formaTipo *removido = dequeue(c -> filaChao);
    return removido;
}

void killChao(chao *c) {
    if (c == NULL) {
        return;
    }

    free(c -> filaChao);
    free(c);
}