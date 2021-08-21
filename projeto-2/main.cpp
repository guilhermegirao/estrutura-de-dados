#include <iostream>
#include <sstream>
#include <fstream>

#include "TreeSort/TreeSort.h"

using namespace std;

int main() {
  ifstream input("Arquivos/input.txt"); // Permite acesso à leitura do arquivo de entrada (Arquivos/input.txt)
  ofstream output("Arquivos/output.txt"); // Permite acesso à escrita no arquivo de saída (Arquivos/output.txt)

  int fileLine = 1; // Auxiliar para contagem de linhas do arquivo de entrada

  if (input.is_open()) {
    string line; // Variável auxiliar para retornar a linha atual
    int vectorSize; // Guarda o tamanho do vetor, indicado no arquivo de entrada

    // Percorre o arquivo linha-por-linha até o fim
    while (getline(input, line)) {
      stringstream ss;
      ss << line;  // Transforma a stream da linha em uma "string"

      /*
       * Se a linha atual do arquivo de entrada for ímpar, então será o tamanho do vetor
       * ou representará parada (caso n = 0).
       * Caso a linha seja par, então salvará os valores desta linha no vetor,
       * instancia a classe de ordenação TreeSort para esse vetor gerado, afim de ordená-lo e,
       * salva o vetor ordenado, vindo da classe de ordenação pelo método getSortedVector(),
       * no arquivo de saída.
       */
      if (fileLine % 2 != 0) {
        ss >> vectorSize;

        if (vectorSize == 0) break;
      } else {
        int vector[vectorSize];

        for (int i = 0; i < vectorSize; i++) {
          ss >> vector[i];
        }

        // Instancia da classe de ordenação TreeSort. A ordenação do vetor é feita a partir do momento em que a classe é instanciada
        // (ou seja, no próprio construtor)
        TreeSort *sort = new TreeSort(vectorSize, vector);

        for (int i = 0; i < vectorSize; i++) {
          output << sort->getSortedVector()[i] << " ";
        }

        output << endl;
        cout << "Vetor ordenado com sucesso!" << endl;
      }

      fileLine++;
    }
  }

  input.close();
  output.close();

  return 0;
}
