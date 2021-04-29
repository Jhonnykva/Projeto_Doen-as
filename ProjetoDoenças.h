#include "include_principal.h"
#include <time.h>
#include "Doenças.h"
#include "Sintomas.h"

typedef struct busca_doencas
{
  Doenca *doenca;
  int n;
} BuscaDoencas;

int lstDoencas(int argc, char **argv);
int genDoencas(int argc, char **argv);
int buscarDoenca(int argc, char **argv);
int buscarDoencas(int argc, char **argv);
void imprimeOperacoes();

int esquerda(int i);
int direita(int i);
void trocar(BuscaDoencas v[], int a, int b);
void max_heapify(BuscaDoencas *v, int n, int i);
void build_max_heap(BuscaDoencas *v, int n);
void heap_sort(BuscaDoencas v[], int n);