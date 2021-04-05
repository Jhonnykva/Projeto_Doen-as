#include "include_principal.h"

/*** 
 * Estrutura de Doenças 
***/

#define MAX_NOME 25

typedef struct doencas
{
  unsigned int id;
  char nome[MAX_NOME];
  unsigned int n_sintomas;
  unsigned int *sintomas;

} Doenca;

Doenca *cria_doenca(unsigned int id, char *nome, unsigned int n_sintomas, unsigned int *sintomas);
void elimina_doenca(Doenca *doenca);
void imprime_doenca(Doenca *doenca);

/*** 
 * Árvore Doenças 
***/

#define T 2
#define MAX_CHAVES 2 * T - 1
#define MIN_CHAVES T - 1
#define MAX_FILHOS 2 * T
#define MIN_FILHOS T

typedef struct no_doencas
{
  int folha, n_chaves;        //bool
  Doenca *chaves[MAX_CHAVES]; //limite superior
  struct no_doencas *filhos[MAX_FILHOS];
} No_Doencas;

typedef struct arvore_doenca
{
  int n_doencas; //nro doencas
  No_Doencas *raiz;
} Arvore_Doencas;

Arvore_Doencas *cria_arvore_doencas();
Arvore_Doencas *inserir_doenca(Doenca *doenca, Arvore_Doencas *a);

No_Doencas *cria_no_arvore_doencas(int folha);
No_Doencas *inserir_no(Doenca *doenca, No_Doencas *a);
void dividir_filho(int pos, No_Doencas *no, No_Doencas *filho);
void imprime_arvore(No_Doencas *a, int h);
Doenca *Busca_Doenca(Arvore_Doencas *a, int chave);
// void Remover_Doença(Arvore_Doencas *a, int chave);
// Arvore_Doencas *Balacear_Arvore_Doenca(Arvore_Doencas *a);
// int testaFolha(Arvore_Doencas *a);