/*
 * Classe da estrutura de dados fila (Queue)
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include "../TreeSort/Node.h"

#ifndef QUEUE_H
#define QUEUE_H

// Nó utilizado para o funcionamento da fila
struct QueueNode {
  Node *key; // Chave do nó
  QueueNode *next; // Referência para o próximo nó

  // Construtor para inicialização com key e sem obrigatoriedade de ter o próximo nó
  QueueNode(Node *key, QueueNode *next = nullptr) {
    this->key = key;
    this->next = next;
  }
};

class Queue {
  private:

    QueueNode *head; // Nó cabeça como referência ao primeiro elemento da fila
    QueueNode *tail; // Nó cauda como referência ao último elemento da fila

  public:

    Queue() {
      head = tail = nullptr; // Inicialização dos nó cabeça e cauda com nullptr
    }

    ~Queue() {
      // Percorre toda fila removendo os nós relacionados (next)
      while (head != nullptr) {
        QueueNode *tmp = head;
        head = head->next;

        delete tmp;
      }

      tail = nullptr;
    }

    // Retorna se a fila está vazia
    bool empty() {
      return head == nullptr;
    }

    // Insere um elemento no final da fila
    void push(Node *key) {
      QueueNode *tmp = new QueueNode(key);

      // Se a fila estiver vazia, insere o elemento como head e tail,
      // caso contrário, será referenciado como o próximo nó, indo para o final da fila
      if (head == nullptr) {
        head = tail = tmp;
      } else {
        tail->next = tmp;
        tail = tmp;
      }
    }

    // Remove o primeiro elemento da fila, passando o próximo elemento para a primeira posição
    void pop() {
      QueueNode *tmp = head;
      head = head->next;

      if (head == nullptr)
        tail = nullptr;

      delete tmp;
    }

    // Retorna o elemento que está no inicio da fila
    Node *front() {
      return head->key;
    }

    // Retorna o elemento que está no final da fila
    Node *back() {
      return tail->key;
    }

    // Retorna o tamanho da fila, a partir da contagem de quantas iterações são feitas até chegar ao final da fila
    int size() {
      int count = 0;
      QueueNode *tmp = head;

      while (tmp != nullptr) {
        tmp = tmp->next;

        count++;
      }

      return count;
    }
};

#endif
