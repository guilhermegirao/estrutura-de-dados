/*
 * Classe referente ao nó da árvore (TreeSort)
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#ifndef NODETREESORT_H
#define NODETREESORT_H

// Nó utilizado para o funcionamento da árvore e como tipagem da key da Queue
struct Node {
  int key; // Chave do nó
  Node *left; // Nó-filho esquerda
  Node *right; // Nó-filho direita

  // Construtor para inicialização com key e sem obrigatoriedade de ter os nós esquerda e/ou direita
  Node(int key, Node *left = nullptr, Node *right = nullptr) {
    this->key = key;
    this->left = left;
    this->right = right;
  }
};

#endif
