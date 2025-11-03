#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "formas.h"
#include "pilha.h"

/**
 * @brief Estruturas principais de controle usadas na simulação da arena.
 *
 * Este módulo é um resumo que reúne todas as estruturas centrais necessárias para representar
 * formas encapsuladas, carregadores, disparadores, elementos posicionados na arena,
 * controle de desalocação e estatísticas de execução.
 */


 /**
 * @brief Estrutura genérica que encapsula qualquer forma (círculo, retângulo, linha ou texto).
 *
 * Cada forma é armazenada dentro de um @c void* apontando para a estrutura
 * específica do tipo correspondente, permitindo manipulação uniforme.
 */
typedef struct{
    formaTipo tipoF; /**< Tipo da forma (enum formaTipo). */
    void* data; /**< Ponteiro para os dados específicos da forma. */
} FormaSt;


/**
 * @brief Representa um carregador que armazena uma pilha de formas.
 *
 * Um carregador é associado posteriormente a um disparador.
 */
typedef struct{
    int id;  /**< Identificador único do carregador. */
    PILHA *formas;  /**< Pilha contendo as formas carregadas. */
}carregadorSt;


/**
 * @brief Representa um disparador que pode lançar formas na arena.
 *
 * Ele pode estar vinculado a até dois carregadores: esquerda e direita.
 */
typedef struct {
    int id;  /**< Identificador do disparador. */
    double x, y;  /**< Posição fixa do disparador na arena. */
    carregadorSt *cargaEsquerda;  /**< Carregador conectado à esquerda. */
    carregadorSt *cargaDireita;  /**< Carregador conectado à direita. */
    FormaSt *emDisparo;  /**< Forma atualmente pronta para ser disparada. */
    int cargaEsqId;  /**< ID do carregador da esquerda (para reconstrução de ponteiros). */
    int cargaDirId;  /**< ID do carregador da direita (para reconstrução de ponteiros). */
} disparadorSt;


/**
 * @brief Guarda a posição final de uma forma lançada na arena.
 *
 * Usada no processamento de colisões e cálculo de resultados.
 */
typedef struct{
    FormaSt *forma;  /**< Forma posicionada na arena. */
    double x, y;  /**< Coordenadas finais da forma. */
    int iA; /**< Flag indicando se houve anotação de dimensões (0 ou 1). */
    double disparadorX;  /**< Posição X do disparador que lançou a forma. */
    double disparadorY;  /**< Posição Y do disparador que lançou a forma. */
} PosicaoFormaASt;


/**
 * @brief Enum para identificação do tipo de ponteiro armazenado na pilha de desalocação.
 *
 * Usado para liberar dinamicamente todos os objetos criados durante a simulação.
 */
typedef enum {
    ARRAYDISPARADORF, ARRAYCARREGADORF, POSICAOFORMAF, PILHAF
} TIPOF;


/**
 * @brief Estrutura que encapsula ponteiros para gerenciamento da desalocação final.
 */
typedef struct{
    void *p;   /**< Ponteiro genérico para o objeto a ser liberado. */
    TIPOF tp;  /**< Tipo do objeto, usado para escolher o método correto de liberação. */
} ItemFree;


/**
 * @brief Representa uma caixa delimitadora (Bounding Box) de uma forma na arena.
 */
typedef struct {
    double minX, minY; /**< Menor coordenada X e Y ocupada pela forma. */
    double maxX, maxY; /**< Maior coordenada X e Y ocupada pela forma. */
} bBox;


/**
 * @brief Estrutura de estatísticas acumuladas durante execução.
 */
typedef struct {
    int instrucoesExecutadas;   /**< Contagem de comandos interpretados. */
    int disparos;   /**< Total de disparos realizados. */
    int formasEsmagadas;  /**< Total de formas destruídas. */
    int formasClonadas;  /**< Total de formas clonadas. */
    double areaEsmagadaTotal;  /**< Soma acumulada das áreas esmagadas. */
} Estatisticas;