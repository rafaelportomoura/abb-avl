
int CONTADOR_NO_BUSCA = 0;
int CONTADOR_NO_INSERCAO = 0;
int CONTADOR_NO_REMOCAO = 0;

bool isINSERCAO = false;
bool isREMOCAO = false;

const int QUANTIDADE_DE_INSERCAO_E_REMOCAO = 100;

const string NOME_ARQUIVO_TESTE = "../arquivos/entrada.csv";
const string NOME_ARQUIVO_REMOCAO = "../arquivos/remocao.csv";
const string NOME_ARQUIVO_ESCRITA = "../arquivos/avl.csv";

struct LINHA_CSV {
    Dado valor;
    int busca;
    int insercao;
    int remocao;
};