#ifndef COR_H
#define COR_H

#include <stdlib.h>
#include <string.h>

/**
 * Módulo com uma função utilitária que encontra uma cor complementar a outra no sistema hexadecimal
 */

/**
 * @brief Calcula a cor complementar (inversa) de uma cor fornecida.
 *
 * Aceita formatos hex (ex: "#FF0000" ou "#F00").
 *
 * @param cor A string (constante) da cor original.
 * @return Um ponteiro para uma string estática (buffer interno) contendo o 
 * hex da cor complementar (ex: "#00FFFF"). 
 * 
 */
char *inverterCor (char *cor);

#endif