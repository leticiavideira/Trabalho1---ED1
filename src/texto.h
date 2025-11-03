#ifndef TEXTO_H
#define TEXTO_H

/**
 * Interface para o módulo de manipulação de textos gráficos.
 * Define o tipo abstrato TEXTO e uma série de funções para criação,
 * acesso e modificação de objetos de texto utilizados em contextos gráficos,
 * mais especificamente svg
 */


/**
 * @typedef TEXTO
 * Tipo opaco que representa um objeto texto.
 */
typedef void* TEXTO;


/**
  * @brief Cria um novo objeto TEXTO com os atributos especificados.
  * 
  * @param i Identificador único do texto.
  * @param x Coordenada X da posição do texto.
  * @param y Coordenada Y da posição do texto.
  * @param corb Cor da borda (cor do contorno, geralmente aplicada ao traçado do texto).
  * @param corp Cor de preenchimento (cor da fonte, o "fill").
  * @param a Caractere que define a âncora de alinhamento do texto:
  *               - 'i' (início / left)
  *               - 'm' (meio / center)
  *               - 'f' (fim / right)
  * @param txto String de texto a ser exibido.
  * 
  * @return Ponteiro para o TEXTO criado.
  */
TEXTO criaTexto (int i, double x, double y, char* corb, char* corp, char a, char* txto);


/**
 * @brief Retorna o ID do objeto texto.
 *
 * @param t texto.
 * @return ID do objeto texto.
 */
int getId_T (TEXTO t);


/**
 * @brief Retorna a coordenada X da âncora do texto.
 *
 * @param t texto.
 * @return Coordenada X da âncora do texto.
 */
double getX_T (TEXTO t);


/**
 * @brief Retorna a coordenada Y da âncora do texto.
 *
 * @param t texto.
 * @return Coordenada Y da âncora do texto.
 */
double getY_T (TEXTO t);


/**
 * @brief Retorna a cor de borda do texto.
 *
 * @param t texto.
 * @return cor de borda do texto (String).
 */
char* getCorb_T (TEXTO t);


/**
 * @brief Retorna a cor de preenchimento do texto.
 *
 * @param t texto.
 * @return cor de preenchimento do texto (String).
 */
char* getCorp_T (TEXTO t);


/**
 * @brief Retorna a âncora do texto: 
 *               - 'i' (início / left)
 *               - 'm' (meio / center)
 *               - 'f' (fim / right)
 * @param t texto.
 * @return âncora do texto (char).
 */
char getA_T (TEXTO t);


/**
 * @brief Retorna o conteúdo textual do objeto texto.
 *
 * @param t texto.
 * @return ponteiro para string constante com o conteúdo do Texto. Pode ser NULL se vazio.
 */
char* getTxto_T (TEXTO t);


/**
  * @brief Retorna o comprimento de linha do texto conforme o especificado (10 * número de caracteres)
  * 
  * @param t texto.
  * @return comprimento de linha do texto.
  */
double comprimento_T (TEXTO t);

/**
  * @brief Retorna a coordenada x inicial do texto;
  * 
  * @param t texto.
  */
double calcX1_T (TEXTO t);


/**
  * @brief Retorna a coordenada y inicial do texto;
  * 
  * @param t texto.
  */
double calcX2_T (TEXTO t);


/**
 * @brief Calcula a área do objeto Texto conforme o especificado (20 * número de caracteres).
 *
 * @param t texto.
 * @return Área calculada.
 */
double calcularArea_T (TEXTO t);


/**
 * @brief Define um novo ID para o objeto Texto.
 *
 * @param t texto.
 * @param i Novo ID.
 */
void setId_T (TEXTO t, int i);


/**
 * @brief Define uma nova coordenada X para o objeto Texto.
 *
 * @param t texto.
 * @param x Novo X.
 */
void setX_T (TEXTO t, double x);


/**
 * @brief Define uma nova coordenada Y para o objeto Texto.
 *
 * @param t texto.
 * @param y Novo Y.
 */
void setY_T (TEXTO t, double y);


/**
 * @brief Define uma nova cor de borda para o objeto Texto.
 *
 * @param t texto.
 * @param cb Nova cor de borda.
 */
void setCorb_T (TEXTO t, char* cb);


/**
 * @brief Define uma nova cor de preenchimento para o objeto Texto.
 *
 * @param t texto.
 * @param cp Nova cor de preenchimento.
 */
void setCorp_T (TEXTO t, char* cp);


/**
 * @brief Define uma nova âncora para o objeto Texto:
 *               - 'i' (início / left)
 *               - 'm' (meio / center)
 *               - 'f' (fim / right)
 *
 * @param t texto.
 * @param a Nova âncora.
 */
void setA_T (TEXTO t, char a);


/**
 * @brief Define um novo conteúdo textual para o objeto texto.
 *
 * @param t texto.
 * @param txto novo conteúdo textual.
 */
void setTxto_T (TEXTO t, char* txto);


/**
 * @brief Libera a memória alocada para o objeto texto.
 *
 * @param t texto a ser desalocado.
 */
void kill_T (TEXTO t);

#endif