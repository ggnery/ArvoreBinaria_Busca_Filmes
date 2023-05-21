#ifndef AVL_HPP_INCLUDED
#define AVL_HPP_INCLUDED

#include <string>

using namespace std;


// Struct para armazenar os dados de um filme e definição do tipo Filme
typedef struct filme {
	int id;
	string nome;
	string linguagem;
	string popularidade;
	string lancamento;
	string descricao;
} Filme;

// Struct para armazenar os dados de um nó da árvore e definição do tipo No
typedef struct no {
	Filme filme;
	int altura;
	struct no* direita;
	struct no* esquerda;
} No;

// Struct para armazenar os dados da árvore e definição do tipo BST
typedef struct bst {
	No* raiz;
	int tamanho;
} BST;

// Declaração das funções

BST* criarArvore();
No* criarNo(Filme filme);
int maior(int num1, int num2);
int alturaArvore(No* raiz);
int alturaNo(No* no);
int fatorBalanceamento(No *no);
No* rotacionarEsquerda(No* raiz);
No* rotacionarDireita(No* raiz);
No* rotacionarEsquerdaDireita(No* raiz);
No* rotacionarDireitaEsquerda(No* raiz);
No* balancear(No* raiz);
No* inserirNo(Filme filme, No* raiz, BST* arvore);
No* maiorNo(No* raiz);
No* menorNo(No* raiz);
No* removerNo(int id, No* raiz, BST* arvore);
No* procurarNo(No* raiz, int id);
void liberarArvore(No* raiz);
void gerarGrafo(BST* arvore);
void lerDados(BST* arvore, string arquivoTXT);
void escreverFilmeEmArquivo(No* no);

#endif // AVL_HPP_INCLUDED