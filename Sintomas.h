#include "include_principal.h"

/**
 * Sintomas
 * **/

typedef struct sintomas
{
    char nome[MAX_NOME];  // Nome do sintoma
    int nDoencas;         // Nro. doencas associadas
    int *doencaAssociada; // Doencas associadas
} Sintoma;

Sintoma *criaSintoma(char *nomeSintoma);
void adicionaDoencaSintoma(Sintoma *sintoma, int idDoenca);
void removerDoencaSintoma(Sintoma *sintoma, int idDoenca);
void liberaSintoma(Sintoma *sintoma);
/**
 * Tabela Hash de sintomas
 * **/

#define SINTOMAS_ARQ "sintomas.ths"
#define FLAG_SINT_RM "SRM"
typedef struct tabelaHashSintoma
{
    Sintoma **estrutura_sintoma;
    int M; //número de posições
    int N; //número de itens

} THSintomas;

//--------TABELA HASH - FUNÇÕES PRINCIPAIS
THSintomas *criarTHSintomas(int M);
int funcaoHashSintoma(char nome_sintoma[], int M);
void inserirSintoma(THSintomas *H, Sintoma *sintoma);
void removerSintoma(THSintomas *H, char nomeSintoma[]);
void buscarSintoma(THSintomas *H, char nomeSintoma[]);
Sintoma *getSintoma(THSintomas *H, char *nomeSintoma);
void liberaTHSintomas(THSintomas *H);

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
