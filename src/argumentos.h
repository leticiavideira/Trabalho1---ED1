#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

/** 
 * Este módulo contém as funções que serão
 * utilizadas para tratar os argumentos
 * que serão passados para o programa.
 */
   

/**
 * @brief Obtém o valor associado a uma opção específica dos argumentos da linha de comando.
 *
 * Esta função procura na lista de argumentos fornecida por uma opção que corresponda a `nomeOpt`
 * e retorna o valor que a segue. Se a opção não for encontrada ou não tiver um valor associado,
 * a função retorna NULL.
 *
 * @param arg Número de argumentos da linha de comando.
 * @param argVet Vetor de strings contendo os argumentos da linha de comando.
 * @param nomeOpt Nome da opção a ser procurada (ex: "--file").
 * @return Ponteiro para a string do valor associado à opção, ou NULL se não encontrado.
 */
char *getValorOpt (int arg, char *argVet[], char *nomeOpt);


/**
 * @brief Função para extrair o sufixo do comando (última string que não começa com '-')
 *
 * @param arg Número de argumentos da linha de comando.
 * @param argVet Vetor de strings contendo os argumentos da linha de comando.
 * 
 * @return Ponteiro para a string do valor associado ao sufixo, ou NULL se não encontrado.
 */
char *getSufixoCmd (int arg, char *argVet[]);

#endif