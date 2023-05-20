#include "AVL.h"

//Representa a arvore
BST* criaArvore(){
    BST* p = new BST;
    p->raiz = nullptr; 
    p->tamanho = 0;
    return p;
}

/**
 * @brief Cria um novo no da arvore
 * 
 * @param dado 
 * @return No* 
 */
No* criaNo(Filme filme){
    No* n = new No;
    n->filme = filme;
    n->altura = 0;
    n->direita = nullptr;
    n->esquerda = nullptr;
    return n;
}

/**
 * @brief Retorna o maior valor de a ou b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int maior(int a, int b){
    return (a>b)? a:b;
}

/**
 * @brief Retorna a altura de um no
 * 
 * @param no 
 * @return int 
 */
int alturaNo(No* no){
    if(no == nullptr){
        return -1; 
    }else{
        return no->altura;
    }      
}

/**
 * @brief Calcula o fator de balanceamento de um no
 * 
 * @param no 
 * @return int 
 */
int fatorBalanceamento(No *no){
    if(no != nullptr){
        return alturaNo(no->esquerda) - alturaNo(no->direita);
    }else{
        return 0;
    }
}

/**
 * @brief Faz a rotação da arvore para a esquerda
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarEsquerda(No* raiz){

    No* y  = raiz->direita; // no direita da raiz
    No* f = y->esquerda;   //no esquerda de y

    //Fazendo a rotacao
    y->esquerda = raiz;
    raiz->direita = f;


    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

/**
 * @brief Faz a rotação da arvore para a direita
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarDireita(No* raiz){

    No* y = raiz->esquerda; //ó esquerda da raiz
    No* f = y->direita; //nó direita de y

    //Fazendo a rotacao
    y->direita = raiz;
    raiz->esquerda = f;

    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

/**
 * @brief Faz a rotação esquerda->direita da arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarDireitaEsquerda(No* raiz){
    raiz->direita = rotacionarDireita(raiz->direita); //Faz a rotação a direita
    return rotacionarEsquerda(raiz); //Faz a rotação a esquerda
}

No* rotacionarEsquerdaDireita(No* raiz){
    raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
    return rotacionarDireita(raiz);
}

No* balancear(No* raiz){
    int f = fatorBalanceamento(raiz);//calcula o fator de balanceamento do no

    //Rotaciona para a esquerda
    if(f<-1 && fatorBalanceamento(raiz->direita) <=0){ 
        
        raiz = rotacionarEsquerda(raiz);
    
    
    }
    //rotaciona para a direita->esquerda
    else if(f<-1 && fatorBalanceamento(raiz->direita) >0){
        
        raiz = rotacionarDireitaEsquerda(raiz);
    
    }
    //rotaciona para a direita
    else if(f>1 && fatorBalanceamento(raiz->esquerda) >= 0){
        
        raiz = rotacionarDireita(raiz);
    
    }
    //rotaciona para a esquerda->direita
    else if(f>1 && fatorBalanceamento(raiz->esquerda) < 0){
        
        raiz = rotacionarEsquerdaDireita(raiz);
    
    }

    return raiz;
}

/**
 * @brief Insere um elemento na arvore e balanceia a mesma
 * 
 * @param dado 
 * @param raiz 
 * @param arvore 
 * @return No* 
 */
No* insereArvore(Filme filme, No* raiz, BST* arvore){
    if(raiz == nullptr){
        arvore->tamanho++;
        return criaNo(filme);       
    }

    if(filme.id < raiz->filme.id){
        raiz->esquerda = insereArvore(filme, raiz->esquerda, arvore);
    }else if(filme.id > raiz->filme.id){
        raiz->direita = insereArvore(filme, raiz->direita, arvore);
    }else{
        return raiz;
    }
    //Recalcula a altura de todos os nos entre a raiz e o no inserido 
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita))+1;
    
    //Balanceia a sub-arvore
    raiz = balancear(raiz);
    
    return raiz;
    
}

/**
 * @brief Encontra o menor elemento em uma arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* encontraMenor(No* raiz){
    No* aux = raiz;
    while(aux != nullptr && aux->esquerda!=nullptr){
        aux = aux->esquerda;
    }
    return aux;
}

/**
 * @brief Encontra o maior elemento em uma arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* encontraMaior(No* raiz){
    No* aux = raiz;
    while(aux != nullptr && aux->direita!=nullptr){
        aux = aux->direita;
    }
    return aux;
}

/**
 * @brief Remove o no de uma arvore e balanceia a mesma
 * 
 * @param dado 
 * @param raiz 
 * @param arvore 
 * @return No* 
 */
No* removeNo(int id, No* raiz, BST* arvore) {
    if (raiz == nullptr) {
        cout<<"O elemento nao existe na arvore"<<endl;
        return nullptr;
    }

    if (raiz->filme.id == id) {
        if (raiz->direita == nullptr && raiz->esquerda == nullptr) {
            delete raiz;
            arvore->tamanho--;
            return nullptr;
        }
        else if (raiz->esquerda == nullptr || raiz->direita == nullptr) {
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
            No* aux = encontraMaior(raiz->esquerda);
            raiz->filme = aux->filme;
            raiz->esquerda = removeNo(aux->filme.id, raiz->esquerda, arvore);
            raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
            raiz = balancear(raiz);
            
            return raiz;
        }
    }
    else if (id < raiz->filme.id) {
        raiz->esquerda = removeNo(id, raiz->esquerda, arvore);
    }
    else {
        raiz->direita = removeNo(id, raiz->direita, arvore);
    }

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    raiz = balancear(raiz);
    return raiz;
}

/**
 * @brief Encontra a altura total da arvore
 * 
 * @param raiz 
 * @return int 
 */
int alturaArvore(No* raiz){
    if(raiz == nullptr){
        return -1;
    }else{
        int esq = alturaArvore(raiz->esquerda);
        int dir = alturaArvore(raiz->direita);
        if(esq > dir){
            return esq + 1;
        }else{
            return dir + 1;
        }
    }
}

/**
 * @brief Libera a memoria da arvore
 * 
 * @param raiz 
 */
void liberaArvore(No* raiz){
    if(raiz != nullptr){
        liberaArvore(raiz->esquerda);
        liberaArvore(raiz->direita);
        delete raiz;
    }
}


/**
 * @brief Procura um filme com base no id desse
 * 
 * @param raiz 
 * @param id 
 * @return No* 
 */
No* procuraNo(No* raiz, int id){
    No* aux = raiz;
    while(aux){
        if(aux->filme.id == id){
            return aux;
        }else if(id < aux->filme.id){
            aux = aux->esquerda;
        }else{
            aux = aux->direita;
        }
    }
    return NULL;
}

/**
 * @brief Cria um arquivo txt que representa a arvore e vai ser lido pelo graphviz
 * 
 * @param arvore 
 */
void gerarGrafo(const BST* arvore) {
    ofstream file("tree.dot");

    file << "digraph BST {" << endl;
    file << "    node [shape=circle];" << endl;

    queue<No*> nodeQueue;
    nodeQueue.push(arvore->raiz);

    while (!nodeQueue.empty()) {
        No* current = nodeQueue.front();
        nodeQueue.pop();
        // Adiciona espaços antes e depois do nome do filme
        string label = "\"" + to_string(current->filme.id) + ": "+current->filme.nome + "\"";

        file << "    " << label << ";" << endl;

        if (current->esquerda != nullptr) {
            string leftLabel = "\"" + to_string(current->esquerda->filme.id) + ": " +current->esquerda->filme.nome + "\"";
            file << "    " << label << " -> " << leftLabel << ";" << endl;
            nodeQueue.push(current->esquerda);
        }

        if (current->direita != nullptr) {
            string rightLabel = "\"" + to_string(current->direita->filme.id) +": "+current->direita->filme.nome + "\"";
            file << "    " << label << " -> " << rightLabel << ";" << endl;
            nodeQueue.push(current->direita);
        }
    }

    file << "}" << endl;

    file.close();

    // Comando para gerar a imagem usando o Graphviz
    system("dot -Tsvg tree.dot -o tree.svg");
}

/**
 * @brief Le o arquivo de dados txt
 * 
 * @param arvore 
 * @param arquivoTXT 
 */
void leDados(BST* arvore, string arquivoTXT){
    ifstream arquivo(arquivoTXT); // Nome do arquivo externo com os dados dos filmes
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
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
        arvore->raiz = insereArvore(filme, arvore->raiz, arvore);
    }

    arquivo.close();
}

void escreverFilmeEmArquivo(No* no) {
    ofstream arquivo("filme.txt");
    if (arquivo.is_open()) {
        arquivo << "Nome: " << no->filme.nome << endl;
        arquivo << "Id: " << no->filme.id << endl;
        arquivo << "Data de lançamento: " << no->filme.lancamento << endl;
        arquivo << "Língua: " << no->filme.linguagem << endl;
        arquivo << "Popularidade: " << no->filme.popularidade << endl;
        arquivo << "Descrição: " << no->filme.descricao << endl;
        arquivo.close();
        cout << "Informacoes do filme foram gravadas no arquivo 'filme.txt'." << endl;
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
    arquivo.close();
}
