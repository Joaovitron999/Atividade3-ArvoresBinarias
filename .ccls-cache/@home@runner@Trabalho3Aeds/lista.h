#ifndef LISTA_H
#define LISTA_H

using namespace std;

// Estrutura da Lista
typedef struct {
	int tam;              // Variável para medir a quantidade de elementos
	struct no_ * inicio; // Ponteiro para o primeiro nó da lista encadeada
        struct no_ * fim;   // Ponteiro para o ultimo nó da lista encadeada
} tLista;

typedef struct tree{
    struct no_ * info;                 // Ponteiro para apontar para as informações dos veículos
    struct tree *esquerdo, *direito; // Ponteiro para o próximo elemento a esquerda/direita
    int altura;                     // Variável para medir a altura da árvore
} Tree;

// Estrutura para guardar as informações dos veículos
typedef struct no_ {
        string modelo, marca, tipo, combustivel, cambio, direcao, cor, placa; 
        string ano, km, portas; 
        string potencia;
	struct no_ * prox;  // Ponteiro do próximo nó da lista encadeada
} no;

bool arvoreVazia(Tree * raiz);
void insereBin(Tree** raiz, no * novo);
Tree * balancear(Tree * raiz);
Tree * rotacao_direita(Tree * raiz);
Tree * dupla_esquerda(Tree * raiz);
Tree * rotacao_esquerda(Tree * raiz);
Tree * dupla_direita(Tree * raiz);
Tree * inserir_AVL(Tree** raiz, no * novo);
Tree * busca (tLista * lista1, string parametro1, string parametro2, int opcao);
bool procura (string busca, no * pont);
void preOrdem(Tree * raiz);
void exibe(Tree * raiz);
Tree * libera_arvore(Tree * raiz);
int maior_altura(int a, int b);
int altura_no(Tree * tmp);
int fator_balanceamento(Tree * tmp);

void relatorio(tLista * lista1);
bool busca_lista(tLista * lista1, no * novo);
bool incluir (no * novo, tLista * lista1);
tLista * encerra_lista(tLista * lista1);
tLista* inicia_lista();
no * remover_lista(string busca1, tLista * lista1);

int alturaBin(Tree * raiz);


#endif // lista.h

