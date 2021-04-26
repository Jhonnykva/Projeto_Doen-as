#include "include_principal.h"

#define MAX_N_SINTOMA 50
typedef struct sintomas
{
    char nome[MAX_N_SINTOMA]; //nome do sintoma
    int *doencaAssociada;     // inserir aqui doenças que estão assiciadas ao sintoma
                              //associar no máximo 10 sintomas
    int nDoencas;
} Sintoma;

Sintoma *criaSintoma(char *nomeSintoma);
void adicionaDoencaSintoma(Sintoma *sintoma, int idDoenca);
void liberaSintoma(Sintoma *sintoma);

#define SINTOMAS_ARQ "sintomas.ths"

typedef struct tabelaHashSintoma
{
    Sintoma **estrutura_sintoma;
    int M; //número de posições
    int N; //número de itens

} THSintomas;

//--------TABELA HASH - FUNÇÕES PRINCIPAIS
THSintomas *criarTHSintomas(int M);
int funcaoHashSintoma(char nome_sintoma[], int M);
void inserirSintoma(THSintomas *H, char nomeSintoma[]);
void removerSintoma(THSintomas *H, char nomeSintoma[]);
void buscarSintoma(THSintomas *H, char nomeSintoma[]);
void freeTHSintomas(THSintomas *H);

//--------TABELA HASH - FUNÇÕES SECUNDÁRIAS
int isFull(THSintomas *H);
int verificaSintomaExistente(char sintoma[], THSintomas *H);
void imprimirTHCompleta(THSintomas *H);

//--------FUNÇÕES DE ARQUIVOS
/*//Não usadas mais, mas ainda não retirei por precaução, caso necessite delas denovo
char *gerarNomeSintoma(const char nomeSintoma[]);
int *vetor_linhas(FILE* arquivo);
void imprimirDadosArquivoSintoma(int linhaInicial, int linhaFinal, FILE *arquivo, int *v);*/
void carregarTHSintoma(THSintomas *H);
int salvarTHSSintoma(THSintomas *h);
THSintomas *carregaArqTHSintomas();

//--------OUTAS FUNÇÕES
void relacionarDoencaSintoma();
