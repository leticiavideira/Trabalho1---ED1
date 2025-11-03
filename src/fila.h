#ifndef FILA_H
#define FILA_H

/**
 * @file fila.h
 * @brief Módulo de implementação de uma fila genérica em C.
 *
 * Este módulo fornece a definição e as funções para manipular uma estrutura
 * de dados do tipo fila (queue) com alocação dinâmica. A fila é implementada
 * como uma lista encadeada simples, permitindo inserção no final e remoção
 * no início (política FIFO — First In, First Out).
 *
 * Os dados armazenados na fila são do tipo `void*`, permitindo o uso genérico
 * com qualquer tipo de dado. O gerenciamento da memória dos dados armazenados
 * (conteúdo dos ponteiros) é responsabilidade do usuário.
 *
 * Funcionalidades oferecidas:
 *  - Criação e destruição de filas
 *  - Inserção (push) e remoção (pop) de elementos
 *  - Consulta ao elemento do início
 *  - Verificação se a fila está vazia
 *  - Consulta ao tamanho da fila
 *  - Excluir todos os elementos da fila, deixando-a vazia
 */


 /**
 * @brief Tipo opaco que representa uma fila genérica.
 * O ponteiro é tratado internamente como `struct Fila*`.
 */
typedef void* FILA;


/**
 * @brief Cria uma nova fila vazia.
 * 
 * @return Fila criada (ponteiro opaco).
 */
FILA criaFila ();


/**
 * @brief Insere um elemento no final da fila.
 * 
 * @param f Fila onde o elemento será inserido.
 * @param conteudo Ponteiro para o conteúdo a ser inserido.
 * @return 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int pushFila (FILA f, void *conteudo);


/**
 * @brief Remove o primeiro elemento da fila.
 * 
 * @param f Fila de onde o elemento será removido.
 * @return Ponteiro para o conteúdo removido ou NULL se a fila estiver vazia.
 */
void *popFila (FILA f);


/**
 * @brief Retorna o conteúdo do início da fila sem removê-lo.
 * 
 * @param f Fila a ser consultada.
 * @return Ponteiro para o conteúdo ou NULL se a fila estiver vazia.
 */
void *primeiroElemFila (FILA f);


/**
 * @brief Retorna a quantidade de elementos na fila.
 * 
 * @param f Fila a ser consultada.
 * @return Número de elementos na fila.
 */
int tamanhoFila (FILA f);


/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param f Fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int filaVazia (FILA f);


/**
 * @brief Libera todos os elementos da fila, deixando-a vazia.
 * 
 * @param f Fila a ser esvaziada.
 */
void limpaFila (FILA f);


/**
 * @brief Libera toda a memória alocada pela fila.
 * 
 * @param f Fila a ser desalocada.
 */
void killFila (FILA f);

#endif