/*
 * Matriz Esparsa com linhas e colunas representadas
 * por uma lista circular com nó cabeça.
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include "Matriz.h"

Matriz::Matriz(int m, int n) {
  assert(m > 0 && n > 0); // Checa se o número de linhas e de colunas é maior que 0

  // Insere o número de linhas e colunas
  linhas = m;
  colunas = n;

  // Inicia o nó-cabeça principal
  head = new Node(-1, -1, nullptr);
  head->abaixo = head;
  head->direita = head;

  // Insere os nó-cabeça relacionado às linhas
  for (int i = 0; i <= (linhas - 1); i++) {
    Node *tmp = new Node(); // Nó auxiliar

    // Se for a primeira linha, insere no nó-cabeça principal abaixo um nó-cabeça
    if (i == 0) {
      tmp->linha = -1;
      tmp->abaixo = head;
      tmp->direita = tmp;

      head->abaixo = tmp;
    } else {
      Node *tmp2 = head; // Nó auxiliar indicando a cabeça principal

      // Percorre a lista de linhas até encontrar o último nó
      while (tmp2->abaixo != head) tmp2 = tmp2->abaixo;

      tmp->linha = -1;
      tmp->abaixo = head;
      tmp->direita = tmp;

      tmp2->abaixo = tmp;
    }
  }

  // Insere os nó-cabeça relacionado às colunas
  for (int i = 0; i <= (colunas - 1); i++) {
    Node *tmp = new Node(); // Nó auxiliar

    // Se for a primeira coluna, insere no nó-cabeça principal à direita um nó-cabeça
    if (i == 0) {
      tmp->coluna = -1;
      tmp->abaixo = tmp;
      tmp->direita = head;

      head->direita = tmp;
    } else {
      Node *tmp2 = head; // Nó auxiliar indicando a cabeça principal

      // Percorre a lista de colunas até encontrar o último nó
      while (tmp2->direita != head) tmp2 = tmp2->direita;

      tmp->coluna = -1;
      tmp->abaixo = tmp;
      tmp->direita = head;

      tmp2->direita = tmp;
    }
  }
}

Matriz::~Matriz() {
  // Seleciona o primeiro nó-cabeça das colunas a partir do nó principal
  Node *headColumnTmp = head->direita;

  // Percorre os nós-cabeça das colunas até o último e os limpa da memória
  while (headColumnTmp != head){
    Node *tmp = headColumnTmp; // Nó auxiliar
    headColumnTmp = headColumnTmp->direita;

    delete tmp; // Limpa o nó da coluna indicada
  }

  // Seleciona o primeiro nó-cabeça das linhas a partir do nó principal
  Node *headRowTmp = head->abaixo;

  // Percorre os nós-cabeça das linhas até o último e os limpa da memória
  while (headRowTmp != head){
    Node *tmp = headRowTmp; // Nó auxiliar
    headRowTmp = headRowTmp->abaixo;

    delete tmp; // Limpa o nó da linha indicada
  }

  delete head; // Limpa o nó-cabeça principal
}

void Matriz::insert(int i, int j, double value) {
  assert((i > 0 && i <= linhas) && (j > 0 && j <= colunas)); // Checa se (i, j) está entre 1 e o número máximo de linhas e colunas

  // Faz a inserção do valor na Matriz se for diferente de 0, dado que é uma matriz esparsa
  if (value != 0) {
    // Nó auxiliar para o nó-cabeça principal (que será utilizado para referenciar o nó-cabeça da coluna)
    Node *headColumnTmp = head;

    // Nó auxiliar para o nó-cabeça principal (que será utilizado para referenciar o nó-cabeça da linha)
    Node *headRowTmp = head;

    // Percorre o nó-cabeça de coluna até a coluna indicada por parâmetro - 1 (pois já está na primeira)
    for (int c = 0; c <= (j - 1); c++) headColumnTmp = headColumnTmp->direita;

    Node *temp = headColumnTmp; // Nó auxiliar

    // Percorre pelas linhas até a linha indicada onde a coluna não for nó-cabeça para ordenar a referência das linhas
    while (temp->abaixo->linha < i) {
      if (temp->abaixo->coluna != -1) {
        temp = temp->abaixo;
      } else {
        break;
      }
    }

    // Percorre o nó-cabeça de linha até a linha indicada por parâmetro - 1 (pois já está na primeira)
    for (int c = 0; c <= (i - 1); c++) headRowTmp = headRowTmp->abaixo;

    Node *temp2 = headRowTmp; // Nó auxiliar

    // Percorre pelas colunas até a coluna indicada onde a linha não for nó-cabeça para ordenar a referência das colunas
    while (temp2->direita->coluna < j) {
      if (temp2->direita->linha != -1) {
        temp2 = temp2->direita;
      } else {
        break;
      }
    }

    Node *tmp = new Node(i, j, value); // Novo nó que será inserido

    // Passagem das referências para o novo nó a partir dos nós previamente ordenados
    tmp->abaixo = temp->abaixo;
    temp->abaixo = tmp;
    tmp->direita = temp2->direita;
    temp2->direita = tmp;
  }
}

double Matriz::getValue(int i, int j) {
  assert((i > 0 && i <= linhas) && (j > 0 && j <= colunas)); // Checa se (i, j) está entre 1 e o número máximo de linhas e colunas

  Node *firstTmp = head->abaixo; // Nó auxiliar para o primeiro nó de linha
  Node *tmp = new Node(); // Nó auxiliar

  // Percorre as linhas e colunas para retornar o valor de (i, j), caso não encontre os nós (i, j), será retornado 0, dado que é uma matriz esparsa
  for (int l = 1; l <= i; l++) {
    tmp = firstTmp->direita;

    for (int c = 1; c <= j; c++) {
      // Checa se existe um nó para a linha e coluna indicadas, caso sim, checa se a linha e colunas são iguais a passadas por parâmetro e retorna o valor
      if (tmp->linha == l && tmp->coluna == c) {
        if (tmp->linha == i && tmp->coluna == j)
          return tmp->valor;

        tmp = tmp->direita;
      }
    }

    firstTmp = firstTmp->abaixo;
  }

  return 0.0;
}

void Matriz::print() {
  assert(linhas > 0 && colunas > 0);

  Node *firstTmp = head->abaixo; // Nó auxiliar para o primeiro nó de linha
  Node *tmp = new Node(); // Nó auxiliar

  // Percorre as linhas e colunas imprimir o valor onde o loop percorre, caso não encontre os nós (i, j), será impresso 0, dado que é uma matriz esparsa
  for (int i = 1; i <= linhas; i++) {
    tmp = firstTmp->direita;

    for (int j = 1; j <= colunas; j++) {
      // Checa se existe um nó para a linha e coluna indicadas, caso sim, imprima o valor, senão, imprima 0;
      if (tmp->linha == i && tmp->coluna == j) {
        cout << tmp->valor;

        tmp = tmp->direita;
      } else {
        cout << "0";
      }

      cout << " ";
    }

    cout << endl;
    firstTmp = firstTmp->abaixo;
  }
}

int Matriz::getLinhas() {
  return linhas; // Retorna o número de linhas da matriz
}

int Matriz::getColunas() {
  return colunas; // Retorna o número de colunas da matriz
}

