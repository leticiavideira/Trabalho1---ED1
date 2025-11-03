#ifndef RETANGULO_H
#define RETANGULO_H

/**
 * @file retangulo.h
 * @brief Módulo de implementação da estrutura de dados Retângulo
 * 
 * Este módulo fornece uma implementação completa para manipulação de retângulos
 * geométricos em um espaço bidimensional. Cada retângulo é definido por uma posição
 * (x, y), dimensões (largura e altura), cores de preenchimento e borda, além de
 * possuir um identificador único.
 * 
 * @note A estrutura utiliza encapsulamento através de ponteiro opaco (void*),
 *       garantindo abstração completa da implementação interna.
 * @note Todas as funções getter são seguras para uso e retornam valores válidos
 *       quando recebem uma instância de Retangulo válida.
 */


 /**
 * @typedef RETANGULO
 * Tipo opaco que representa um retângulo.
 */
typedef void* RETANGULO;


/**
 * @brief Cria um novo retângulo com os atributos especificados.
 *
 * @param i Identificador único do retângulo.
 * @param x Coordenada X da posição do retângulo.
 * @param y Coordenada Y da posição do retângulo.
 * @param h Altura do retângulo.
 * @param w Largura do retângulo.
 * @param corb Cor da borda (string).
 * @param corp Cor de preenchimento (string).
 * @return Um ponteiro para o retângulo criado.
 */
RETANGULO criaRetangulo (int i, double x, double y, double w, double h, char* corb, char* corp);


/**
 * @brief Retorna o ID do retângulo.
 *
 * @param r Retângulo.
 * @return ID do retângulo.
 */
int getId_R (RETANGULO r);


/**
 * @brief Retorna a coordenada X do retângulo.
 *
 * @param r Retângulo.
 * @return Valor de X.
 */
double getX_R (RETANGULO r);


/**
 * @brief Retorna a coordenada Y do retângulo.
 *
 * @param r Retângulo.
 * @return Valor de Y.
 */
double getY_R (RETANGULO r);


/**
 * @brief Retorna a largura do retângulo.
 *
 * @param r Retângulo.
 * @return Largura.
 */
double getW_R (RETANGULO r);


/**
 * @brief Retorna a altura do retângulo.
 *
 * @param r Retângulo.
 * @return Altura.
 */
double getH_R (RETANGULO r);



/**
 * @brief Calcula a área do retângulo.
 *
 * @param r Retângulo.
 * @return Área calculada (altura * largura).
 */
double calcularArea_R (RETANGULO r);




/**
 * @brief Retorna a cor da borda do retângulo.
 *
 * @param r Retângulo.
 * @return String com a cor da borda.
 */
char* getCorB_R (RETANGULO r);


/**
 * @brief Retorna a cor de preenchimento do retângulo.
 *
 * @param r Retângulo.
 * @return String com a cor de preenchimento.
 */
char* getCorP_R (RETANGULO r);




/**
 * @brief Define um novo ID para o retângulo.
 *
 * @param r Retângulo.
 * @param i Novo ID.
 */
void setId_R (RETANGULO r, int i);


/**
 * @brief Define uma nova coordenada X para o retângulo.
 *
 * @param r Retângulo.
 * @param x Nova coordenada X.
 */
void setX_R (RETANGULO r, double x);

/**
 * @brief Define uma nova coordenada Y para o retângulo.
 *
 * @param r Retângulo.
 * @param y Nova coordenada Y.
 */
void setY_R (RETANGULO r, double y);


/**
 * @brief Define uma nova largura para o retângulo.
 *
 * @param r Retângulo.
 * @param w Nova largura.
 */
void setW_R (RETANGULO r, double w);


/**
 * @brief Define uma nova altura para o retângulo.
 *
 * @param r Retângulo.
 * @param h Nova altura.
 */
void setH_R (RETANGULO r, double h);


/**
 * @brief Define uma nova cor de borda para o retângulo.
 *
 * @param r Retângulo.
 * @param cb Nova cor da borda (string).
 */
void setCorB_R (RETANGULO r, char* cb);


/**
 * @brief Define uma nova cor de preenchimento para o retângulo.
 *
 * @param r Retângulo.
 * @param cp Nova cor de preenchimento (string).
 */
void setCorP_R (RETANGULO r, char* cp);


/**
 * @brief Libera a memória alocada para o retângulo.
 *
 * @param r Retângulo a ser desalocado.
 */
void kill_R (RETANGULO r);

#endif