/*--------------------------------------------------------------------/
/                 Universidade Federal de Alfenas                    /
/            Gerenciador-de-Busca-de-Carros-Arvores-AEDs2           /
/ Nome: Caio Eduardo Marcondes     // Matrícula: 2020.1.08.035     /
/ Nome: João Vitor Fonseca         // Matrícula: 2020.1.08.003    /   
/ Nome: Pedro Henrique Borges Luiz // Matrícula: 2020.1.08.036   /
/ Data: 2022                                                    /
--------------------------------------------------------------*/

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h> 
#include "lista.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

using namespace std;

tLista * lista1;

int main(int argc, char** argv) {
  setlocale(LC_ALL, "Portuguese");
    // Variável que guarda o valor da resposta do usuário
    int opcao = 0;
    int opcao2 = 0;
  
    // Variável para saber as opções dos primeiros parâmetros de busca dos veículos. Também irá ser usada para saber a placa do veículo que o usuário deseja remover.
    string elemento1, elemento2;
    
     // Variável que confirma se já foi feita uma busca. Se resultar =0 significa que a Arvore está vazia, logo nenhum dado de busca foi armazenado nesses lugares, caso seja = 1 significa que precisamos deletar o conteúdo que está na Arvore
    bool existeArv = false, existeAVL = false;
    
    // Variável que identifica se o arquivo existe
    bool arquivo = false;
    
    // Variável que nomeia o arquivo após ser lido
    string nomearq;
    
    // Variáveis de busca
    Tree * Binaria = NULL;
    Tree *AVL = NULL;

    // Procura o arquivo com o nome correspondente
    nomearq = "BD_veiculos.txt";
    
    // Aqui se obtém as informações do arquivo
    ifstream dados1 (nomearq);
    if (dados1.is_open()){
        // Início da lista
        lista1 = inicia_lista();
      string word;
        for(int i = 0; i < 13; i++){
      dados1 >> word;
        }
        word = "";   
      
        while (!dados1.eof() ){
            no * novo = new no();
            dados1 >> novo->modelo;
            dados1 >> novo->marca;
            dados1 >> novo->tipo;
            dados1 >> novo->ano;
            dados1 >> novo->km;
            dados1 >> novo->potenciaMotor;
            dados1 >> novo->combustivel;
            dados1 >> novo->cambio;
            dados1 >> novo->direcao;
            dados1 >> novo->cor;
            dados1 >> novo->portas;
            dados1 >> novo->placa;  
            novo->prox = NULL;
            incluir (novo, lista1);
            arquivo = 1;
        }
        dados1.close();
    }
    else{
        cout << "Arquivo não disponível."<<endl;
    }
    
    if(arquivo == 1){
        do{
            cout << "  -------------------------------------" << endl;
            cout << "  |           MENU DE OPÇÕES          |" << endl;
            cout << "  -------------------------------------" << endl;
            cout << "  |   Inserir veículo             [1] |" << endl;
            cout << "  |   Remover veículo             [2] |" << endl;
            cout << "  |   Buscar                      [3] |" << endl;
            cout << "  |   Relatório                   [4] |" << endl;
            cout << "  |   RELATÓRIO DAS ÁRVORES       [5] |" << endl;
            cout << "  |   SAIR                        [0] |" << endl;
            cout << "  -------------------------------------" << endl;

            cout << endl;
            cout << " Digite o numero da opção desejada: ";
            cin >> opcao;

            system("clear||cls"); // Limpar a tela (Funciona tanto em linux ou windows

            // Caso o valor digitado não esteja de acordo com as opções, a seguinte mensagem será exibida:
            while ( opcao < 0 || opcao > 5){
                cout << " Valor inválido, digite novamente " << endl;
                cin >> opcao;
            }

            // Se digitar 0 o programa será fechado 
            if ( opcao == 0){
                // Remoção das árvores
                if (existeArv){ // Remove a árvore binária caso exista
                    libera_arvore(Binaria);
                    existeArv = false;
                }
                if (existeAVL){// Remove a árvore AVL caso exista
                    libera_arvore(AVL);
                    existeAVL = false;
                }
                // Remove a lista
                lista1 = encerra_lista(lista1);
            }

            // 1 - Inserir
            if(opcao == 1){
                no * novo = new no();
                cout << endl;
                cout << "\r" " Insira os dados do novo veículo: " << endl;
                cout << endl;
                cout << " Digite o modelo: ";
                cin >> novo->modelo;

                cout << " Digite a marca: ";
                cin >> novo->marca;

                cout << " Digite o tipo: ";
                cin >> novo->tipo;

                cout << " Digite o ano: ";
                cin >> novo->ano;

                cout << " Digite a KM: ";
                cin >> novo->km;

                cout << " Digite a Potência do Motor: ";
                cin >> novo->potenciaMotor;

                cout << " Digite o combustível: ";
                cin >> novo->combustivel;

                cout << " Digite o câmbio: ";
                cin >> novo->cambio;

                cout << " Digite a direção: ";
                cin >> novo->direcao;

                cout << " Digite a cor: ";
                cin >> novo->cor;

                cout << " Digite a quantidade de portas: ";
                cin >> novo->portas;

                cout << " Digite a placa: ";
                cin >> novo->placa;

                novo->prox = NULL;
                if (incluir (novo, lista1)){
                    cout << endl;
                    cout << "  Veículo foi inserido com sucesso! " << endl;
                    cout << endl;
                }
                else{
                    cout << endl;
                    cout << "  [   O veículo já está existe na Lista  ]" << endl;
                    cout << endl;
                }

              system("clear||cls"); //Limpar a tela (Funciona tanto em linux ou windows
            }

            // 2 - Remover 
            if(opcao == 2){
                cout << " Digite a placa do veículo que deseja remover: ";
                cin >> elemento1;
                for(int i = 0; i < elemento1.length(); i++){
                  elemento1[i] = toupper(elemento1[i]);
                }
                no * deletar;
                deletar = remover_lista(elemento1, lista1);
                if(deletar != NULL){
                    cout << endl;
                    cout << "[ O veículo de placa (" << deletar->placa << ") foi removido com sucesso! ]" << endl;
                    cout << endl;
                }
            }

            // 3 - Buscar 
            if(opcao == 3){
                cout << endl;
                cout << "\t[     Qual tipo de árvore usar?     ]" << endl;
                cout << endl;
                cout << "  |          [1] Árvore Binária           |" << endl;
                cout << "  |          [2] Árvore AVL               |" << endl;
                cout << endl;
                cout << " Digite a opção de armazenamento desejada: ";
                cin >> opcao2;
                if (opcao2 > 0 && opcao2 <= 2){
                   
                //Tira a ÁRVORE BINÁRIA para realizar uma nova busca
                if (existeArv){
                    libera_arvore(Binaria);
                    existeArv = false;
                }
                //Tira a ÁRVORE AVL para realizar uma nova busca
                if (existeAVL){
                    libera_arvore(AVL);
                    existeAVL = false;
                }
                // 1 - ÁRVORE BINÁRIA
                if (opcao2 == 1){              
                    cout <<endl;
                    cout << " Exemplo: Se deseja buscar por carros da cor Preto a câmbio Manual digite: 'Preto' no primeiro critério e 'Manual' no segundo critério" << endl;
                    cout <<endl;
                    cout << " Digite o PRIMEIRO critério de busca desejada: ";
                    cin >> elemento1; 
                    cout << endl;
                    cout << " Digite o SEGUNDO critério de busca desejada: ";
                    cin >> elemento2;
                    
                    //Chama a função de busca
                    Binaria = busca (lista1, elemento1, elemento2, opcao);
                    existeArv = true;
                }
                else if(opcao2 == 2) { // 2 - ÁRVORE AVL
                    cout <<endl;
                    cout << " Exemplo: Se deseja buscar por carros da cor Branco a câmbio Automático digite: 'Branco' no primeiro critério e 'Automático' no segundo critério" << endl;
                    cout << " Digite o primeiro critério de busca desejada: ";
                    cin >> elemento1;
                    cout << endl;
                    
                    cout << " Digite o segundo critério de busca desejada: ";
                    cin >> elemento2;
                    
                    //Chama a função de busca
                    AVL = busca (lista1, elemento1, elemento2, opcao);
                    existeAVL = true;
                }
                cout << endl;
                cout << "  \t[\t\t  Busca realizada!\t\t]" << endl;
                cout << endl;
                }
            }
            // 4 - Relatório
            if(opcao == 4){
                cout << endl;
                relatorio(lista1);
            }
            if(opcao == 5){
                cout<<endl;
                if(!existeArv && !existeAVL){
                    cout << "  [   Nenhuma árvore foi utilizada   ]" << endl;
                }
                if (existeArv){
                    cout << endl;
                    cout << "                     [ Árvore Binário: ]                     "<< endl;
                    cout << endl;
                    imprime_arvore(Binaria);
                    cout<<endl;
                   
                }
                cout << endl;
                if (existeAVL){
                    cout << endl;
                    cout << "                      [ Árvore AVL: ]                      "<< endl;
                    cout << endl;
                    imprime_arvore(AVL);
                    cout<<endl;
                }
            }
        } while (opcao != 0);
    }
    return 0;
}