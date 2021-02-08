#include "Menu.hpp"
#include <fstream>

void leArquivoTeste( ifstream& leitura, ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    Dado d;
    char escolha;
    char virgula;
    int cont = 0;
    while ( leitura >> escolha >> virgula >> d ) {
        menu( minhaArvore, d, escolha );
        if ( escolha == 'i' && cont < QUANTIDADE_DE_INSERCAO ) {
            linhaCSV[cont].valor = d;
            linhaCSV[cont].insercao = CONTADOR_NO_INSERCAO;
            cont++;
        }
    }
}

void buscaValor( ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ], int posicao ) {
    menu( minhaArvore, linhaCSV[posicao].valor, 'b' );
    linhaCSV[posicao].busca = CONTADOR_NO_BUSCA;
}

void nivel( ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ], int posicao ) {
    linhaCSV[posicao].nivel = minhaArvore.Nivel( linhaCSV[posicao].valor );
}

void escreveArquivo( ofstream& escrita, ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    escrita << "valor,insercao,busca,nivel\n";
    for ( int i = 0; i < QUANTIDADE_DE_INSERCAO; i++ ) {
        buscaValor( minhaArvore, linhaCSV, i );
        nivel( minhaArvore, linhaCSV, i );
        escrita << linhaCSV[i].valor << ',' << linhaCSV[i].insercao << ',' << linhaCSV[i].busca << ',' << linhaCSV[i].nivel << "\n";
    }
}