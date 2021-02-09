/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa dado na forma umDado/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>
#include <fstream>
typedef int Dado;


using namespace std;
#include "config.hpp"




class noh {
    friend class avl;
    private:
    Dado elemento;
    noh* esq;
    noh* dir;
    unsigned altura;
    public:
    noh( const Dado& umDado ) :
        elemento( umDado ), esq( NULL ), dir( NULL ), altura( 1 ) {}
    ~noh() {}
    int fatorBalanceamento();
    int informarAltura( noh* umNoh ) { if ( umNoh == NULL ) { return 0; } else { return  umNoh->altura; } }

    void atualizaAltura();
};

int noh::fatorBalanceamento() {
    int e, d;
    e = informarAltura( esq );
    d = informarAltura( dir );
    return e - d;
}

void noh::atualizaAltura() {
    int altArvEsq = informarAltura( esq );
    int altArvDir = informarAltura( dir );
    altura = 1 + max( altArvEsq, altArvDir );
}

class avl {
    friend ostream& operator<<( ostream& output, avl& arvore );
    private:
    noh* raiz;
    // percorrimento em ordem da árvore
    void percorreEmOrdemAux( noh* atual, int nivel );
    // funções auxiliares para remoção
    noh* encontraMenor( noh* raizSub );
    noh* removeMenor( noh* raizSub );
    // funções auxiliares para inserção e remoção usando método recursivo
    // retorna o nó para ajustar o pai ou o raiz
    noh* insereAux( noh* umNoh, const Dado& umDado );
    noh* removeAux( noh* umNoh, Dado chave );
    // métodos para manutenção do balanceamento
    noh* rotacaoEsquerda( noh* umNoh );
    noh* rotacaoDireita( noh* umNoh );
    noh* arrumaBalanceamento( noh* umNoh );
    // busca, método iterativo
    noh* buscaAux( Dado chave );
    // função auxiliar do destrutor, usa percorrimento pós-ordem
    void destruirRecursivamente( noh* umNoh );
    void imprimirDir( const std::string& prefixo, const noh* meuNoh );
    void imprimirEsq( const std::string& prefixo, const noh* meuNoh, bool temIrmao );
    int levantamentoAux( noh* umNoh, string marca );
    void buscaLevantamento( string marca, int& lev, noh* atual );
    public:
    avl() { raiz = NULL; }
    ~avl();
    void imprimir();
    // inserção e remoção são recursivos
    void insere( const Dado& umDado );
    void remove( Dado chave );
    // inserção e remoção, métodos recursivos
    // busca retorna uma cópia do objeto armazenado
    Dado busca( Dado chave );
    // efetua levantamento de quantos produtos existem de uma dada marca
    int levantamento( string marca );
};

// destrutor
avl::~avl() {
    destruirRecursivamente( raiz );
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente( noh* umNoh ) {
    if ( umNoh->esq == NULL && umNoh->dir == NULL ) {
        delete umNoh;
    }
    else {
        if ( umNoh->esq != NULL ) {
            destruirRecursivamente( umNoh->esq );
        }
        if ( umNoh->dir != NULL ) {
            destruirRecursivamente( umNoh->dir );
        }
    }
}

void avl::insere( const Dado& umDado ) {
    CONTADOR_NO_INSERCAO = 0;
    isINSERCAO = true;
    raiz = insereAux( raiz, umDado );
    isINSERCAO = false;
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux( noh* umNoh, const Dado& umDado ) {
    noh* novo;
    novo = new noh( umDado );
    CONTADOR_NO_INSERCAO++;
    if ( umNoh == NULL ) {
        return novo;
    }
    else {
        if ( umDado < umNoh->elemento ) {
            umNoh->esq = insereAux( umNoh->esq, umDado );
        }
        else if ( umDado > umNoh->elemento ) {
            umNoh->dir = insereAux( umNoh->dir, umDado );
        }
        else {
            throw runtime_error( "Erro na insercao: chave repetida!" );
        }
    }
    return arrumaBalanceamento( umNoh );
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento( noh* umNoh ) {
    if ( umNoh != NULL ) {
        umNoh->atualizaAltura();
        int bal = umNoh->fatorBalanceamento();
        if ( bal < -1 ) {
            if ( umNoh->dir->fatorBalanceamento() > 0 )
                umNoh->dir = rotacaoDireita( umNoh->dir );

            return rotacaoEsquerda( umNoh );
        }
        else if ( bal > 1 ) {
            if ( umNoh->esq->fatorBalanceamento() < 0 )
                umNoh->esq = rotacaoEsquerda( umNoh->esq );

            return rotacaoDireita( umNoh );
        }
    }
    return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda( noh* umNoh ) {
    noh* aux;
    aux = umNoh->dir;
    umNoh->dir = aux->esq;
    if ( umNoh == raiz ) raiz = aux;
    aux->esq = umNoh;
    umNoh->atualizaAltura();
    aux->atualizaAltura();
    if (isINSERCAO) CONTADOR_NO_INSERCAO++;
    if (isREMOCAO) CONTADOR_NO_REMOCAO++;
    return aux;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita( noh* umNoh ) {
    noh* aux;
    aux = umNoh->esq;
    umNoh->esq = aux->dir;
    if ( umNoh == raiz ) raiz = aux;
    aux->dir = umNoh;
    umNoh->atualizaAltura();
    aux->atualizaAltura();
    if ( isINSERCAO ) CONTADOR_NO_INSERCAO++;
    if ( isREMOCAO ) CONTADOR_NO_REMOCAO++;
    return aux;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux( Dado chave ) {
    noh* busca;
    busca = raiz;
    CONTADOR_NO_BUSCA = 0;
    while ( busca != NULL ) {
        CONTADOR_NO_BUSCA++;
        if ( chave == busca->elemento ) {
            return busca;
        }
        else if ( chave < busca->elemento ) {
            busca = busca->esq;
        }
        else {
            busca = busca->dir;
        }
    }
    return busca;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
Dado avl::busca( Dado chave ) {
    noh* resultado = buscaAux( chave );
    if ( resultado != NULL )
        return resultado->elemento;
    else
        throw runtime_error( "Erro na busca: elemento não encontrado!" );
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor( noh* raizSub ) {
    if ( raizSub->esq == NULL ) {
        return raizSub;
    }
    else {
        return encontraMenor( raizSub->esq );
    }
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor( noh* raizSub ) {
    if ( raizSub->esq == NULL ) {
        return raizSub->dir;
    }
    else {
        raizSub->esq = removeMenor( raizSub->esq );
        return arrumaBalanceamento( raizSub );
    }
}

// remoção recursiva
void avl::remove( Dado chave ) {
    CONTADOR_NO_REMOCAO = 0;
    isREMOCAO = true;
    raiz = removeAux( raiz, chave );
    isREMOCAO = false;
}

noh* avl::removeAux( noh* umNoh, Dado chave ) {
    if ( umNoh == NULL ) {
        throw runtime_error( "Erro na remoção: elemento não encontrado!" );
    }
    noh* raizSubArvore;
    raizSubArvore = umNoh;
    CONTADOR_NO_REMOCAO++;
    if ( chave < umNoh->elemento ) {
        umNoh->esq = removeAux( umNoh->esq, chave );
    }
    else if ( chave > umNoh->elemento ) {
        umNoh->dir = removeAux( umNoh->dir, chave );
    }
    else {
        if ( umNoh->esq == NULL ) {
            raizSubArvore = umNoh->dir;
        }
        else if ( umNoh->dir == NULL ) {
            raizSubArvore = umNoh->esq;
        }
        else {
            raizSubArvore = encontraMenor( umNoh->dir );
            raizSubArvore->dir = removeMenor( umNoh->dir );
            raizSubArvore->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento( raizSubArvore );
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::percorreEmOrdemAux( noh* atual, int nivel ) {
    if ( atual != NULL ) {
        int proxNivel = nivel + 1;
        percorreEmOrdemAux( atual->esq, proxNivel );
        cout << atual->elemento << "/" << nivel << ' ' << endl;
        percorreEmOrdemAux( atual->dir, proxNivel );
    }
}

ostream& operator<<( ostream& output, avl& arvore ) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir( const std::string& prefixo, const noh* meuNoh ) {
    if ( meuNoh != nullptr ) {
        std::cout << prefixo
            << "└d─"
            << "(" << meuNoh->elemento << "," << ")"
            << std::endl;

  // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    ", meuNoh->esq, meuNoh->dir == nullptr );
        imprimirDir( prefixo + "    ", meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq( const std::string& prefixo, const noh* meuNoh, bool temIrmao ) {
    if ( meuNoh != nullptr ) {
        std::cout << prefixo;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if ( temIrmao )
            std::cout << "└e─";
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento << "," << ")"
            << std::endl;

  // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   ", meuNoh->esq, meuNoh->dir == nullptr );
        imprimirDir( prefixo + "│   ", meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir() {
    if ( this->raiz != nullptr ) {
        std::cout << "(" << this->raiz->elemento << "," << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " ", this->raiz->esq, this->raiz->dir == nullptr );
        imprimirDir( " ", this->raiz->dir );
    }
    else
        std::cout << "*arvore vazia*" << std::endl;
}

#include "Menu_Arquivos/Arquivos.hpp"

int main() {
    avl arvore;
    Dado umDado;
    char operacao;
    ifstream leituraEntrada(NOME_ARQUIVO_TESTE.c_str());
    LINHA_CSV linhaCSV[QUANTIDADE_DE_INSERCAO_E_REMOCAO];
    leEntrada(leituraEntrada,arvore,linhaCSV);
    atribuiBuscaAoCSV(arvore, linhaCSV);
    ifstream leituraRemocao(NOME_ARQUIVO_REMOCAO.c_str());
    leRemocao(leituraRemocao,arvore,linhaCSV);
    ofstream escrita( NOME_ARQUIVO_ESCRITA.c_str());
    escreveArquivo(escrita,arvore,linhaCSV);

    do{
        cout<<"Deseja fazer alguma alteracao?\n";
        cin>>operacao;
        if (operacao == 'i' ||operacao == 'r' || operacao == 'b')
        cin>>umDado;
        menu(arvore, operacao,umDado);
    } while (operacao!='f');
    
    

    return 0;
}
