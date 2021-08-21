/*
 * Ordenação de Vetores utilizando Árvore
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include <iostream>
#include <cassert>
#include <math.h>

#include "../Queue/Queue.h"

#ifndef TREESORT_H
#define TREESORT_H

using namespace std;

class TreeSort {
  private:

    Node *root; // Nó-raiz da árvore
    int vectorSize; // Tamanho do vetor
    int maxValue; // Guarda o maior valor do vetor + 1
    int *vector; // Vetor padrão, antes de ser ordenado
    int *stateVector; // Vetor utilizado para armazenar os status da ordenação, ou seja, se um valor já foi ordenado ou não
    int *sortedVector; // Vetor ordenado

    // Retorna se a árvore está vazia ou não
    bool empty();

    // Método para construção da árvore a partir de uma fila de folhas gerada na função generateLeaves
    Node *buildTree(Queue leavesQueue);

    // Método para gerar as folhas com base no vetor de estado
    Queue generateLeaves();

    // Retorna a posição do vetor de estado que contém a chave da raíz
    int getIndexByRootKey();

    // Função recursiva utilizada para limpar todos os nós da árvore
    Node *clear(Node *node);

    // Função recursiva que printa os nós-filhos (esquerda e direita) a partir do nó passado por parâmetro
    void _print(Node *node);

    // Função recursiva que retorna o número de nós existentes a partir do nó passado por parâmetro
    int _getTreeSize(Node *node);

  public:

    /*
     * Construtor que recebe o tamanho do vetor e o vetor,
     * constrói e inicia a árvore e executa o método de ordenação, salvando o
     * novo vetor ordenado no atributo *sortedVector
     */
    TreeSort(int _vectorSize, int *_vector);

    // Destrutor (desaloca da memória todos os atributos do vetor, inclusive os nós da árvore)
    ~TreeSort();

    // Printa todos os nós-filhos a partir do nó-raíz
    void print();

    // Retorna o vetor ordenado
    int *getSortedVector();

    // Retorna o tamanho do vetor
    int getVectorSize();

    /*
     * Retorna o número de nós da árvore (utilizando-se da função _getTreeSize, passando como parâmetro inicial o nó-raiz)
     * Uma maneira alternativa para retorno do número de nós dessa árvore seria pegar o número de folhas e subtrair por 1.
     */
    int getTreeSize();

    // Retorna a altura da árvore
    int getHeight();

    // Retorna o número de folhas da árvore
    int getLeavesNumber();
};

#endif
