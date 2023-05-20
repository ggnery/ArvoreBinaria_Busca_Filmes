#ifndef AVL
#define AVL

#include <fstream> 
#include <string>
#include <queue>
#include <iostream>
#include <limits>
//#include <cstdlib>

using namespace std;

typedef struct filme {
    int id;
    string nome;
    string linguagem;
    string popularidade;
    string lancamento;
    string descricao;
} Filme;

//Representa um no da arvore
typedef struct no{
    Filme filme;
    int altura;
    struct no* direita;
    struct no* esquerda;
}No;

typedef struct bst{
    No* raiz;
    int tamanho;
}BST;


BST* criaArvore();
No* criaNo(Filme filme);
int maior(int a, int b);
int alturaNo(No* no);
int fatorBalanceamento(No *no);
No* rotacionarEsquerda(No* raiz);
No* rotacionarDireita(No* raiz);
No* rotacionarDireitaEsquerda(No* raiz);
No* rotacionarEsquerdaDireita(No* raiz);
No* balancear(No* raiz);
No* insereArvore(Filme filme, No* raiz, BST* arvore);
No* encontraMenor(No* raiz);
No* encontraMaior(No* raiz);
No* removeNo(int id, No* raiz, BST* arvore);
int alturaArvore(No* raiz);
void liberaArvore(No* raiz);
No* procuraNo(No* raiz, int id);
void gerarGrafo(const BST* arvore);
void leDados(BST* arvore, string arquivoTXT);
void escreverFilmeEmArquivo(No* no);

#endif