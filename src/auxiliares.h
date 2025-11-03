#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "fila.h"
#include "pilha.h"
#include "struct.c"
#include "leitorGeo.h"
#include "leitorQry.h"

/**
 * @file auxiliares.h
 * @brief Funções auxiliares para manipulação de formas, clonagem, cálculo de áreas e detecção de sobreposições.
 *
 * Este módulo contém funções utilitárias que apoiam a execução dos comandos da arena.
 * Inclui criação de bounding boxes para detecção de colisões, clonagem de formas com modificação
 * de atributos, e funções auxiliares para gerenciar estruturas de carregadores/disparadores.
 * Também contém utilidades como recuperação de índice de disparador.
 */


 /**
 * @brief Retorna o índice de um disparador no array com base em seu ID.
 *
 * @param disparador Ponteiro para o array de disparadores.
 * @param contDisparos Quantidade de disparadores existentes.
 * @param id ID procurado.
 * @return Índice encontrado ou -1 caso não exista.
 */
int getDisparadorIndexPorId (disparadorSt **disparador, int contDisparos, int id);


/**
 * @brief Libera corretamente a memória associada a uma forma.
 *
 * Inclui a desalocação da estrutura da forma e seu conteúdo interno conforme o tipo.
 *
 * @param f Ponteiro para a FormaSt a ser destruída.
 */
void killForma (FormaSt *f);


/**
 * @brief Encapsula um dado de forma em uma estrutura FormaSt, atribuindo seu tipo.
 *
 * @param tp Tipo da forma (enum formaTipo).
 * @param data Ponteiro para a estrutura específica da forma.
 * @return Nova instância de FormaSt contendo os dados.
 */
FormaSt *encapsularForma (formaTipo tp, void *data);


/**
 * @brief Calcula a área de uma forma genérica, identificando seu tipo.
 *
 * @param tp Tipo da forma.
 * @param formaData Ponteiro para os dados da forma.
 * @return Área da forma ou 0 em caso de tipos sem área.
 */
double getAreaForma (formaTipo tp, void *formaData);


/**
 * @brief Cria uma bounding box (área delimitadora) para uma forma em uma posição no plano.
 *
 * @param f Estrutura contendo posição da forma na arena.
 * @return Estrutura bBox contendo os limites calculados.
 */

bBox criarBBoxParaForma (PosicaoFormaASt *f);


/**
 * @brief Verifica se duas bounding boxes se sobrepõem.
 *
 * @param a Bounding box A.
 * @param b Bounding box B.
 * @return 1 se sobrepõe, 0 caso contrário.
 */
int sobreposicaoBBox (bBox a, bBox b);


/**
 * @brief Verifica se duas formas se sobrepõem na arena.
 *
 * Determina as bounding boxes e utiliza @ref sobreposicaoBBox.
 *
 * @param a Primeira forma.
 * @param b Segunda forma.
 * @return 1 se houver colisão, 0 se não houver.
 */
int sobreposicaoFormas (PosicaoFormaASt *a, PosicaoFormaASt *b);


/**
 * @brief Clona uma forma alterando apenas a cor de borda.
 *
 * @param src Forma original.
 * @param novaCorB Nova cor de borda.
 * @return Forma clonada.
 */
FormaSt *clonarCorb (FormaSt *src, char *novaCorB);


/**
 * @brief Clona uma forma trocando automaticamente cor de borda e preenchimento.
 *
 * @param src Forma original.
 * @return Forma clonada com as cores invertidas.
 */
FormaSt *clonarCoresTrocadas (FormaSt *src);


/**
 * @brief Clona uma forma para uma nova posição na arena.
 *
 * @param src Forma original.
 * @param x Nova coordenada X.
 * @param y Nova coordenada Y.
 * @param chao Ponteiro para CHAO usado para registrar para posterior desalocação.
 * @return Forma clonada posicionada.
 */
FormaSt *clonarComPosicao (FormaSt *src, double x, double y, CHAO chao);


/**
 * @brief Clona uma forma atribuindo nova cor de borda e nova posição.
 *
 * @param src Forma original.
 * @param novaCorB Nova cor de borda.
 * @param x Nova coordenada X.
 * @param y Nova coordenada Y.
 * @param chao Gerenciador de memória do chão.
 * @return Forma clonada e posicionada.
 */
FormaSt *clonarEmComCorB (FormaSt *src, char *novaCorB, double x, double y, CHAO chao);


/**
 * @brief Clona uma forma trocando borda <-> preenchimento e altera sua posição.
 *
 * @param src Forma original.
 * @param x Nova posição X.
 * @param y Nova posição Y.
 * @param chao Gerenciador de memória para desalocação automática.
 * @return Forma clonada modificada.
 */
FormaSt *clonarEmComCoresTrocadas (FormaSt *src, double x, double y, CHAO chao);

#endif