/*
 * Matriz Esparsa com linhas e colunas representadas
 * por uma lista circular com nó cabeça.
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include <iostream>
#include <cassert>

#ifndef MATRIZ_H
#define MATRIZ_H

using namespace std;

// Nó para o funcionamento da estrutura de dados
struct Node {
  Node *direita;
  Node *abaixo;
  int linha;
  int coluna;
  double valor;

  // Construtor para inicialização sem parâmetros
  Node() {}

  // Construtor para inicialização sem valor com nós direita e abaixo diferentes
  Node(const int& l, const int& c, const int& v) {
    linha = l;
    coluna = c;
    valor = v;
  }

  // Construtor para inicialização sem valor com nós direita e abaixo diferentes
  Node(const int& l, const int& c, Node *d, Node *a) {
    linha = l;
    coluna = c;
    direita = d;
    abaixo = a;
  }

  // Construtor para inicialização sem valor
  Node(const int& l, const int& c, Node *prox) {
    linha = l;
    coluna = c;
    direita = prox;
    abaixo = prox;
  }
};

class Matriz {
  private:
    Node *head; // Nó que representa o nó-cabeça principal
    int linhas, // Quantidade de linha e colunas, respectivamente
        colunas;

  public:
    // Construtor que inicializa a matriz vazia com capacidade para m linhas e n colunas.
    Matriz(int m, int n);

    // Destrutor.
    ~Matriz();

    // Insere um valor na célula (i, j) da matriz, onde i é a linha e j é a coluna.
    void insert(int i, int j, double value);

    // Devolve o valor na célula (i, j) da matriz, onde i é a linha e j é a coluna.
    double getValue(int i, int j);

    // Imprime a matriz, inclusive com os elementos iguais a zero.
    void print();

    // Retorna o número de linhas da matriz.
    int getLinhas();

    // Retorna o número de colunas da matriz.
    int getColunas();
};

#endif
