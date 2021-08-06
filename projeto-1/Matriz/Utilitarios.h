/*
 * Classe de utilitários manipuladores da estrutura
 * Matriz criada, com os métodos de somar, multiplicar
 * e ler a matriz a partir de um arquivo.
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include <iostream>
#include <fstream>

#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "Matriz.h"

using namespace std;

class Utilitarios {
  public:
    /*
     * Essa função recebe as matrizes A e B como parâmetro, e devolve
     * uma matriz C, que é a soma de A com B.
     */
    Matriz *soma(Matriz *A, Matriz *B);

    /*
     * Essa função recebe as matrizes A e B como parâmetro, e devolve
     * uma matriz C, que é o produto de A com B.
     */
    Matriz *multiplica(Matriz *A, Matriz *B);

    /*
     * Essa função lê, de um arquivo de entrada, os elementos diferentes de zero
     * de uma matriz e monta a estrutura especificada anteriormente, devolvendo um
     * ponteiro para uma Matriz alocada dinamicamente.
     */
    Matriz *lerMatrizDeArquivo(string nome_do_arquivo);
};

Matriz *Utilitarios::soma(Matriz *A, Matriz *B) {
  // Verifica se o número de linhas e colunas da Matriz A é igual ao número de linhas e colunas da Matriz B
  assert(A->getLinhas() == B->getLinhas() && A->getColunas() == B->getColunas());

  int linhas = A->getLinhas();
  int colunas = A->getColunas();

  Matriz *m = new Matriz(linhas, colunas); // Nova matriz que armazena a soma de tamanho de linhas e colunas iguais aos das matrizes

  // Percorre as linhas e as colunas das matrizes
  for (int i = 1; i <= linhas; i++) {
    for (int j = 1; j <= colunas; j++) {
      int valA = A->getValue(i, j); // Pega o valor da Matriz A em (i, j)
      int valB = B->getValue(i, j); // Pega o valor da Matriz B em (i, j)
      int soma = valA + valB;  // Faz a soma dos valores das matrizes em (i, j)

      m->insert(i, j, soma); // Insere na nova matriz, o valor da soma em (i, j)
    }
  }

  return m;
}

Matriz *Utilitarios::multiplica(Matriz *A, Matriz *B) {
  // Verifica se o número de colunas da Matriz A é igual ao número de linhas da Matriz B
  assert(A->getColunas() == B->getLinhas());

  int linhas = A->getLinhas();
  int colunas = B->getColunas();

  // Nova matriz que armazena a multiplicação com tamanho de linhas da Matriz A e colunas da Matriz B
  Matriz *m = new Matriz(linhas, colunas);

  // Percorre as linhas da Matriz A e as colunas da Matriz B
  for (int i = 1; i <= linhas; i++) {
    for (int j = 1; j <= colunas; j++) {
      int mult = 0;

      // Percorre as linhas da Matriz A (somatório das multiplicações)
      for (int k = 1; k <= linhas; k++) {
        int valA = A->getValue(i, k); // Pega o valor da Matriz A em (i, k)
        int valB = B->getValue(k, j); // Pega o valor da Matriz B em (k, j)

        mult += valA * valB;
      }

      m->insert(i, j, mult); // Insere na nova matriz, o valor da multiplicação em (i, j)
    }
  }

  return m;
}

Matriz *Utilitarios::lerMatrizDeArquivo(string nome_do_arquivo) {
  // Matriz que será retornada, caso o arquivo existir, senão, retornar um nullptr para retorno de erro
  Matriz *m = nullptr;

  ifstream file(nome_do_arquivo); // Lê o arquivo passado por parâmetro
  int fileLine = 0; // Linha que está sendo lida do arquivo atualmente

  // Testa se o arquivo foi lido com sucesso
  if (file.is_open()) {
    string line; // Variável auxiliar para retornar a linha atual

    // Auxiliares respectivos: Número de linhas e colunas (recebidos na linha 0 do arquivo), linha, coluna e valor (das próximas linhas)
    int linhas,
        colunas,
        linha,
        coluna,
        valor;

    // Percorre o arquivo linha-por-linha até o fim
    while (getline(file, line)) {
      stringstream ss;
      ss << line; // Transforma a stream da linha em uma "string"

      // Se a linha for a primeira, então, inicie a matriz com o número de linhas e colunas passadas
      // Senão, pega a linha, coluna e valor passados e insere o valor na matriz em (linha, coluna)
      if (!fileLine) {
        ss >> linhas >> colunas;

        m = new Matriz(linhas, colunas);
      } else {
        ss >> linha >> coluna >> valor;

        // A própria função insert já tem a validação do valor ser diferente de 0
        m->insert(linha, coluna, valor);
      }

      fileLine++; // Incrementa a linha que está sendo lida do arquivo atualmente
    }
  }

  file.close(); // Fecha o arquivo

  assert(m != nullptr);
  return m;
}

#endif
