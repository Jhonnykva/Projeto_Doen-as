#include "include_principal.h"

/*** 
 * Estrutura de Doenças 
***/

#define MAX_NOME 25

typedef struct doenca
{
  unsigned int id;
  char nome[MAX_NOME];
  unsigned int n_sintomas;
  unsigned int *sintomas;

} Doença;

Doença *cria_doenca(unsigned int id, char *nome, unsigned int n_sintomas, unsigned int *sintomas);
void elimina_doenca(Doença *doença);
void imprime_doenca(Doença *doença);

/*** 
 * Árvore Doenças 
***/

#define T 10
#define MAX_CHAVES 2 * T - 1
#define MAX_FILHOS 2 * T

typedef struct nodo_doenca
{
  Doença *doença;
  int chave;              //número da chave
  int folha;              //bool
  int chaves[MAX_CHAVES]; //limite superior
  struct nodo_doenca *filhos[MAX_FILHOS];

} Arvore_Doencas;

Arvore_Doencas *cria_arvore_doencas();
Arvore_Doencas *inserir_doenca(Arvore_Doencas *a, Doença *doença);
Arvore_Doencas Busca_Doenca(Arvore_Doencas *a, int chave);
// void Remover_Doença(Arvore_Doencas *a, int chave);
// Arvore_Doencas *Balacear_Arvore_Doenca(Arvore_Doencas *a);