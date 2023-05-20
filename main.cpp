#include <iostream>
#include "interface.h"
#include "AVL.h"



int main(){
    run();
    return 0;
}

// int main() {
//     BST* arvore = criaArvore();
//     leDados(arvore, "dados.txt");
//     gerarGrafo(arvore);
//     while(true){ 
//         int op;
//         cout<<"1 - Remover filme"<<endl;
//         cout<<"2 - Buscar filme"<<endl;
//         cout<<"3 - Tamanho da arvore"<<endl;
//         cout<< "4 - Altura arvore" <<endl;
//         cout<<"5- sair" <<endl;
//         cin>>op;

//         //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
//         if(op == 1){
//             int id;
//             cout<<"Digite o id a ser removido: ";
//             cin>>id;
//             //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
//             arvore->raiz = removeNo(id, arvore->raiz, arvore);
//             gerarGrafo(arvore);
//         }
//         if(op == 2){
//             int id;
//             cout << "Digite o id a ser procurado: ";
//             cin >> id;
//             No* no = procuraNo(arvore->raiz, id);
//             if (no != nullptr) {
//                 escreverFilmeEmArquivo(no);
//             } else {
//                 cout << "Elemento nao encontrado" << endl;
//             }
//         }
//         if(op == 3){
//             cout<< "O tamanho da arvore e: "<< arvore->tamanho <<endl;
//         }
//         if(op == 4){
//             cout<< "A altura da arvore e: "<< alturaArvore(arvore->raiz) <<endl;
//         }
//         if(op ==5){
//             break;
//         }
//     }
//     liberaArvore(arvore->raiz);
//     delete arvore;
//     return 0;   
// }