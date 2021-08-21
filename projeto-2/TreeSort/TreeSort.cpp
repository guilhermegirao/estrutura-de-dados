/*
 * Ordenação de Vetores utilizando Árvore
 *
 * Equipe: Eliton Lima e Guilherme Girão Alves
 */

#include "TreeSort.h"

TreeSort::TreeSort(int _vectorSize, int *_vector) {
  assert(_vectorSize > 0); // Verifica se o tamanho do vetor é maior que zero

  vectorSize = _vectorSize; // Guarda o tamanho do vetor
  vector = _vector; // Guarda o vetor antigo
  stateVector = _vector; // Inicia o vetor de estado
  sortedVector = new int[_vectorSize]; // Inicializa o vetor ordenado

  // Encontra o maior valor do vetor e guarda em maxValue somado com 1
  for (int i = 0; i < _vectorSize; i++) {
    if (_vector[i] > maxValue - 1)
      maxValue = _vector[i] + 1;
  }

  // Faz as iterações suficientes (o tamanho do vetor) para todos os menores valores virarem a key do nó-raiz, ou seja,
  // para os todos os menores valores serem ordenados. Outra forma de fazer isso seria fazer um loop de while enquanto
  // root->key != maxValue, contudo, foi observado que será a mesma quantidade de iterações que o tamanho do vetor.
  for (int i = 0; i < _vectorSize; i++) {
    root = buildTree(generateLeaves()); // Constrói a árvore a partir das folhas geradas a partir do vetor de estados
    sortedVector[i] = root->key; // Insere no vetor de ordenação o valor (key) do nó raiz da árvore

    // Procura se o valor do nó raiz existe no vetor de estados, caso sim, o primeira ocorrencia desse valor
    // será substituida pelo maxValue, com a finalidade de que na próxima iteração, o antigo menor valor não existir mais
    // para o próximo menor valor ser ordenado
    int index = getIndexByRootKey();
    if (index > -1) stateVector[index] = maxValue;
  }
}

TreeSort::~TreeSort() {
  root = clear(root); // Limpa todos os nós associados ao nó raíz e o seta como nullptr

  delete vector; // Remove da memória o vetor original
  delete stateVector; // Remove da memória o vetor de estados
  delete sortedVector; // Remove da memória o vetor ordenado
}

Node *TreeSort::clear(Node *node) {
  if (node != nullptr) {
    node->left = clear(node->left); // Remove todos os nós a partir da esquerda do nó passado
    node->right = clear(node->right); // Remove todos os nós a partir da direita do nó passado

    delete node; // Remove o nó da memória
  }

  return nullptr; // Retorna nullptr como caso de parada e para setar o no raíz como nullptr
}

/*
 * Recebe uma fila de folhas, geradas a partir da função generateLeaves().
 * Dessa maneira, constrói-se a árvore de baixo para cima.
 * Pega-se as duas primeiras folhas da fila, compara qual tem o menor valor (key),
 * e cria um novo nó (o qual será pai dessas duas folhas) com a menor key comparada,
 * assim será até sobrar um nó na fila, o qual será o nó raiz, e, consequentemente o menor elemento do vetor.
 */
Node *TreeSort::buildTree(Queue leavesQueue) {
  while (leavesQueue.size() > 1) {
    Node *leaf1 = leavesQueue.front(); // Primeira folha
    leavesQueue.pop();

    Node *leaf2 = leavesQueue.front(); // Primeira folha após a remoção da folha anterior
    leavesQueue.pop();

    // Criação de um nó pai auxiliar com o menor valor entre os filhos
    Node *tmpRoot = new Node(min(leaf1->key, leaf2->key), leaf1, leaf2);
     // Inserção do nó pai na fila para ser comparado e criar um novo nó pai ou nó raiz (caso seja o último nó restante da fila)
    leavesQueue.push(tmpRoot);
  }

  return leavesQueue.front(); // O nó restante da fila será o nó raiz da árvore
}

Queue TreeSort::generateLeaves() {
  Queue tmpNodeQueue; // Fila auxiliar

  // Faz um loop pelo número de folhas da árvore
  for (int i = 0; i < getLeavesNumber(); i++) {
    // Caso a posição seja menor que o tamanho do vetor, então preencha a key do Node como o maxValue,
    // senão, a key será o valor na posição i do vetor
    int key = i < vectorSize ? stateVector[i] : maxValue;

    Node *tmp = new Node(key); // Nó auxiliar
    tmpNodeQueue.push(tmp); // Insere na fila
  }

  return tmpNodeQueue;
}

int TreeSort::getIndexByRootKey() {
  if (root != nullptr) { // A árvore deve ter sido criada previamente
    // Procura pelo vetor de estado e retorna a posição,
    // caso a key do nó raiz seja igual ao valor na posição rodada
    for (int i = 0; i < vectorSize; i++) {
      if (stateVector[i] == root->key)
        return i;
    }
  }

  return -1;
}

bool TreeSort::empty() {
  return root == nullptr; // Árvore é vazia quando o nó raíz é null
}

int *TreeSort::getSortedVector() {
  return sortedVector; // Retorna o vetor ordenado
}

int TreeSort::getVectorSize() {
  return vectorSize; // Retorna o tamanho do vetor
}

int TreeSort::getHeight() {
  // Calcula a altura da árvore com base na fórmula de altura no documento de instruções: (teto de log2 n) + 1.
  return ceil(log2(vectorSize)) + 1;
}

int TreeSort::getLeavesNumber() {
  // Calcula o número de folhas da árvore com base na fórmula 2^(h - 1), onde h = altura da árvore
  return pow(2, getHeight() - 1);
}

void TreeSort::print() {
  _print(root); // Chamada da função recursiva a partir do nó raiz
}

void TreeSort::_print(Node *node) {
  // Caso o nó seja null não será mostrado nada
  if (node != nullptr) {
    cout << node->key << " ";

    _print(node->left); // Printa a sequencia de nós a partir da esquerda do nó passado
    _print(node->right); // Printa a sequencia de nós a partir da direita do nó passado
  }
}

int TreeSort::getTreeSize() {
  return _getTreeSize(root); // Chamada da função recursiva a partir do nó raiz
}

int TreeSort::_getTreeSize(Node *node) {
  if (node == nullptr) return 0; // Caso de parada da recursão
  return _getTreeSize(node->left) + _getTreeSize(node->right) + 1; // Some 1 para cada nó filho da esquerda e direita
}
