#ifndef LEITOR_DE_ARQUIVOS_H
#define LEITOR_DE_ARQUIVOS_H

#include "fila.h"

/**
 * @file leitorDeArquivos.h
 * @brief Biblioteca para leitura de arquivos texto em memória, linha por linha.
 *
 * Este módulo fornece funções para criar uma estrutura que representa um arquivo,
 * contendo seu caminho, nome e as linhas lidas armazenadas em uma fila dinâmica.
 * Permite acessar o caminho e nome do arquivo, bem como iterar pelas linhas carregadas.
 * Também é responsável por liberar corretamente toda a memória alocada. 
 */


/**
 * @brief Estrutura que representa um arquivo lido, contendo seu caminho, nome e as linhas em uma fila.
 */
typedef void* DadosArquivo;


/**
 * @brief Cria uma nova instância de DadosArquivo, lendo o conteúdo do arquivo especificado.
 *
 * @param arqPath Caminho completo do arquivo a ser lido.
 * @return Ponteiro para DadosArquivo criado, ou NULL em caso de erro.
 */
DadosArquivo criarDadosArq (char * arqPath);


/**
 * @brief Obtém o caminho completo do arquivo armazenado em DadosArquivo.
 *
 * @param arqData Ponteiro para DadosArquivo.
 * @return Ponteiro constante para a string com o caminho do arquivo.
 */
char* getPathArq (DadosArquivo arqData);


/**
 * @brief Obtém o nome do arquivo (apenas o nome, sem o caminho).
 *
 * @param arqData Ponteiro para DadosArquivo.
 * @return Ponteiro constante para a string com o nome do arquivo.
 */
char* getNomeArq (DadosArquivo arqData);


/**
 * @brief Obtém a fila contendo as linhas do arquivo.
 *
 * Cada elemento da fila é uma string alocada dinamicamente contendo uma linha do arquivo.
 * O usuário é responsável por tratar esses dados com cuidado.
 *
 * @param arqData Ponteiro para DadosArquivo.
 * @return Ponteiro para Fila contendo as linhas do arquivo.
 */
FILA getFilaLinhasArq (DadosArquivo arqData);


/**
 * @brief Libera a memória alocada para DadosArquivo e todas as linhas armazenadas.
 *
 * @param dados Ponteiro para DadosArquivo a ser destruído.
 */
void destruirDadosArq (DadosArquivo arqData);

#endif