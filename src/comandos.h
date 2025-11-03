#ifndef COMANDOS_H
#define COMANDOS_H

#include "fila.h"
#include "pilha.h"
#include "leitorGeo.h"
#include "auxiliares.h"

/**
 * @file comandos.h
 * @brief Módulo responsável pela execução dos comandos do arquivo `.qry`.
 *
 * Este módulo contém as funções que simulam a execução das instruções
 * presentes no arquivo de consultas (`.qry`). Cada função representa uma
 * instrução que manipula os elementos da arena — disparadores, carregadores
 * e formas geométricas — de acordo com as regras da simulação.
 *
 * As funções realizam operações como:
 * - Posicionar disparadores na arena;
 * - Carregar formas no carregador;
 * - Vincular carregadores a disparadores;
 * - Transferir formas entre carregadores e disparadores;
 * - Disparar formas com deslocamentos específicos;
 * - Simular disparos em rajada;
 * - Calcular colisões, destruições e clones entre as formas disparadas.
 *
 * Cada função atualiza o arquivo de saída textual (`.txt`) e as estruturas
 * de dados usadas na simulação.
 */


/**
 * @brief Posiciona um novo disparador na arena.
 * 
 *  Lê os parâmetros da linha atual do `.qry` e adiciona um novo disparador
 * no vetor de disparadores, armazenando-o na pilha de elementos livres (`pilhaFree`).
 *
 * @param disparador Ponteiro duplo para o vetor de disparadores ativos.
 * @param contDisparos Ponteiro para o contador de disparadores existentes.
 * @param pilhaFree Pilha global contendo referências de memória para liberação posterior.
 * @param stats Estrutura de estatísticas do programa; o campo `instrucoesExecutadas` é incrementado.
 *
 */
void pdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, Estatisticas *stats);


/**
 * @brief Carrega as primeiras N formas do chão em um carregador.
 *
 * Se o carregador ainda não existir, é criado e adicionado à lista.
 * As formas são removidas da fila do chão (`CHAO`) e empilhadas na
 * pilha de formas do carregador.
 *
 * Os dados de cada forma carregada são registrados no arquivo `.txt`.
 *
 * @param carregador Ponteiro duplo para o vetor de carregadores.
 * @param contCarregador Ponteiro para o contador de carregadores existentes.
 * @param chao Estrutura representando o chão (fila de formas).
 * @param pilhaFree Pilha global de alocação dinâmica para liberação posterior.
 * @param txtFile Arquivo de saída textual onde os logs são escritos.
 * @param stats Estrutura de estatísticas (incrementa `instrucoesExecutadas`).
 *
 */
void lcExecutar (carregadorSt **carregador, int *contCarregador, CHAO chao, PILHA pilhaFree, FILE *txtFile, Estatisticas *stats);


/**
 * @brief Acopla dois carregadores (esquerdo e direito) a um disparador.
 *
 * Caso os carregadores informados não existam, eles são criados automaticamente.
 * O disparador passa a armazenar ponteiros para esses carregadores, permitindo
 * as operações de transferência (via comando `shft`).
 *
 * @param carregador Ponteiro duplo para o vetor de carregadores disponíveis.
 * @param contCarregador Ponteiro para o contador de carregadores.
 * @param disparador Ponteiro duplo para o vetor de disparadores.
 * @param contDisparos Ponteiro para o contador de disparadores.
 * @param pilhaFree Pilha global para gerenciamento de memória.
 * @param stats Estrutura de estatísticas (incrementa `instrucoesExecutadas`).
 *
 */
void atchExecutar (carregadorSt **carregador, int *contCarregador, disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, Estatisticas *stats);


/**
 * @brief Simula o acionamento do botão de transferência (`shift`).
 *
 * Move formas entre os carregadores e o disparador, conforme o botão pressionado:
 * - `'e'`: descarrega da esquerda e empurra o conteúdo atual para a direita;
 * - `'d'`: descarrega da direita e empurra o conteúdo atual para a esquerda.
 *
 * Após o movimento, a forma presente na posição de disparo é registrada no `.txt`.
 *
 * @param disparador Vetor de disparadores.
 * @param contDisparos Ponteiro para o número de disparadores existentes.
 * @param carregador Vetor de carregadores disponíveis.
 * @param contCarregador Ponteiro para o número de carregadores existentes.
 * @param txtFile Arquivo `.txt` de saída (log do processo).
 * @param stats Estrutura de estatísticas (incrementa `instrucoesExecutadas`).
 *
 */
void shftExecutar (disparadorSt **disparador, int *contDisparos, carregadorSt *carregador, int *contCarregador, FILE *txtFile, Estatisticas *stats);


/**
 * @brief Dispara a forma atualmente carregada no disparador.
 *
 * Move a forma da posição de disparo para a arena, aplicando deslocamentos
 * horizontais e verticais (`dx`, `dy`). Pode incluir anotações visuais
 * (como linhas de guia e distâncias) no SVG final.
 *
 * @param disparador Vetor de disparadores existentes.
 * @param contDisparos Ponteiro para o número de disparadores.
 * @param arena Pilha contendo as formas que já foram disparadas.
 * @param pilhaFree Pilha global para rastrear alocações.
 * @param txtFile Arquivo `.txt` de saída (log de disparo).
 * @param stats Estrutura de estatísticas (incrementa `disparos` e `instrucoesExecutadas`).
 *
 */
void dspExecutar (disparadorSt **disparador, int *contDisparos, PILHA arena, PILHA pilhaFree, FILE *txtFile, Estatisticas *stats);


/**
 * @brief Realiza uma rajada de disparos automáticos.
 *
 * Dispara sucessivamente todas as formas contidas em um carregador,
 * aplicando deslocamentos iniciais (`dx`, `dy`) e incrementos a cada disparo (`incX`, `incY`).
 * Cada disparo é registrado no arquivo `.txt` e a forma é inserida na arena.
 *
 * @param disparador Vetor de disparadores.
 * @param contDisparos Ponteiro para o número de disparadores ativos.
 * @param pilhaFree Pilha de alocações dinâmicas.
 * @param arena Pilha onde as formas disparadas são armazenadas.
 * @param carregador Vetor de carregadores.
 * @param contCarregador Ponteiro para o número de carregadores.
 * @param txtFile Arquivo de log textual.
 * @param stats Estrutura de estatísticas (incrementa `instrucoesExecutadas` e `disparos`).
 *
 */
void rjdExecutar (disparadorSt **disparador, int *contDisparos, PILHA pilhaFree, PILHA arena, carregadorSt *carregador, int *contCarregador, FILE *txtFile, Estatisticas *stats);

/**
 * @brief Calcula colisões entre formas da arena e atualiza o chão.
 *
 * As formas disparadas são comparadas entre si:
 * - Se sobrepostas, é feita a destruição (esmagamento) ou clonagem;
 * - Formas esmagadas são marcadas com um asterisco vermelho (`*`);
 * - Áreas esmagadas e estatísticas são registradas no arquivo `.txt`.
 *
 * @param arena Pilha com as formas presentes na arena.
 * @param chao Estrutura `CHAO` onde as formas remanescentes e clones são colocados.
 * @param txtFile Arquivo `.txt` de saída (contendo as métricas calculadas).
 * @param stats Estrutura de estatísticas com os contadores de formas e áreas.
 *
 */
void calcExecutar (PILHA arena, CHAO chao, FILE *txtFile, Estatisticas *stats);


#endif