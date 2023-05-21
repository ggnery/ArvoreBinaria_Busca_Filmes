#include <iostream>
#include <string>
#include "interface.hpp"

// Vetor de ponteiros para funções que representam as opções do menu
FuncaoPtr F[] = {
	&sair,
	&adicionarFilme,
	&removerFilme,
	&buscarFilme,
	&informarAtributos,
	&visualizarGrafo,
	&carregarArquivo
};

// String que representa o menu de opções
string home = 
	"\033[0;36m"
	"      Escolha uma opção: \n\n"
	"\033[1;32m 1) \033[0;m \033[0;32mAdicionar filme \n"
	"\033[1;31m 2) \033[0;m \033[0;31mRemover filme\n"
	"\033[1;33m 3) \033[0;m \033[0;33mBuscar filme\n"
	"\033[1;35m 4) \033[0;m \033[0;35mInformar atributos da árvore\n"
	"\033[1;36m 5) \033[0;m \033[0;36mVisualizar grafo\n"
	"\033[1;34m 6) \033[0;m \033[0;34mCarregar dados (Ação única)\n"
	"\033[1;30m 0)  Sair\n"
	"\033[0m"
	">> ";

// String que representa o título do programa
string title = 
	"\033[1;36m"
	"------------------------------\n"
	"     Árvore AVL de filmes     \n"
	"------------------------------\n"
	"\033[m";

// String que representa o submenu de inserção de filmes
string adicionaFilme = 
	"\033[1;32m"
	"---------------------\n"
	"   Adição de filme   \n"
	"---------------------\n"
	"\033[m";

// String que representa o submenu de remoção de filmes
string removeFilme = 
	"\033[1;31m"
	"----------------------\n"
	"   Remoção de filme   \n"
	"----------------------\n"
	"\033[m";

// String que representa o submenu de busca de filmes
string buscaFilme = 
	"\033[1;33m"
	"--------------------\n"
	"   Busca de filme   \n"
	"--------------------\n"
	"\033[m";

// String que representa o submenu de remoção de filmes
string informaAtributos = 
	"\033[1;35m"
	"-----------------------------\n"
	"   Informação da árvore AVL  \n"
	"-----------------------------\n"
	"\033[m";

// String que representa o submenu de visualização do grafo
string visualizaGrafo = 
	"\033[1;36m"
	"----------------------\n"
	"   Visualizar grafo   \n"
	"----------------------\n"
	"\033[m";

// String que representa o submenu de carregamento de dados
string carregaDados = 
	"\033[1;34m"
	"---------------------------\n"
	"   Carregamento de dados   \n"
	"---------------------------\n"
	"\033[m";

// Condição que indica se os dados já foram carregados
bool carregado = false;


/**
 * @brief Limpa a tela do terminal
 */
void clear() {
	system(CLEAR_COMMAND);
}

/**
 * @brief Função principal do programa que inicia a interface
 */
void run() {
	BST* arvore = criarArvore();
	
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
	
	cout << title;
	while (1) {
		cout << home;
		cin >> entrada;

		if ((entrada >= 0) && (entrada < QTD_FUNCOES)) {
			break;
		} else {
			clear();
			cout << "\033[1;31mERRO: Opção inválida\n\n\033[m";
		}
	}
	
	F[entrada](arvore);
	
	if (entrada == 6) {
		carregado = true;
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
 * @brief Adiciona um filme na árvore
 * 
 * @param arvore Ponteiro para a árvore
 */
void adicionarFilme(BST* arvore) {
	Filme filme;

	clear();

	while (1) {
		cout << adicionaFilme;

		cout << "\033[0;32mQual o id do filme?\033[m\n>> ";
		cin >> filme.id;
		cin.ignore();

		if (procurarNo(arvore->raiz, filme.id) != nullptr) {
			clear();
			cout << "\033[1;31mERRO: Filme com esse id já cadastrado\n\n\033[m";
		} else {
			break;
		}
	}

	cout << "\033[0;32mQual o nome do filme?\033[m\n>> ";
	getline(cin, filme.nome);

	cout << "\033[0;32mQual a data de lançamento do filme? (aaaa-mm-dd)\033[m\n>> ";
	getline(cin, filme.lancamento);

	cout << "\033[0;32mEm qual idioma o filme foi lançado? (en)\033[m\n>> ";
	getline(cin, filme.linguagem);

	cout << "\033[0;32mQual a popularidade do filme? (8530.89)\033[m\n>> ";
	getline(cin, filme.popularidade);

	cout << "\033[0;32mQual a descrição do filme?\033[m\n>> ";
	getline(cin, filme.descricao);

	arvore->raiz = inserirNo(filme, arvore->raiz, arvore);

	cout << "\033[1;32mFilme adicionado com sucesso\033[m\n\n";
}

/**
 * @brief Remove um filme da árvore com base no id
 * 
 * @param arvore Ponteiro para a árvore
 */
void removerFilme(BST* arvore) {
	int entrada;
	No* filme;

	clear();
	cout << removeFilme;
	
	cout << "\033[0;33mQual o id do filme?\033[m\n>> ";
	cin >> entrada;
	
	filme = procurarNo(arvore->raiz, entrada);
	
	if (filme == NULL) {
		cout << "\033[1;31mFilme não encontrado\033[m\n\n";
	} else {
		arvore->raiz = removerNo(entrada, arvore->raiz, arvore);
		cout << "\033[1;32mFilme removido com sucesso\033[m\n\n";
	}
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

	clear();
	cout << buscaFilme;
	
	cout << "\033[0;33mQual o id do filme?\033[m\n>> ";
	cin >> entrada;
	
	filme = procurarNo(arvore->raiz, entrada);
	
	if (filme != nullptr) {
		escreverFilmeEmArquivo(filme);
	} else {
		cout << "\033[1;31mFilme não encontrado\033[m\n";
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

	clear();
	cout << informaAtributos;
	
	tamanho = arvore->tamanho;
	altura = alturaArvore(arvore->raiz);
	
	cout << "\033[0;35m* Tamanho: \033[1;35m" << tamanho << "\033[0;35m elementos\n";
	cout << "* Altura: \033[1;35m" << altura << "\033[0;35m níveis\033[m\n\n";
}

/**
 * @brief Gera um grafo da árvore
 * 
 * @param arvore Ponteiro para a árvore
 */
void visualizarGrafo(BST* arvore) {
	clear();
	cout << visualizaGrafo;

	cout << "\033[36mGerando grafo...\n";
	cout << "Pode demorar um pouco\033[m\n";

	gerarGrafo(arvore);
	cout << "\033[1;32mO arquivo tree.svg foi criado\033[m\n\n";
}

/**
 * @brief Lê os dados do arquivo e os insere na árvore (Ação única)
 * 
 * @param arvore Ponteiro para a árvore
 */
void carregarArquivo(BST* arvore) {
	clear();
	cout << carregaDados;

	if (carregado) {
		cout << "\033[1;31mOs dados já foram carregados\033[m\n\n";
	} else {
		cout << "\033[34mLendo dados do arquivo...\n";
		cout << "Pode demorar um pouco\033[m\n";

		lerDados(arvore, "dados.txt");
		gerarGrafo(arvore);
	
		cout << "\033[1;32mO arquivo tree.svg foi criado\033[m\n\n";
	}
}
