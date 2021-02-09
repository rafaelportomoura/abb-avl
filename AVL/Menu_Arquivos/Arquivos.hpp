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

void leRemocao( ifstream& leitura, avl& arvore, LINHA_CSV linhaCSV[ ] ) {
    Dado umDado;
    char operacao;
    char virgula;
    while ( leitura >> operacao >> virgula >> umDado ) {
        cout << umDado << " ";
        menu( arvore, operacao, umDado );
        if ( operacao == 'r' ) {
            for ( int i = 0; i < QUANTIDADE_DE_INSERCAO_E_REMOCAO; i++ ) {
                if ( linhaCSV[i].valor == umDado ) {
                    linhaCSV[i].remocao = CONTADOR_NO_REMOCAO;
                }
            }
        }
    }

}

void atribuiBuscaAoCSV( avl& arvore, LINHA_CSV linhaCSV[ ] ) {
    for ( int posicao = 0; posicao < QUANTIDADE_DE_INSERCAO_E_REMOCAO; posicao++ ) {
        menu( arvore, 'b', linhaCSV[posicao].valor );
        linhaCSV[posicao].busca = CONTADOR_NO_BUSCA;
    }
}

void escreveArquivo( ofstream& escrita, avl& arvore, LINHA_CSV linhaCSV[ ] ) {
    escrita << "valor,insercao,busca,remocao\n";
    for ( int posicao = 0; posicao < QUANTIDADE_DE_INSERCAO_E_REMOCAO; posicao++ ) {
        escrita << linhaCSV[posicao].valor << ',' << linhaCSV[posicao].insercao << ',' << linhaCSV[posicao].busca << ',' << linhaCSV[posicao].remocao << "\n";
    }
}