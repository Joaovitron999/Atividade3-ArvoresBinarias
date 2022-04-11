#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

using namespace std;

/*Estrutura para guardar as informações dos veículos*/
typedef struct no_ {
        string modelo, marca, tipo, combustivel ,cambio, direcao, cor, placa; 
        string ano, km, portas; 
        string potenciaMotor;
	struct no_ * prox;  // ponteiro para o próximo nó da lista encadeada
} no;

/*Estrutura de cabeçalho da Lista*/
typedef struct {
	int tam;              //Variável para medir a quantidade de elementos
	struct no_ * inicio; // Ponteiro para o primeiro nó da lista encadeada
        struct no_ * fim;   //Ponteiro para o ultimo nó da lista encadeada
} tLista;

typedef struct tree{
    struct no_ * info;                 //Ponteiro para apontar para as informações dos veículos
    struct tree *esquerdo, *direito; //Ponteiro para o próximo elemento a esquerda/direita
    int altura;                     //Variável para medir a altura da árvore
} Tree;

bool arvore_vazia(Tree * raiz);
void inserir_binario(Tree** raiz, no * novo);
int maior_altura(int a, int b);
int altura_no(Tree * tmp);
int fator_balanceamento(Tree * tmp);
Tree * rotacao_esquerda(Tree * raiz);
Tree * rotacao_direita(Tree * raiz);
Tree * dupla_esquerda(Tree * raiz);
Tree * dupla_direita(Tree * raiz);
Tree * balancear(Tree * raiz);
Tree *  inserir_AVL(Tree** raiz, no * novo);
Tree * busca (tLista * lista1, string elemento1, string elemento2, int opcao);
bool procura (string busca, no * pont);
void preOrdem(Tree * raiz);
void imprime_arvore(Tree * raiz);
Tree * libera_arvore(Tree * raiz);

void relatorio(tLista * lista1);
bool busca_lista(tLista * lista1, no * novo);
bool incluir (no * novo, tLista * lista1);
tLista * encerra_lista(tLista * lista1);
tLista* inicia_lista();
no * remover_lista(string busca1, tLista * lista1);

int altura_binaria(Tree * raiz);


#endif /* LISTA_H */

