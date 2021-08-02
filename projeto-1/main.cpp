#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Matriz/Matriz.h"
#include "Matriz/Utilitarios.h"

using namespace std;

int main() {
  Utilitarios utils; // Classe utilizada para servir as funções extra de soma, multiplica e lerMatrizDeArquivo

  Matriz *m = new Matriz(2, 2);
  m->insert(1, 1, 3);
  m->insert(1, 2, 2);
  m->insert(2, 1, 5);
  m->insert(2, 2, -1);

  m->print();

  Matriz *n = new Matriz(2, 3);
  n->insert(1, 1, 6);
  n->insert(1, 2, 4);
  n->insert(1, 3, -2);
  n->insert(2, 2, 7);
  n->insert(2, 3, 1);

  n->print();

  Matriz *mult = utils.multiplica(m, n);

  mult->print();

  Matriz *A = utils.lerMatrizDeArquivo("arquivo1.txt");
  Matriz *B = utils.lerMatrizDeArquivo("arquivo2.txt");
  B->insert(1, 2, -4);

  A->print();
  cout << "====================" << endl;
  B->print();
  cout << "====================" << endl;

  Matriz *C = utils.soma(A, B);
  C->print();
  cout << "====================" << endl;

  Matriz *D = utils.multiplica(A, B);
  D->print();
  cout << "====================" << endl;

  delete D;
  cout << "hello world!";

  return 0;
}
