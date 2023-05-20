#include "interface.h"

#ifdef _WIN32
    #define SO 1
#elif __linux__
    #define SO 2
#endif

#define QTD_FUNCOES 4

typedef void (*FuncaoPtr)(BST*);

static void thisHome(BST* AV);
static void sair(BST* AV);
static void buscarFilme(BST* AV);
static void informarAtributos(BST* AV);
static void visualisarGrafo(BST* AV);
static void clear();

FuncaoPtr F[] = {
    &sair,
    &buscarFilme,
    &informarAtributos,
    &visualisarGrafo
};

//         cout<<"1 - Remover filme"<<endl;
//         cout<<"2 - Buscar filme"<<endl;
//         cout<<"3 - Tamanho da arvore"<<endl;
//         cout<< "4 - Altura arvore" <<endl;
//         cout<<"5- sair" <<endl;

string home = 
        "Escolha uma acao: \n"
        "1 - Buscar filme.\n"
        "2 - Informar atributos da arvore.\n"
        "3 - Visualisar grafo.\n"
        "0 - Sair.\n"
        ">> ";

void run(){
    BST* AV = criaArvore();
    leDados(AV, "dados.txt");
    gerarGrafo(AV);
    clear();
    while(1) thisHome(AV);
}

void thisHome(BST* AV){
    int entrada;
    cout << home;
    cin >> entrada;
    if(entrada >= 0 && entrada <= QTD_FUNCOES){
        F[entrada](AV);
    }
    cout << "Enter para continuar...";
    cin.ignore();
    cin.get();
    clear();
}

void sair(BST* AV){
    liberaArvore(AV->raiz);
    delete AV;
    exit(0);
}

void buscarFilme(BST* AV){
    int entrada;
    No* filme;
    cout << "Qual o id do filme?\n>> ";
    cin >> entrada;
    filme = procuraNo(AV->raiz, entrada);
    if(filme != NULL){
        escreverFilmeEmArquivo(filme);
        system("filme.txt");
    } else {
        cout << "Filme nao encontrado." <<endl;
    }
    cout << endl;
}

void informarAtributos(BST* AV){
    int tamanho;
    int altura;
    tamanho = AV->tamanho;
    altura = alturaArvore(AV->raiz);
    cout <<   "Tamanho da arvore: " << tamanho << " elementos.";
    cout << "\nAltura da arvore: " << altura << " niveis.";
    cout << "\n" << endl;
}

void visualisarGrafo(BST* AV){
    gerarGrafo(AV);
    cout << "Um tree.svg foi criado.\n\n";
    //system("tree.svg");
}

static void clear(){
    if(SO == 1) system("cls");
    else if(SO == 2) system("clear");
}
