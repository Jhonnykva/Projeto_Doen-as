#include "include_principal.h"

/**
 * Sintomas
 * **/

typedef struct sintomas
{
    char nome[MAX_NOME];  // Nome do sintoma
    int nDoencas;         // Número de doenças associadas
    int *doencaAssociada; // Doenças associadas
} Sintoma;

Sintoma *criaSintoma(char *nomeSintoma);
void adicionaDoencaSintoma(Sintoma *sintoma, int idDoenca);
void removerDoencaSintoma(Sintoma *sintoma, int idDoenca);
void liberaSintoma(Sintoma *sintoma);

/**
 * Tabela Hash de sintomas
 * **/

#define SINTOMAS_ARQ "sintomas.ths"
#define FLAG_SINT_RM "SRM" // Bandeira de elemento eliminado
#define M_THS 5000000
typedef struct tabelaHashSintoma
{
    Sintoma **sintomas;
    int M; //número de posições
    int N; //número de itens

} THSintomas;

THSintomas *criarTHSintomas(int M);
int funcaoHashSintoma(char *nome_sintoma, int M);
void inserirSintoma(THSintomas *H, Sintoma *sintoma);
void removerSintoma(THSintomas *H, char *nomeSintoma);
void liberaTHSintomas(THSintomas *H);

int isFull(THSintomas *H);
int verificaSintomaExistente(char sintoma[], THSintomas *H);
void imprimirTHCompleta(THSintomas *H);
Sintoma *getSintoma(THSintomas *H, char *nomeSintoma);

int salvarTHSSintoma(THSintomas *H);
THSintomas *carregaArqTHSintomas();
