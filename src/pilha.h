#ifndef PILHA_H
#define PILHA_H

/**
 * Este módulo define uma estrutura de dados do tipo pilha (stack) com
 * alocação dinâmica. A pilha segue o comportamento LIFO (Last In, First Out),
 * permitindo inserções e remoções apenas no topo.
 *
 * Os elementos armazenados na pilha são ponteiros genéricos,
 * permitindo o uso com diferentes tipos de dados. O gerenciamento da memória
 * dos conteúdos apontados é responsabilidade do usuário.
 *
 * Funcionalidades oferecidas:
 *  - Criação e destruição da pilha
 *  - Inserção (push) e remoção (pop) de elementos
 *  - Consulta ao topo da pilha
 *  - Verificação se a pilha está vazia
 *  - Consulta ao tamanho atual da pilha
 *  - Procurar um elemento no meio da pilha
 *  - Excluir todos os elementos da fila, deixando-a vazia
 */

/**
 * @brief Tipo abstrato que representa a pilha como um ponteiro genérico.
 */
typedef void* PILHA;


/**
 * @brief Cria uma nova pilha vazia.
 * 
 * @return Pilha criada (ponteiro opaco).
 */
PILHA criaPilha ();


/**
 * @brief Insere um elemento no topo da pilha.
 * 
 * @param p Pilha na qual o elemento será inserido.
 * @param conteudo Ponteiro para o conteúdo a ser inserido.
 * @return 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int pushPilha (PILHA p, void *conteudo);


/**
 * @brief Remove o elemento do topo da pilha.
 * 
 * @param p Pilha de onde o elemento será removido.
 * @return Ponteiro para o conteúdo removido ou NULL se a pilha estiver vazia.
 */
void *popPilha (PILHA p);


/**
 * @brief Retorna o conteúdo do topo da pilha sem removê-lo.
 * 
 * @param p Pilha a ser consultada.
 * @return Ponteiro para o conteúdo do topo ou NULL se a pilha estiver vazia.
 */
void *topoPilha (PILHA p);


/**
 * @brief Retorna o elemento da pilha no índice especificado sem remove-lo
 * 
 * @param p Poteiro para a pilha
 * @param index Indice do elemento ( 0 é o topo da pilha)
 * @return Conteúdo do elemento no indice ou NULL se a pilha for vazia ou o indice inválido
 */
void *acharElemPilha (PILHA p, int index);


/**
 * @brief Retorna a quantidade de elementos na pilha.
 * 
 * @param p Pilha a ser consultada.
 * @return Número de elementos na pilha.
 */
int tamanhoPilha (PILHA p);


/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param p Pilha a ser verificada.
 * @return 1 se estiver vazia, 0 caso contrário.
 */
int pilhaVazia (PILHA p);


/**
 * @brief Remove todos os elementos da pilha.
 * 
 * @param p Pilha a ser desalocada.
 */
void limpaPilha (PILHA p);


/**
 * @brief Libera toda a memória alocada pela pilha.
 * 
 * @param p Pilha a ser desalocada.
 */
void killPilha (PILHA p);

#endif