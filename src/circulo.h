#ifndef CIRCULO_H
#define CIRCULO_H

/*
 * @file circulo.h
 * @brief Interface para o módulo de Circulo.
 *
 * Este arquivo contém a interface pública para criação, destruição, acesso e modificação
 * de objetos Círculo. Cada círculo possui um identificador único, coordenadas (x, y),
 * raio, cor de borda (stroke) e cor de preenchimento (fill).
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação dos círculos
 * e fornece funções getter/setter para manipulação das propriedades, além de cálculos
 * de área.
 */


 /**
 * @typedef CIRCULO
 * Tipo opaco que representa um círculo.
 */
typedef void* CIRCULO;


/**
 * @brief Cria e inicializa um novo círculo.
 * 
 * @param i Identificador do círculo.
 * @param x Coordenada X do centro do círculo.
 * @param y Coordenada Y do centro do círculo.
 * @param raio Raio do círculo.
 * @param corp Cor de preenchimento do círculo (string).
 * @param corb Cor da borda do círculo (string).
 * @return CIRCULO Retorna um ponteiro para o novo círculo criado.
 */
CIRCULO criaCirculo (int i, double x, double y, double r, char* corb, char* corp);


/**
 * @brief Retorna o ID do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return int ID do círculo.
 */
int getId_C (CIRCULO c);


/**
 * @brief Retorna a coordenada X do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return double Coordenada X.
 */
double getX_C (CIRCULO c);


/**
 * @brief Retorna a coordenada Y do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return double Coordenada Y.
 */
double getY_C (CIRCULO c);


/**
 * @brief Retorna o raio do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return double Raio do círculo.
 */
double getR_C (CIRCULO c);


/**
 * @brief Calcula e retorna a área do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return double Área do círculo (π * r²).
 */
double calcularArea_C (CIRCULO c);


/**
 * @brief Retorna a cor da borda do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return char* String contendo a cor da borda.
 */
char* getCorB_C (CIRCULO c);


/**
 * @brief Retorna a cor de preenchimento do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @return char* String contendo a cor de preenchimento.
 */
char* getCorP_C (CIRCULO c);




/**
 * @brief Define o ID do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param i Novo ID a ser definido.
 */
void setId_C (CIRCULO c, int i);


/**
 * @brief Define a coordenada X do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param x Novo valor para a coordenada X.
 */
void setX_C (CIRCULO c, double x);


/**
 * @brief Define a coordenada Y do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param y Novo valor para a coordenada Y.
 */
void setY_C (CIRCULO c, double y);


/**
 * @brief Define o raio do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param r Novo valor de raio.
 */
void setR_C (CIRCULO c, double r);


/**
 * @brief Define a cor da borda do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param cb Nova cor da borda (string).
 */
void setCorB_C (CIRCULO c, char* cb);


/**
 * @brief Define a cor de preenchimento do círculo.
 * 
 * @param c Ponteiro para o círculo.
 * @param cp Nova cor de preenchimento (string).
 */
void setCorP_C (CIRCULO c, char* cp);


/** 
 * @brief Libera toda a memória alocada para um circulo.
 *
 * @param c, ponteiro para o circulo a ser destruído
 *
 * @pre O parâmetro c deve referenciar um circulo válido.
 * 
 */
void kill_C (CIRCULO c);

#endif