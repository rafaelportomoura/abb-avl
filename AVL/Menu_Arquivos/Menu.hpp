void menu( avl& arvore, char operacao, Dado umDado ) {
    try {
        switch ( operacao ) {
        case 'i': // Inserir recursivamente
            // objeto recebe chave, nome do produto, marca, quantidade disponível
            arvore.insere( umDado );
            break;
        case 'r': // Remover recursivamente
            arvore.remove( umDado );
            break;
        case 'b': // Buscar
            umDado = arvore.busca( umDado ); // escrever dados do produto
            cout << "Elemento buscado: " << umDado << endl;
            break;
        case 'e': // Escrever tudo (em ordem)
            cout << arvore;
            break;
        case 'f': // Finalizar execução
            break;
        default:
            cout << "Comando invalido!\n";
        }
    }
    catch ( runtime_error& e ) {
        cout << e.what() << endl;
    }
}
