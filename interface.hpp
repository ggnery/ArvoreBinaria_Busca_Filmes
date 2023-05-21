#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

// Includes
#include "AVL.hpp"

// Macros
#ifdef _WIN32
	#define CLEAR_COMMAND "cls"
#elif __linux__
	#define CLEAR_COMMAND "clear"
#endif

#define QTD_FUNCOES 7

using namespace std;


// Declarações de funções e tipos

typedef void (*FuncaoPtr)(BST*);
void clear();
void run();
void thisHome(BST* arvore);
void sair(BST* arvore);
void adicionarFilme(BST* arvore);
void removerFilme(BST* arvore);
void buscarFilme(BST* arvore);
void informarAtributos(BST* arvore);
void visualizarGrafo(BST* arvore);
void carregarArquivo(BST* arvore);

#endif // INTERFACE_H_INCLUDED