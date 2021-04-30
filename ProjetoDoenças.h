#include "include_principal.h"
#include "Doenças.h"
#include "Sintomas.h"

/**
 * Estrutura de busca de doencas
 * **/
typedef struct busca_doencas
{
  Doenca *doenca; // Ponteiro doença
  int n;          // Nro. de coincidencias
} BuscaDoencas;

/**
 * Funções relacionadas as operacoes
 * **/
int lstDoencas(int argc, char **argv);
int genDoencas(int argc, char **argv);
int buscarDoenca(int argc, char **argv);
int buscarDoencas(int argc, char **argv);
int addDoenca(int argc, char **argv);
int rmDoenca(int argc, char **argv);
void imprimeOperacoes();

/**
 * HeapSort para busca de doencas p/ Sintomas
 * **/
int esquerda(int i);
int direita(int i);
void trocar(BuscaDoencas v[], int a, int b);
void max_heapify(BuscaDoencas *v, int n, int i);
void build_max_heap(BuscaDoencas *v, int n);
void heap_sort(BuscaDoencas v[], int n);