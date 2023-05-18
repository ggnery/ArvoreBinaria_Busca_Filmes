#include <fstream> 
#include <string>
#include <queue>
#include <iostream>
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

//Representa a arvore
BST* criaArvore(){
    BST* p = new BST;
    if(p == nullptr) exit(1);
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
    if(n == nullptr) exit(1);

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
   
    No* y, *f; 

    y = raiz->direita; // no direita da raiz
    f = y->esquerda;   //no esquerda de y

    //Fazendo a rotacao
    y->esquerda = raiz;
    raiz->direita = f;


    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    return y;
}

/**
 * @brief Faz a rotação da arvore para a direita
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarDireita(No* raiz){
    No* y, *f;

    y = raiz->esquerda; //ó esquerda da raiz
    f = y->direita; //nó direita de y

    //Fazendo a rotacao
    y->direita = raiz;
    raiz->esquerda = f;

    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

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
        printf("O elemento ja existe\n");
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
No* removeNo(Filme filme, No* raiz, BST* arvore) {
    if (raiz == nullptr) {
        printf("O elemento nao existe na arvore\n");
        return nullptr;
    }

    if (raiz->filme.id == filme.id) {
        if (raiz->direita == nullptr && raiz->esquerda == nullptr) {
            free(raiz);
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
            free(raiz);
            arvore->tamanho--;
            return aux;
        }
        else {
            No* aux = encontraMaior(raiz->esquerda);
            raiz->filme = aux->filme;
            raiz->esquerda = removeNo(aux->filme, raiz->esquerda, arvore);
            raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
            raiz = balancear(raiz);
            return raiz;
        }
    }
    else if (filme.id < raiz->filme.id) {
        raiz->esquerda = removeNo(filme, raiz->esquerda, arvore);
    }
    else {
        raiz->direita = removeNo(filme, raiz->direita, arvore);
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
 * @brief Imprime a arvore
 * 
 * @param raiz 
 * @param nivel 
 */
void imprimir(No* raiz, int nivel){
    int i;
    if(raiz != nullptr){
        imprimir(raiz->direita, nivel+1);
        cout<<"\n\n";

        for(i=0; i<nivel; i++)
            cout<<"\t";

        cout << raiz->filme.nome;
        imprimir(raiz->esquerda, nivel +1);  
    }
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
        string label = "\"" + to_string(current->filme.id) + " : "+current->filme.nome + "\"";

        file << "    " << label << ";" << endl;

        if (current->esquerda != nullptr) {
            string leftLabel = "\"" + to_string(current->esquerda->filme.id) + " : " +current->esquerda->filme.nome + "\"";
            file << "    " << label << " -> " << leftLabel << ";" << endl;
            nodeQueue.push(current->esquerda);
        }

        if (current->direita != nullptr) {
            string rightLabel = "\"" + to_string(current->direita->filme.id) +" : "+current->direita->filme.nome + "\"";
            file << "    " << label << " -> " << rightLabel << ";" << endl;
            nodeQueue.push(current->direita);
        }
    }

    file << "}" << endl;

    file.close();

    // Comando para gerar a imagem usando o Graphviz
    system("dot -Tpng tree.dot -o tree.png");
}





int main(){
    
    int n;
    cin >> n;
    cin.ignore();
    
    BST* arvore = criaArvore();

    while (n--) {
        Filme filme;
        getline(cin, filme.nome);
        cin>>filme.id;
        cin.ignore();
        getline(cin, filme.linguagem);
        getline(cin, filme.popularidade);
        getline(cin, filme.lancamento);
        getline(cin, filme.descricao);
        arvore->raiz = insereArvore(filme, arvore->raiz, arvore);
        
    }
    
    gerarGrafo(arvore);
    //imprimir(arvore->raiz, 1);
    liberaArvore(arvore->raiz);
    delete arvore;
    
    return 0;
    
}
