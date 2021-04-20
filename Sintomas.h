#include "include_principal.h"


typedef struct sintomas{

    char nome[30];//nome do sintoma
    char *doencaAssociada[10];// inserir aqui doenças que estão assiciadas ao sintoma
                              //associar no máximo 10 sintomas
}Sintoma;

typedef struct tabelaHashSintoma{
    Sintoma **estrutura_sintoma;
    int M;//número de posições
    int N;//número de itens

}THSintomas;

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
char *gerarNomeSintoma(const char nomeSintoma[]);
int *vetor_linhas(FILE* arquivo);
void imprimirDadosArquivoSintoma(int linhaInicial, int linhaFinal, FILE *arquivo, int *v);

void *carregarTHSintoma(const char nome[]);//falta implementar

//--------OUTAS FUNÇÕES
void relacionarDoencaSintoma();
