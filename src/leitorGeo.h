#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H

#include "fila.h"
#include "pilha.h"
#include "leitorDeArquivos.h"


/**
  Módulo responsável por interpretar e executar comandos do arquivo `.geo`, 
 *        armazenando as formas e gerando a saída em SVG.
 * 
 * Esse módulo processa o conteúdo lido de arquivos `.geo`, cria objetos geométricos 
 * correspondentes (círculo, retângulo, linha), e os armazena 
 * em estruturas auxiliares. Ele também é responsável por gerar a saída gráfica em formato SVG.
 */


/**
 * @typedef Chao
 * @brief Ponteiro opaco que representa a coleção de formas geométricas no ambiente do jogo.
 *
 * Funciona como um "handle" para a estrutura de dados que armazena todas as formas
 * criadas a partir do arquivo .geo, ocultando os detalhes da implementação.
 */
typedef void* CHAO;


/**
 * @brief Processa os comandos presentes no arquivo `.geo`.
 * 
 * Essa função percorre cada linha do arquivo `.geo`, interpreta os comandos (como "c", "r", "l", "t", "ts"),
 * e armazena as formas correspondentes nas filas e pilhas internas. Ao final, gera um arquivo `.svg`
 * com os elementos gráficos resultantes.
 * 
 * @param arqData Estrutura contendo os dados lidos do arquivo `.geo`, incluindo suas linhas.
 * @param saidaPath Caminho para o diretório onde o arquivo SVG de saída será criado.
 * @param sufixoCmd Sufixo a ser adicionado ao nome do arquivo de saída SVG, antes da extensão.
 * 
 * @return Um ponteiro opaco para o contexto (Chao) contendo todas as formas e estruturas alocadas.
 *         Esse ponteiro deve ser usado para operações posteriores e precisa ser desalocado com `killGeo`.
 */
CHAO processarGeo (DadosArquivo arqData, char *saidaPath, char *sufixoCmd);


/**
 * @brief Retorna a fila contendo todas as formas geométricas criadas no contexto `Chao`.
 * 
 * Essa fila pode ser usada para processamento adicional ou visualização das formas
 * fora do módulo `leitorGeo`.
 * 
 * @param chao Contexto de execução retornado por `processarGeo`.
 * @return Fila com os elementos gráficos processados.
 */
FILA getFChao (CHAO chao);


/**
 * Obtem a pilha para liberar formas do chão
 *
 * @param chao chao- O chão do qual se vai obter a pilha para liberar formas
 * @return A pilha para liberar formas
 */
PILHA getPFormasChaoFree (CHAO chao);


/**
 * @brief Libera toda a memória alocada para o contexto `Chao`.
 * 
 * Essa função desaloca todas as formas geométricas, estilos de texto, bem como
 * as estruturas auxiliares (fila, pilha) utilizadas durante o processamento.
 * 
 * @param chao Contexto a ser desalocado, retornado por `processarGeo`.
 */
void killGeo (CHAO chao);

#endif