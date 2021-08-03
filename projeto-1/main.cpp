#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Matriz/Matriz.h"
#include "Matriz/Utilitarios.h"

using namespace std;

int main() {
  Utilitarios utils; // Classe utilizada para servir as funções extra de soma, multiplica e lerMatrizDeArquivo

  vector<Matriz*> matrizes; // Vector utilizado para salvar as matrizes

  // Main Interativa
  while (true) {
    string cmd;
    getline(cin, cmd);

    std::stringstream ss { cmd };
    vector <string> tokens;
    string buffer;

    while (ss >> buffer)
      tokens.push_back(buffer);

    if (tokens[0] == "exit") { // Encerra a execução do projeto
      for (int i = 0; i < (int) matrizes.size(); i++)
        delete matrizes[i];

      matrizes.clear();

      cout << "encerrando..." << endl;
      break;
    } else if (tokens[0] == "create") { // Cria a Matriz e a armazena em um vector de Matrizes
      int i = std::stoi(tokens[1]);
			int j = std::stoi(tokens[2]);

      Matriz* m = new Matriz(i, j);
      matrizes.push_back(m);

      cout << "matriz " << matrizes.size() - 1 << " criada com sucesso" << endl;
    } else if (tokens[0] == "soma") { // Realiza a Soma de duas matrizes, armazenando uma nova matriz
      int m = std::stoi(tokens[1]);
      int n = std::stoi(tokens[2]);

      Matriz *soma = utils.soma(matrizes[m], matrizes[n]);
      matrizes.push_back(soma);

      cout << "matriz soma " << matrizes.size() - 1 << " criada:" << endl;
      soma->print();
    } else if (tokens[0] == "multiplica") { // Realiza a Multiplicação de duas matrizes, armazenando uma nova matriz
      int m = std::stoi(tokens[1]);
      int n = std::stoi(tokens[2]);

      Matriz *multiplica = utils.multiplica(matrizes[m], matrizes[n]);
      matrizes.push_back(multiplica);

      cout << "matriz multiplica " << matrizes.size() - 1 << " criada:" << endl;
      multiplica->print();
    } else if (tokens[0] == "insert") { // Insere um valor na matriz selecionada em uma célula (i, j) especificada
      int m = std::stoi(tokens[1]);
			int i = std::stoi(tokens[2]);
			int j = std::stoi(tokens[3]);
			int v = std::stoi(tokens[4]);

      matrizes[m]->insert(i, j, v);

      cout << "valor " << v << " inserido na linha " << i << " e coluna " << j << " da matriz " << m << endl;
    } else if (tokens[0] == "getValue") { // Pega o valor na matriz selecionada de uma célula (i, j) especificada
      int m = std::stoi(tokens[1]);
			int i = std::stoi(tokens[2]);
			int j = std::stoi(tokens[3]);

      double v = matrizes[m]->getValue(i, j);

      cout << "valor " << v << " encontrado na linha " << i << " e coluna " << j << " da matriz " << m << endl;
    } else if (tokens[0] == "print") { // Printa a matriz especificada
      int m = std::stoi(tokens[1]);

      cout << "matriz " << m << ":" << endl;
      matrizes[m]->print();
    } else if (tokens[0] == "lerMatrizDeArquivo") { // Lê um arquivo de estrutura de matriz (consultar Arquivos/arquivo1.txt),
                                                    // e armazena uma nova matriz com os dados do arquivo
      string f = tokens[1];

      Matriz *m = utils.lerMatrizDeArquivo(f);
      matrizes.push_back(m);

      cout << "matriz de arquivo " << matrizes.size() - 1 << " criada:" << endl;
      m->print();
    } else {
      cout << "comando inexistente" << endl;
    }
  }

  return 0;
}
