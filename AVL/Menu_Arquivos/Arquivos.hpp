#include "Menu.hpp"
#include <fstream>

void leEntrada( ifstream& leitura, avl& arvore, LINHA_CSV linhaCSV[ ] ) {
    Dado umDado;
    char operacao, virgula;
    int cont = 0;
    while ( leitura >> operacao >> virgula >> umDado ) {
        cout << umDado << endl;
        menu( arvore, operacao, umDado );
        if ( operacao == 'i' && cont < QUANTIDADE_DE_INSERCAO_E_REMOCAO ) {
            linhaCSV[cont].valor = umDado;
            linhaCSV[cont].insercao = CONTADOR_NO_INSERCAO;
            cout << "valor: " << linhaCSV[cont].valor << " insercao: " << linhaCSV[cont].insercao << endl;
            cont++;
        }
    }
}
