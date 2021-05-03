#include "include_principal.h"

/*** 
 * Estrutura de Doencas 
***/

typedef struct doencas
{
  unsigned int id;          // Identificador de cada doença
  char nome[MAX_NOME];      // Nome da doença
  unsigned int nSintomas;   // Número de sintomas associados
  char **sintomas;          // Ponteiros para os sintomas

} Doenca;

//Funções de modelagem de doença
Doenca *criaDoenca(unsigned int id, char *nome, unsigned int nSintomas, char **sintomas);
void eliminaDoenca(Doenca *doenca);
void imprimeDoenca(Doenca *doenca);
void adicionaSintoma(Doenca *doenca, char *nomeSintoma);
void removeSintoma(Doenca *doenca, char *nomeSintoma);

/*** 
 * Árvore Doencas 
***/

#define T 1000
#define MAX_CHAVES 2 * T - 1
#define MIN_CHAVES T - 1
#define MAX_FILHOS 2 * T
#define MIN_FILHOS T
#define NO_DOENCA_VAZIO -1
#define DOENCAS_N_PRE "d-bt-"
#define DOENCAS_N_EXT ".no"
#define DOENCAS_CAB "doencas.btree"
typedef struct no_doencas
{
  int id;                     // Identificador único do nó
  int folha, nChaves;         // Bool
  Doenca *chaves[MAX_CHAVES]; // Limite superior
  // struct no_doencas *filhos[MAX_FILHOS];
  int filhos[MAX_FILHOS];
} NoDoencas;

#define V_SIZE 5
typedef struct v_nos
{
  int n;
  int max;
  NoDoencas **nos;
} Vnos;

typedef struct arvore_doenca
{
  int nDoencas; // Número de doenças
  int raiz;     // Raíz da árvore

  Vnos *nosAbertos; // Cache de nós abertos em memória
  int maxNoId;      // Número do último id de nó associado
} ArvoreDoencas;

// Criação
ArvoreDoencas *criaArvoreDoencas();
NoDoencas *criaNoArvoreDoencas(ArvoreDoencas *r, int folha);
void liberarNoArvoreDoencas(NoDoencas *no);
void liberarArvoreDoencas(ArvoreDoencas *a);

// A seguintes funções são funções de inserção
void inserirDoenca(Doenca *doenca, ArvoreDoencas *a);
NoDoencas *inserirNo(ArvoreDoencas *r, Doenca *doenca, NoDoencas *a);
void dividirFilho(ArvoreDoencas *r, int pos, NoDoencas *no, NoDoencas *filho);


// As seguintes funções tratam-se de todos os possíveis casos de remoção de uma árvore B
void removerDoenca(ArvoreDoencas *a, int id);
void remover(ArvoreDoencas *r, int id, NoDoencas *a);
void removerDeInterno(ArvoreDoencas *r, NoDoencas *a, int pos);
void removerDeFolha(ArvoreDoencas *r, NoDoencas *a, int pos);
void combinarFilhos(ArvoreDoencas *r, NoDoencas *a, int pos);
void DoadorDireita(ArvoreDoencas *r, NoDoencas *a, int pos);
void DoadorEsquerda(ArvoreDoencas *r, NoDoencas *a, int pos);

// Funções secundárias 
void imprimeArvore(ArvoreDoencas *r, NoDoencas *a, int h);
void imprimeDoencas(ArvoreDoencas *r, NoDoencas *a);
int isCheio(NoDoencas *a);
int isVazio(NoDoencas *a);
int isFolha(NoDoencas *a);
Doenca *getDoenca(int id, ArvoreDoencas *a);
Doenca *getChave(int id, NoDoencas *n, ArvoreDoencas *a);

// As seguintes funções carregam os nós de arquivos e os mantém
ArvoreDoencas *carregaArvDoencas();
NoDoencas *getNo(int idNo, ArvoreDoencas *a);
void persistirArvDoencas(ArvoreDoencas *a);
void persistirNo(int id, ArvoreDoencas *a);
void liberarNosAbertos(ArvoreDoencas *a);
void liberarNo(int id, ArvoreDoencas *a);
int persisteNoArq(NoDoencas *no);
int persisteCabDoencas(ArvoreDoencas *a);
NoDoencas *carregaArqNo(int id);
ArvoreDoencas *carregaArqArvDoencas();