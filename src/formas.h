#ifndef FORMAS_H
#define FORMAS_H


/**
 * @enum formaTipo
 * @brief Tipos de formas gráficos suportados pela biblioteca.
 *
 * Enumera os diferentes tipos de elementos gráficos que podem ser
 * criados e manipulados pela aplicação (formas geométricas e texto/estilo).
 *
 * Valores:
 *  - CIRCLE:      Representa um círculo.
 *  - RECTANGLE:   Representa um retângulo.
 *  - LINE:        Representa uma linha reta.
 *  - TEXT:        Representa um elemento de texto a ser renderizado.
 *  - TEXT_STYLE:  Representa propriedades de estilo de texto
 *                  (por exemplo fonte, tamanho, cor, alinhamento).
 */
enum formatipo {CIRCLE, RECTANGLE, LINE, TEXT, TEXT_STYLE};

typedef enum formatipo formaTipo;

#endif