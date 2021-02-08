
int CONTADOR_NO_BUSCA = 0;
int CONTADOR_NO_INSERCAO = 0;

const int QUANTIDADE_DE_INSERCAO = 30;
const string NOME_ARQUIVO_TESTE = "entrada.csv";
const string NOME_ARQUIVO_ESCRITA = "abb.csv";

struct LINHA_CSV {
    Dado valor;
    int busca;
    int insercao;
    int nivel;
};