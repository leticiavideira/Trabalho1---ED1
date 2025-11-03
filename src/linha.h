#ifndef LINHA_H
#define LINHA_H


/**
 * @file linha.h
 * @brief Módulo de implementação da estrutura de dados Linha
 * 
 * Este módulo fornece uma implementação completa para manipulação de linhas
 * geométricas em um espaço bidimensional. Cada linha é definida por dois pontos
 * (x1, y1) e (x2, y2) que determinam sua posição e orientação, além de possuir
 * um identificador único e uma cor associada.
 * 
 * @note A estrutura utiliza encapsulamento através de ponteiro opaco (void*),
 *       garantindo abstração completa da implementação interna.
 * @note Todas as funções getter são seguras para uso e retornam valores válidos
 *       quando recebem uma instância de Linha válida.
 */


/**
 * @typedef TEXTO
 * Tipo opaco que representa um objeto texto.
 */
typedef void* LINHA;


/**
 * @brief Cria uma nova linha com os pontos (x1,y1) e (x2,y2).
 * 
 * @param i Identificador único da linha.
 * @param x1 Coordenada X do ponto inicial da linha.
 * @param y1 Coordenada Y do ponto inicial da linha.
 * @param x2 Coordenada X do ponto final da linha.
 * @param y2 Coordenada Y do ponto final da linha.
 * @param cor Cor da linha (string).
 * @return Um ponteiro para a linha criada (tipo LINHA).
 */
LINHA criaLinha (int i, double x1, double y1, double x2, double y2, char* cor);


/**
 * @brief Obtém o identificador da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return O identificador da linha.
 */
int getId_L (LINHA l);


/**
 * @brief Obtém a coordenada X do ponto inicial da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return A coordenada X do ponto inicial.
 */
double getX1_L (LINHA l);


/**
 * @brief Obtém a coordenada Y do ponto inicial da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return A coordenada Y do ponto inicial.
 */
double getY1_L (LINHA l);


/**
 * @brief Obtém a coordenada X do ponto final da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return A coordenada X do ponto final.
 */
double getX2_L (LINHA l);


/**
 * @brief Obtém a coordenada Y do ponto final da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return A coordenada Y do ponto final.
 */
double getY2_L (LINHA l);


/**
 * @brief Obtém a cor da linha.
 * 
 * @param l Ponteiro para a linha.
 * @return Ponteiro para a string que representa a cor da linha.
 */
char* getCor_L (LINHA l);


/**
 * @brief Calcula a "área" associada à linha.
 *
 * No contexto deste programa, define-se a "área" da linha como sendo 10 vezes
 * o seu comprimento, ou seja:
 *
 *     área = 2 * sqrt((x2 - x1)² + (y2 - y1)²)
 *
 * Essa definição permite a comparação com áreas de figuras geométricas reais.
 *
 * @param l Ponteiro para a linha.
 * @return Valor da "área" (comprimento * 10).
 */
double calcularArea_L (LINHA l);



/**
 * @brief Define o identificador da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param i Novo identificador.
 */
void setId_L (LINHA l, int i);


/**
 * @brief Define a coordenada X do ponto inicial da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param x1 Nova coordenada X inicial.
 */
void setX1_L (LINHA l, double x1);


/**
 * @brief Define a coordenada Y do ponto inicial da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param y1 Nova coordenada Y inicial.
 */
void setY1_L (LINHA l, double y1);


/**
 * @brief Define a coordenada X do ponto final da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param x2 Nova coordenada X final.
 */

void setX2_L (LINHA l, double x2);


/**
 * @brief Define a coordenada Y do ponto final da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param y2 Nova coordenada Y final.
 */
void setY2_L (LINHA l, double y2);


/**
 * @brief Define a cor da linha.
 * 
 * @param l Ponteiro para a linha.
 * @param cor Nova cor (string).
 */
void setCor_L (LINHA l, char* cor);


/**
 * @brief Libera a memória alocada para a linha.
 * 
 * @param l Ponteiro para a linha.
 */
void kill_L (LINHA l);

#endif