#include <cstdlib>
#include <iostream>
#include "lista.h"

using namespace std;

// Calcula o fator de balanceamento!!
int fator_balanceamento(Tree * tmp){
    if(tmp){
        return(altura_no(tmp->esquerdo) - altura_no(tmp->direito));
    }else{
        return 0;
    }
}

// Função que insere uma árvore binária
void insereBin(Tree** raiz, no * novo){
    if (*raiz == NULL){
        *raiz = new(Tree); // Aloca memória para a estrutura
        (*raiz)->esquerdo = NULL; // Subárvore à esquerda é nulo
        (*raiz)->direito = NULL; // Subárvore à direita é nulo
        (*raiz)->info = novo; // Armazena a informação
    }else{
        no * aux = (*raiz)->info;
        // número vai pra esquerda se for menor
        if(novo->placa < aux->placa){
          // Percorre a subarvore pela esquerda
          insereBin(&(*raiz)->esquerdo, novo);
        }
        // Compara se maior, se for, então vai pra direita 
        if(novo->placa > aux->placa){
          // Percorre a subarvore pela direiota
          insereBin(&(*raiz)->direito, novo);
        }
    }
}


  
// Verificar se a árvore está vazia
bool arvoreVazia(Tree * raiz){
    if(raiz == NULL){ // Caso a raiz seja nula então está vazia 
        return true;
    }else{
        return false;
    }
}

Tree * rotacao_esquerda(Tree * raiz){
    Tree *y, *f;
    y = raiz->direito;
    f = y->esquerdo;
    
    y->esquerdo = raiz;
    raiz->direito = f;
    
    raiz->altura = maior_altura(altura_no(raiz->esquerdo), altura_no(raiz->direito)) +1;
    y->altura = maior_altura(altura_no(y->esquerdo), altura_no(y->direito)) +1;
    
    return y;
}

Tree * rotacao_direita(Tree * raiz){
    Tree *y, *f;
    y = raiz->esquerdo;
    f = y->direito;
    
    y->direito = raiz;
    raiz->esquerdo = f;
    
    raiz->altura = maior_altura(altura_no(raiz->esquerdo), altura_no(raiz->direito)) +1;
    y->altura = maior_altura(altura_no(y->esquerdo), altura_no(y->direito)) +1;

    return y;
}

Tree * dupla_esquerda(Tree * raiz){
    raiz->direito = rotacao_direita(raiz->direito);
    return rotacao_esquerda(raiz);
}

Tree * dupla_direita(Tree * raiz){
    raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
    return rotacao_direita(raiz);
}

// Feito para realizar o balanceamento da árvore após a inserção de um nó
Tree * balancear(Tree * raiz){
    int num = fator_balanceamento(raiz);
    
    
    if(num < -1 && fator_balanceamento(raiz->direito) <= 0){
        // Rotação esquerda
        raiz = rotacao_esquerda(raiz);        
    }else if(num > 1 && fator_balanceamento(raiz->esquerdo) >= 0){ 
        // Rotação direita
        raiz = rotacao_direita(raiz);
    }else if(num > 1 && fator_balanceamento(raiz->esquerdo) < 0 ){
        // Rotação dupla direita
        raiz = dupla_direita(raiz);
    }else if(num < -1 && fator_balanceamento(raiz->direito) > 0){
        // Rotação dupla esquerda
        raiz = dupla_esquerda(raiz);
    }
    
    return raiz;
}

// Insere um nó na árvore AVL
Tree *  inserir_AVL(Tree** raiz, no * novo){
    if((*raiz) == NULL){ // Árvore vazia
        *raiz = new(Tree);
        (*raiz)->info = novo;
        (*raiz)->esquerdo = NULL;
        (*raiz)->direito = NULL;
        (*raiz)->altura = 0;
        return (*raiz);
    }
    else{ // Inserção à esquerda ou direita
        no * aux = (*raiz)->info;
        if( novo->placa < aux->placa){
            (*raiz)->esquerdo = inserir_AVL(&(*raiz)->esquerdo, novo);
        }
        else if(novo->placa > aux->placa){
            (*raiz)->direito = inserir_AVL(&(*raiz)->direito, novo);
        }
        else{
            cout << " [   Falha na inserção   ] " << endl;
            return (*raiz);
        }
    }
    
    (*raiz)->altura = 1 + maior_altura(altura_no((*raiz)->esquerdo), altura_no((*raiz)->direito));
    
    (*raiz) = balancear(*raiz);
    
    return (*raiz);
}

 // Busca de veículos*/
 // lista1 -> lista principal
 // parametro1 -> primeiro parâmetro ou elemento de busca
 // parametro2 -> segundo parâmetro ou elemento de busca
 // opcao -> para saber se é uma PILHA ou FILA 
 
Tree * busca (tLista * lista1, string parametro1, string parametro2, int opcao){
    no * pont = lista1->inicio;
    int tamanho = lista1->tam;
    
    // Se for Árvore Binária escolhe
    if (opcao == 1){
        Tree * binaria1 = NULL;
        while(tamanho > 0){
            if(procura(parametro1, pont)){    
                if(procura(parametro2, pont)){
                    // Se o ponteiro possuir os dois elementos 
                    // descritos nas strings o elemento é
                    // inserido na árvore
                    insereBin(&binaria1, pont);
                }
            }
            pont = pont->prox;
            tamanho--;
        }
        return binaria1;
        
    }// Se for ÁRVORE AVL
    else{
        Tree * avl = NULL;
        while(tamanho > 0){
            if(procura(parametro1, pont)){    
                if(procura(parametro2, pont)){
                    // Se o ponteiro possuir os dois elementos 
                    // descritos nas strings o elemento é 
                    // inserido na árvore
                    inserir_AVL(&avl, pont);
                }
            }
            pont = pont->prox;
            tamanho--;
        }
        return avl;
    }
}

// Compara um elemento com as informações do veículo para ver se são iguais
bool procura (string busca, no * pont){
  // Tratamento de strings Minúsculas para Maiúsculas
  for(int i = 0; i < busca.length(); i++){
      busca[i] = toupper(busca[i]);
  }

  // Dados veículo, comparando suas strings e deixando tudo em maiúsculo
  for(int i = 0; i < pont->marca.length(); i++){
      pont->marca[i] = toupper(busca[i]);
  }
  for(int i = 0; i < pont->tipo.length(); i++){
        pont->tipo[i] = toupper(pont->tipo[i]);
  }
  for(int i = 0; i < pont->ano.length(); i++){
        pont->ano[i] = toupper(pont->ano[i]);
  }
  for(int i = 0; i < pont->km.length(); i++){
        pont->km[i] = toupper(pont->km[i]);
  }
  for(int i = 0; i < pont->potencia.length(); i++){
        pont->potencia[i] = toupper(pont->potencia[i]);
  }
  for(int i = 0; i < pont->combustivel.length(); i++){
        pont->combustivel[i] = toupper(pont->combustivel[i]);
  }
  for(int i = 0; i < pont->cambio.length(); i++){
        pont->cambio[i] = toupper(pont->cambio[i]);
  }
  for(int i = 0; i < pont->direcao.length(); i++){
        pont->direcao[i] = toupper(pont->direcao[i]);
  }
  for(int i = 0; i < pont->cor.length(); i++){
        pont->cor[i] = toupper(pont->cor[i]);
  }
  for(int i = 0; i < pont->portas.length(); i++){
        pont->portas[i] = toupper(pont->portas[i]);
  }
  for(int i = 0; i < pont->modelo.length(); i++){
        pont->modelo[i] = toupper(pont->modelo[i]);
  }
  for(int i = 0; i < pont->placa.length(); i++){
        pont->placa[i] = toupper(pont->placa[i]);
  }


    if(busca == pont->marca){
        return true;
    }
    if(busca == pont->tipo){
        return true;                    
    }
    if(busca == pont->ano){
        return true;                
    }
    if(busca == pont->km){
        return true;
    }
    if(busca == pont->potencia){
        return true;                
    }
    if(busca == pont->combustivel){
        return true;                
    }
    if(busca == pont->cambio){
        return true;                
    }
    if(busca == pont->direcao){
        return true;                
    }
    if(busca == pont->cor){
        return true;                
    }
    if(busca == pont->portas){
        return true;                
    }
    if(busca == pont->placa){
        return true;                
    }
    if(busca == pont->modelo){
        return true;                
    }
    return false;   
}

// Imprime a árvore em pré Ordem
void preOrdem(Tree * raiz){
    cout << "\t|  Placa...: ""[" << raiz->info->placa<< "]";
    cout << "\t|  Modelo..: ""[" << raiz->info->modelo<< "]" "\t   " << endl;
    if(raiz->esquerdo != NULL){  //Diferente
        preOrdem(raiz->esquerdo);
    }
    if(raiz->direito != NULL){
        preOrdem(raiz->direito);
    }
}

//Imprime a árvore
void exibe(Tree * raiz){
    if(arvoreVazia(raiz)){
        
        cout << endl;
        cout << " \t\t\t [      Veículo não encontrado      ]"<< endl;
        cout << endl;        
    } else {
        raiz->altura = alturaBin(raiz); 
        cout << "\t\t|\t\t    Altura da árvore --> "<< raiz->altura << "       |" << endl;
        cout << endl;
        preOrdem(raiz);
        cout << endl;    
      }
}

//Libera a Árvore
Tree * libera_arvore(Tree * raiz){
    if (!arvoreVazia(raiz)){
        libera_arvore(raiz->esquerdo);
        libera_arvore(raiz->direito);
        free(raiz);
    }
    return NULL;
}

//Imprime o estado atual da lista
void relatorio(tLista * lista1){
	no * ptr = lista1->inicio;
        cout << "  --------------------------------------" << endl;
        cout << "  |       ESTADO ATUAL DA LISTA:       |" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "  |      PLACA      |      MODELO      |" << endl;
        cout << "  --------------------------------------" << endl;
	while(ptr != NULL){
          cout << "  |\t\t"<<"["<<ptr->placa <<"]\t|\t ["<< ptr->modelo << "]" << endl;

        ptr = ptr->prox;
	}
        cout << "  |                                   |"<< endl;
        cout << "  |     Quantidade de Carros  = " << lista1->tam << "    |"<< endl;
        cout << "  |                                   |"<< endl;
        cout << "  -------------------------------------" << endl;
        cout << endl;
}

//Verifica se o elemento já existe na lista
bool busca_lista(tLista * lista1, no * novo){
    no * ant = lista1->inicio;
    no * pont = lista1->inicio;
    while (pont != NULL){
        if (pont->placa == novo->placa){
            return true;
        }
        else{
            ant = pont;
            pont = pont->prox; 
        }
    }
    return false;
}
//Inclui um elemento na Lista
//Parametros: Novo - nó a ser incluso | lista1 - lista para o nó ser inserido
 
bool incluir (no * novo, tLista * lista1){
    no * ant = lista1->inicio;
    no * ptr = lista1->inicio;
    //Caso a lista estiver vazia:
    if (lista1->tam == 0){
        //lista1->lista = new(no);
        lista1->inicio = novo;
        lista1->fim = novo;
        lista1->inicio->prox = NULL;
        lista1->tam++;
        return true;
    }
    //Verifica se o elemento já existe na lista
    if(busca_lista(lista1, novo)){
        return false;
    }
    lista1->tam++;
    
    lista1->fim->prox = novo;
    lista1->fim = novo;

    return true;
}

//Encerra a Lista
tLista * encerra_lista(tLista * lista1) {
    no * ant = lista1->inicio;
    no * pont = lista1->inicio;
    while(ant != NULL){
	pont = ant->prox;
	delete(ant);
	ant = pont;
    }
    delete(lista1);
    return NULL;
}

//Inicia a Lista
tLista* inicia_lista() {
    tLista* tmp = new (tLista);
    tmp->tam = 0;
    tmp->inicio = NULL;
    tmp->fim = NULL;
    return tmp;
}

//Remove um elemento da lista
no * remover_lista(string busca1, tLista * lista1){
    no * ant = lista1->inicio;
    no * pont= lista1->inicio;
    if(lista1->tam == 0){
        cout << "  Não foi possível remover o veículo de placa ("<< busca1 <<") , pois a Lista está vazia." <<endl;
        return NULL;
    }
    // Acha o elemento
    while(pont != NULL){
        if(pont->placa == busca1){
            if(pont->placa == lista1->inicio->placa){
                lista1->inicio = pont->prox;
            }
            if(pont->placa == lista1->fim->placa){
                lista1->fim = ant;
            }
            if(lista1->tam==1){
                lista1->inicio = NULL;
                lista1->fim = NULL;
                ant->prox = NULL;
                ant = NULL;
                pont->prox = NULL;
                lista1->tam--;

                return pont;
            }
            else{
                ant->prox = pont->prox;
                pont->prox = NULL;
                lista1->tam--;
            }         

            return pont;
        }
        ant = pont;
        pont = ant->prox;
    }
    cout << "  Não foi possível remover o veículo de placa ("<< busca1 <<"), tente novamente." << endl;
    return NULL;
    
}

//Calcula a altura da árvore binária
int alturaBin(Tree * raiz){
   if (raiz == NULL) 
      return -1; // altura da árvore vazia
   else {
      int he = alturaBin(raiz->esquerdo);
      int hd = alturaBin(raiz->direito);
      if (he < hd) return hd + 1;
      else return he + 1;
   }
}