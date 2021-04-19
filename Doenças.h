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
#define NO_DOENCA_VAZIO -1
#define DOENCAS_N_PRE "d-bt-"
#define DOENCAS_N_EXT ".no"
#define DOENCAS_CAB "doencas.btree"
typedef struct no_doencas
{
  int id;                     // Identificador unico do no
  int folha, n_chaves;        //bool
  Doenca *chaves[MAX_CHAVES]; //limite superior
  // struct no_doencas *filhos[MAX_FILHOS];
  int filhos[MAX_FILHOS];
} No_Doencas;

#define V_SIZE 5
typedef struct v_nos
{
  int n;
  int max;
  No_Doencas **nos;
} V_Nos;

typedef struct arvore_doenca
{
  int n_doencas; // Nro. de doencas
  int raiz;      // Raiz da arvore

  V_Nos *nos_abertos; // Cache de nos abertos em memoria
  int max_no_id;      // Nro do ultimo id de no asignado
} Arvore_Doencas;

// Criação
Arvore_Doencas *cria_arvore_doencas();
No_Doencas *cria_no_arvore_doencas(Arvore_Doencas *r, int folha);
void liberar_no_arvore_doencas(No_Doencas *no);
void liberar_arvore_doencas(Arvore_Doencas *a);

// Inserção
void inserir_doenca(Doenca *doenca, Arvore_Doencas *a);
No_Doencas *inserir_no(Arvore_Doencas *r, Doenca *doenca, No_Doencas *a);
void dividir_filho(Arvore_Doencas *r, int pos, No_Doencas *no, No_Doencas *filho);

// Remoção :(
void remover_doenca(Arvore_Doencas *a, int id);
void remover(Arvore_Doencas *r, int id, No_Doencas *a);
void remover_de_interno(Arvore_Doencas *r, No_Doencas *a, int pos);
void remover_de_folha(Arvore_Doencas *r, No_Doencas *a, int pos);
void combinar_filhos(Arvore_Doencas *r, No_Doencas *a, int pos);
void doador_direita(Arvore_Doencas *r, No_Doencas *a, int pos);
void doador_esquerda(Arvore_Doencas *r, No_Doencas *a, int pos);

// Varias
void imprime_arvore(Arvore_Doencas *r, No_Doencas *a, int h);
int is_cheio(No_Doencas *a);
int is_vazio(No_Doencas *a);
int is_folha(No_Doencas *a);

// Carga/Persistencia de nos;
Arvore_Doencas *carregar_arvore_doencas();
No_Doencas *get_no(int id_no, Arvore_Doencas *a);
void persistir_arvore_doencas(Arvore_Doencas *a);
void persistir_no(int id, Arvore_Doencas *a);
void liberar_nos_abertos(Arvore_Doencas *a);
void liberar_no(int id, Arvore_Doencas *a);
int persiste_no_arquivo(No_Doencas *no);
int persiste_cab_doencas(Arvore_Doencas *a);
No_Doencas *carrega_arquivo_no(int id);
Arvore_Doencas* carrega_arq_a_doencas();