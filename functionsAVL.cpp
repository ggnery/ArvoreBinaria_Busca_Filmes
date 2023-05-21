#include <iostream>
#include <string>
#include <queue>
#include <fstream> 
#include "AVL.hpp"

using namespace std;

/**
 * @brief Cria uma nova árvore vazia
 * 
 * @return BST* - Ponteiro para a árvore criada
 */
BST* criarArvore() {
	BST* tree = new BST;

	if (tree == nullptr) {
		cout << "Erro ao alocar memória" << "\n";
		exit(1);
	}	

	tree->raiz = nullptr; 
	tree->tamanho = 0;

	return tree;
}

/**
 * @brief Cria um novo nó com o 'filme' passado como parâmetro
 * 
 * @param filme Filme a ser inserido no nó
 * @return No* - Ponteiro para o nó criado
 */
No* criarNo(Filme filme) {
	No* node = new No;

	node->filme = filme;
	node->altura = 0;
	node->direita = nullptr;
	node->esquerda = nullptr;

	return node;
}

/**
 * @param num1 Primeiro número inteiro
 * @param num2 Segundo número inteiro
 * @return int - Maior valor entre 'num1' e 'num2'
 */
int maior(int num1, int num2) {
	return (num1 > num2) ? num1 : num2;
}

/**
 * @param raiz Raiz da árvore
 * @return int - Altura da árvore
 */
int alturaArvore(No* raiz) {
	if (raiz == nullptr) {
		return -1;
	} else {
		int esq = alturaArvore(raiz->esquerda);
		int dir = alturaArvore(raiz->direita);
		
		if (esq > dir) {
			return esq + 1;
		} else {
			return dir + 1;
		}
	}
}

/**
 * @param no Um nó da árvore
 * @return int - Altura do 'nó'
 */
int alturaNo(No* no) {
	if(no == nullptr){
		return -1; 
	}else{
		return no->altura;
	}      
}

/**
 * @param no Um nó da árvore
 * @return int - Fator de balanceamento do 'nó'
 */
int fatorBalanceamento(No* no) {
	if (no != nullptr) {
		return alturaNo(no->esquerda) - alturaNo(no->direita);
	} else {
		return 0;
	}
}

/**
 * @brief Faz a rotação da árvore para a esquerda
 * 
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para a nova raiz da árvore
 */
No* rotacionarEsquerda(No* raiz) {
	// Nó à direita da raiz
	No* noDireita = raiz->direita;
	// Nó à esquerda de noDireita
	No* noEsquerda = noDireita->esquerda;

	// Fazendo a rotação
	noDireita->esquerda = raiz;
	raiz->direita = noEsquerda;

	// Recalcula as alturas dos nós
	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
	noDireita->altura = maior(alturaNo(noDireita->esquerda), alturaNo(noDireita->direita)) + 1;

	return noDireita;
}

/**
 * @brief Faz a rotação da árvore para a direita
 * 
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para a nova raiz da árvore
 */
No* rotacionarDireita(No* raiz) {
	// Nó à esquerda da raiz
	No* noEsquerda = raiz->esquerda;
	// Nó à direita de noEsquerda
	No* noDireita = noEsquerda->direita;

	// Fazendo a rotação
	noEsquerda->direita = raiz;
	raiz->esquerda = noDireita;

	//recalcula as alturas dos nós
	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
	noEsquerda->altura = maior(alturaNo(noEsquerda->esquerda), alturaNo(noEsquerda->direita)) + 1;

	return noEsquerda;
}

/**
 * @brief Faz a rotação esquerda->direita da árvore
 * 
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para a nova raiz da árvore
 */
No* rotacionarEsquerdaDireita(No* raiz) {
	// Faz a rotação à esquerda ...
	raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
	// ... e depois à direita
	return rotacionarDireita(raiz);
}

/**
 * @brief Faz a rotação direita->esquerda da árvore
 * 
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para a nova raiz da árvore
 */
No* rotacionarDireitaEsquerda(No* raiz) {
	// Faz a rotação à direita ...
	raiz->direita = rotacionarDireita(raiz->direita);
	// ... e depois à esquerda
	return rotacionarEsquerda(raiz); 
}

/**
 * @brief Balanceia a árvore a partir do nó 'raiz'
 * 
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para a raiz da árvore balanceada
 */
No* balancear(No* raiz) {
	if (raiz == nullptr) {
		return nullptr;
	}

	int f = fatorBalanceamento(raiz);

	// Rotaciona para a esquerda
	if ((f < -1) && (fatorBalanceamento(raiz->direita) <= 0)) { 
		raiz = rotacionarEsquerda(raiz);
	}

	// Rotaciona para a direita
	else if ((f > 1) && (fatorBalanceamento(raiz->esquerda) >= 0)) {
		raiz = rotacionarDireita(raiz);
	}

	// Rotaciona para a direita->esquerda
	else if ((f < -1) && (fatorBalanceamento(raiz->direita) > 0)) {
		raiz = rotacionarDireitaEsquerda(raiz);
	}

	// Rotaciona para a esquerda->direita
	else if ((f > 1) && (fatorBalanceamento(raiz->esquerda) < 0)) {
		raiz = rotacionarEsquerdaDireita(raiz);
	}

	return raiz;
}

/**
 * @brief Insere um novo nó na 'árvore' contendo o 'filme' informado
 * 		  e balanceia ela após a inserção
 * 
 * @param filme Filme a ser inserido no nó
 * @param raiz Raiz da árvore
 * @param arvore Ponteiro para a árvore
 * @return No* - Ponteiro para o nó criado
 */
No* inserirNo(Filme filme, No* raiz, BST* arvore) {
	if (arvore == nullptr) {
		cout << "Erro ao inserir elemento: árvore não alocada" << "\n";
		return nullptr;
	}
	
	if (raiz == nullptr) {
		arvore->tamanho++;
		return criarNo(filme);       
	}

	if (filme.id < raiz->filme.id) {
		raiz->esquerda = inserirNo(filme, raiz->esquerda, arvore);
	}
	else if (filme.id > raiz->filme.id) {
		raiz->direita = inserirNo(filme, raiz->direita, arvore);
	}
	else {
		cout << "Erro ao inserir elemento: elemento já existe na árvore" << "\n";
		return raiz;
	}

	// Recalcula a altura de todos os nós entre a raiz e o no inserido 
	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
	
	// Balanceia a sub-árvore
	raiz = balancear(raiz);
	
	return raiz;
}

/**
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para o nó com o maior valor da árvore
 * 		   (nó mais à direita da árvore)
 */
No* maiorNo(No* raiz) {
	No* aux = raiz;
	
	while ((aux != nullptr) && (aux->direita != nullptr)) {
		aux = aux->direita;
	}

	return aux;
}

/**
 * @param raiz Raiz da árvore
 * @return No* - Ponteiro para o nó com o menor valor da árvore
 * 		   (nó mais à esquerda da árvore)
 */
No* menorNo(No* raiz) {
	No* aux = raiz;
	
	while ((aux != nullptr) && (aux->esquerda != nullptr)) {
		aux = aux->esquerda;
	}
	
	return aux;
}

/**
 * @brief Remove o nó com o 'id' informado da 'árvore'
 * 		  e balanceia ela após a remoção.
 * 
 * @param id id do filme a ser removido
 * @param raiz Raiz da árvore
 * @param arvore Ponteiro para a árvore
 * @return No* - Ponteiro para a raiz da árvore (agora sem o 'nó' removido)
 */
No* removerNo(int id, No* raiz, BST* arvore) {
	if (arvore == nullptr) {
		cout << "Erro ao remover elemento: árvore não alocada" << "\n";
		return nullptr;
	}
	
	if (raiz == nullptr) {
		cout << "O elemento não existe na árvore" << "\n";
		return nullptr;
	}

	if (raiz->filme.id == id) {
		if ((raiz->direita == nullptr) && (raiz->esquerda == nullptr)) {
			delete raiz;
			arvore->tamanho--;

			return nullptr;
		}

		else if ((raiz->esquerda == nullptr) || (raiz->direita == nullptr)) {
			No* aux;
			if (raiz->esquerda == nullptr) {
				aux = raiz->direita;
			}
			else {
				aux = raiz->esquerda;
			}

			delete raiz;
			arvore->tamanho--;
			
			return aux;
		}

		else {
			No* aux = maiorNo(raiz->esquerda);
			raiz->filme = aux->filme;
			raiz->esquerda = removerNo(aux->filme.id, raiz->esquerda, arvore);
			raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
			raiz = balancear(raiz);
			
			return raiz;
		}
	}

	else if (id < raiz->filme.id) {
		raiz->esquerda = removerNo(id, raiz->esquerda, arvore);
	}

	else {
		raiz->direita = removerNo(id, raiz->direita, arvore);
	}

	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
	raiz = balancear(raiz);

	return raiz;
}

/**
 * @brief Procura um nó na árvore com o 'id' informado
 * 
 * @param raiz Raiz da árvore
 * @param id id do filme a ser procurado
 * @return No* - Ponteiro para o nó com o 'id' informado (se existir)
 */
No* procurarNo(No* raiz, int id) {
	No* aux = raiz;
	
	while (aux) {
		if (aux->filme.id == id) {
			return aux;
		} else if (id < aux->filme.id) {
			aux = aux->esquerda;
		} else {
			aux = aux->direita;
		}
	}

	return nullptr;
}

/**
 * @brief Libera a memória alocada para a árvore
 * 
 * @param raiz Raiz da árvore
 */
void liberarArvore(No* raiz) {
	if (raiz != nullptr) {
		liberarArvore(raiz->esquerda);
		liberarArvore(raiz->direita);
		delete raiz;
	}
}

/**
 * @brief Cria um arquivo txt que representa a 'árvore'
 * 		  e vai ser lido pelo graphviz
 * 
 * @param arvore Ponteiro para a árvore 
 */
void gerarGrafo(BST* arvore) {
	if (arvore == nullptr) {
		cout << "Erro ao gerar grafo: árvore não alocada" << "\n";
		return;
	}

	ofstream file("tree.dot");

	file << "digraph BST {" << "\n";
	file << "    node [shape=circle];" << "\n";

	queue<No*> nodeQueue;
	nodeQueue.push(arvore->raiz);

	while (!nodeQueue.empty()) {
		No* current = nodeQueue.front();
		nodeQueue.pop();

		// Adiciona espaços antes e depois do nome do filme
		string label = "\"" + to_string(current->filme.id) + ": "+current->filme.nome + "\"";

		file << "    " << label << ";" << "\n";

		if (current->esquerda != nullptr) {
			string leftLabel = "\"" + to_string(current->esquerda->filme.id) + ": " +current->esquerda->filme.nome + "\"";
			file << "    " << label << " -> " << leftLabel << ";" << "\n";
			nodeQueue.push(current->esquerda);
		}

		if (current->direita != nullptr) {
			string rightLabel = "\"" + to_string(current->direita->filme.id) +": "+current->direita->filme.nome + "\"";
			file << "    " << label << " -> " << rightLabel << ";" << "\n";
			nodeQueue.push(current->direita);
		}
	}

	file << "}" << "\n";

	file.close();

	// Comando para gerar a imagem usando o Graphviz
	system("dot -Tsvg tree.dot -o tree.svg");
}

/**
 * @brief Lê o arquivo de dados txt
 * 
 * @param arvore Ponteiro para a árvore
 * @param arquivoTXT Nome do arquivo txt
 */
void lerDados(BST* arvore, string arquivoTXT) {
	// Nome do arquivo externo com os dados dos filmes
	ifstream arquivo(arquivoTXT);
	
	if (!arquivo.is_open()) {
		cout << "\033[1;31mErro ao abrir o arquivo\033[m\n";
		exit(1);
	}

	Filme filme;

	while (getline(arquivo, filme.nome)) {
		arquivo >> filme.id;
		arquivo.ignore();
		getline(arquivo, filme.linguagem);
		getline(arquivo, filme.popularidade);
		getline(arquivo, filme.lancamento);
		getline(arquivo, filme.descricao);
		arvore->raiz = inserirNo(filme, arvore->raiz, arvore);
	}

	arquivo.close();
}

/**
 * @brief Escreve as informações de um filme em um arquivo txt
 * 
 * @param no Ponteiro para o nó que contém o filme
 */
void escreverFilmeEmArquivo(No* no) {
	ofstream arquivo("filme.txt");
	
	if (arquivo.is_open()) {
		arquivo << "Nome: " << no->filme.nome << "\n";
		arquivo << "Id: " << no->filme.id << "\n";
		arquivo << "Data de lançamento: " << no->filme.lancamento << "\n";
		arquivo << "Língua: " << no->filme.linguagem << "\n";
		arquivo << "Popularidade: " << no->filme.popularidade << "\n";
		arquivo << "Descrição: " << no->filme.descricao << "\n";
		arquivo.close();
		cout << "\033[1;32mInformações do filme foram gravadas no arquivo 'filme.txt'\033[m\n";
	} else {
		cout << "\033[1;31mErro ao abrir o arquivo\n";
	}

	arquivo.close();
}
