


void menu( ArvoreABB& minhaArvore, Dado chave, char escolha ) {
    switch ( escolha ) {
    case 'i':
        minhaArvore.insere( chave );
        break;
    case 'r':
        minhaArvore.remove( chave );
        break;
    case 'b':
        minhaArvore.Busca( chave );
        break;
    case 'q':
        break;
    default:
        cout << "Comando Invalido!\n";
    }
}