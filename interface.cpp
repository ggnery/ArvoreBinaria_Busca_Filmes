#include <iostream>
#include <string>
#include "interface.hpp"

// Vetor de ponteiros para funções que representam as opções do menu
FuncaoPtr F[] = {
	&sair,
	&buscarFilme,
	&informarAtributos,
	&visualisarGrafo,
	&removerFilme
};

// String que representa o menu de opções
string home = 
		"Escolha uma ação: \n"
		"1 - Buscar filme.\n"
		"2 - Informar atributos da árvore.\n"
		"3 - Visualisar grafo.\n"
		"4 - Remover filme.\n"
		"0 - Sair.\n"
		">> ";

/**
 * @brief Limpa a tela do terminal
 */
void clear() {
	system(CLEAR_COMMAND);
}

/**
 * @brief Função principal do programa que lê os dados do arquivo
 * 		  e inicia a interface
 */
void run() {
	BST* arvore = criarArvore();
	
	lerDados(arvore, "dados.txt");
	gerarGrafo(arvore);
	clear();
	
	while (1) {
		thisHome(arvore);
	}
}

/**
 * @brief Exibe o menu e chama a função correspondente à opção escolhida
 * 
 * @param arvore Ponteiro para a árvore
 */
void thisHome(BST* arvore) {
	int entrada;
	
	cout << home;
	cin >> entrada;
	
	if ((entrada >= 0) && (entrada <= QTD_FUNCOES)) {
		F[entrada](arvore);
	}
	
	cout << "Enter para continuar...";
	cin.ignore();
	cin.get();
	clear();
}

/**
 * @brief Apaga a árvore e sai do programa
 * 
 * @param arvore Ponteiro para a árvore
 */
void sair(BST* arvore) {
	liberarArvore(arvore->raiz);
	delete arvore;
	
	exit(0);
}

/**
 * @brief Busca um filme na árvore com base em um id
 * 		  e escreve em um arquivo
 * 
 * @param arvore Ponteiro para a árvore
 */
void buscarFilme(BST* arvore) {
	int entrada;
	No* filme;
	
	cout << "Qual o id do filme?\n>> ";
	cin >> entrada;
	
	filme = procurarNo(arvore->raiz, entrada);
	
	if (filme != NULL) {
		escreverFilmeEmArquivo(filme);
		system("filme.txt");
	} else {
		cout << "Filme não encontrado." << "\n";
	}

	cout << "\n";
}

/**
 * @brief Informa o tamanho e a altura da árvore
 * 
 * @param arvore Ponteiro para a árvore
 */
void informarAtributos(BST* arvore) {
	int tamanho, altura;
	
	tamanho = arvore->tamanho;
	altura = alturaArvore(arvore->raiz);
	
	cout << "Tamanho da árvore: " << tamanho << " elementos.";
	cout << "\nAltura da árvore: " << altura << " niveis.";
	cout << "\n" << "\n";
}

/**
 * @brief Gera um grafo da árvore
 * 
 * @param arvore Ponteiro para a árvore
 */
void visualisarGrafo(BST* arvore) {
	gerarGrafo(arvore);
	cout << "O arquivo tree.svg foi criado.\n\n";
}

/**
 * @brief Remove um filme da árvore com base no id
 * 
 * @param arvore Ponteiro para a árvore
 */
void removerFilme(BST* arvore) {
	int entrada;
	No* filme;
	
	cout << "Qual o id do filme?\n>> ";
	cin >> entrada;
	
	filme = procurarNo(arvore->raiz, entrada);
	
	if (filme == NULL) {
		cout << "Filme não encontrado.\n" << "\n";
	} else {
		arvore->raiz = removerNo(entrada, arvore->raiz, arvore);
		cout << "Filme removido." << "\n";
	}
}
