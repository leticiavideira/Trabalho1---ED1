#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * Módulo para gerenciamento de estilos de texto (TextStyle).
 * Define uma interface para criação, acesso e destruição de objetos que armazenam
 * informações sobre estilo de texto: família da fonte (font family), espessura da fonte
 * (font weight) e tamanho da fonte (font size).
 * 
 * A estrutura interna do TextStyle é oculta (opaca), garantindo encapsulamento e
 * evitando acesso direto aos campos. A manipulação é feita apenas por meio das funções
 * fornecidas neste header.
 */


/**
 * @typedef TEXTO
 * Tipo opaco que representa um objeto texto.
 */
typedef void* ESTILO_TEXTO;


/**
 * @brief Cria um novo objeto TextStyle para armazenar as características de um estilo
 * de texto com base nos parâmetros fornecidos.
 * 
 * @param fFamily Ponteiro para string com o nome da família da fonte (font family). Não pode ser NULL.
 * @param fWeight Ponteiro para string com o peso da fonte (font weight), ex: "bold", "normal".
 * @param fSize Inteiro representando o tamanho da fonte (font size).
 * 
 * @return void* Retorna um ponteiro genérico para o objeto criado, ou NULL em caso de falha na alocação.
 */
ESTILO_TEXTO criaEstiloTexto (char* fFamily, char* fWeight, int fSize);


/**
 * @brief Retorna a font family de um objeto TextStyle.
 * 
 * @param ts Ponteiro para o objeto TextStyle.
 * 
 * @return char* Ponteiro para a string contendo a font family, ou NULL se textstyle for NULL.
 */
char* getfFamily_T (ESTILO_TEXTO ts);


/**
 * @brief Retorna a font weight de um objeto TextStyle.
 * 
 * @param ts Ponteiro para o objeto TextStyle.
 * 
 * @return char* Ponteiro para a string contendo a font weight, ou NULL se textstyle for NULL.
 */
char* getfWeight_T (ESTILO_TEXTO ts);


/**
 * @brief Retorna o font size de um objeto TextStyle.
 * 
 * @param ts Ponteiro para o objeto TextStyle.
 * 
 * @return int Valor inteiro do tamanho da fonte, ou 0 se textstyle for NULL.
 */
int getfSize_T (ESTILO_TEXTO ts);


/**
 * @brief Libera toda a memória associada a um objeto TextStyle.
 * 
 * @param ts Ponteiro retornado por criaTextStyle. Se for NULL, nada acontece.
 */
void killEstiloTexto (ESTILO_TEXTO ts);

#endif