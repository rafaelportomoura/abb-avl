#include "Menu.hpp"
#include <fstream>

void leArquivo( ifstream& leitura, ArvoreABB& minhaArvore ) {
    Dado d;
    char escolha;
    char virgula;
    while ( leitura >> escolha >> virgula >> d ) {
        menu( minhaArvore, d, escolha );
    }
}