#include "Menu.hpp"
#include <fstream>

void leArquivoEntrada( ifstream& leitura, ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    Dado d;
    char escolha;
    char virgula;
    int cont = 0;
    while ( leitura >> escolha >> virgula >> d ) {
        menu( minhaArvore, d, escolha );
        if ( escolha == 'i' && cont < QUANTIDADE_DE_INSERCAO_E_REMOCAO ) {
            linhaCSV[cont].valor = d;
            linhaCSV[cont].insercao = CONTADOR_NO_INSERCAO;
            cont++;
        }
    }
}


void leArquivoRemocao( ifstream& leitura, ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    Dado d;
    char escolha;
    char virgula;
    while ( leitura >> escolha >> virgula >> d ) {
        menu( minhaArvore, d, escolha );
        if ( escolha == 'r' ) {
            for ( int i = 0; i < QUANTIDADE_DE_INSERCAO_E_REMOCAO; i++ ) {
                if ( linhaCSV[i].valor == d ) {
                    linhaCSV[i].remocao = CONTADOR_NO_REMOCAO;
                }

            }
        }
    }
}

void buscaValor( ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ], int posicao ) {
    menu( minhaArvore, linhaCSV[posicao].valor, 'b' );
    linhaCSV[posicao].busca = CONTADOR_NO_BUSCA;
}


void atualizaLinhaCSV( ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    for ( int i = 0; i < QUANTIDADE_DE_INSERCAO_E_REMOCAO; i++ ) {
        buscaValor( minhaArvore, linhaCSV, i );
    }
}

void escreveArquivo( ofstream& escrita, ArvoreABB& minhaArvore, LINHA_CSV linhaCSV[ ] ) {
    escrita << "valor,insercao,busca,remocao\n";
    for ( int i = 0; i < QUANTIDADE_DE_INSERCAO_E_REMOCAO; i++ ) {
        escrita << linhaCSV[i].valor << ',' << linhaCSV[i].insercao << ',' << linhaCSV[i].busca << ',' << linhaCSV[i].remocao << "\n";
    }
}


void buscaValoresInexistentes( ifstream& leitura, ArvoreABB& minhaArvore, ofstream& escrita ) {
    Dado umDado;
    char operacao;
    char virgula;
    escrita << "valor,busca\n";
    while ( leitura >> operacao >> virgula >> umDado ) {
        menu( minhaArvore, umDado, operacao );
        escrita << umDado << ',' << CONTADOR_NO_BUSCA << endl;
    }
}
