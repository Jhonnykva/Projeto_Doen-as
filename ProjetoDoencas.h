/** 
 *   ____            _           _          ____                                 
 *  |  _ \ _ __ ___ (_) ___  ___| |_ ___   |  _ \  ___   ___ _ __   ___ __ _ ___ 
 *  | |_) | '__/ _ \| |/ _ \/ __| __/ _ \  | | | |/ _ \ / _ \ '_ \ / __/ _` / __|
 *  |  __/| | | (_) | |  __/ (__| || (_) | | |_| | (_) |  __/ | | | (_| (_| \__ \
 *  |_|   |_|  \___// |\___|\___|\__\___/  |____/ \___/ \___|_| |_|\___\__,_|___/
 *                |__/                                              )_)   
 * UTFPR - CT - CSF30 - Projeto da Matéria de Estrutura de Dados II 
 * Autores:
 *    - Jhonny Kristyan Vaz-Tostes de Assis | jhonnykva@gmail.com
 *    - Matheus Kunnen Ledesma | matheusl.2000@alunos.utfpr.edu.br
 * Data: Maio-2021 (Período 2020/2) 
 * Github repo: https://github.com/Jhonnykva/Projeto_Doen-as
 * **/

#include "include_principal.h"
#include "Doencas.h"
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
int addSintoma(int argc, char **argv);
int rmSintoma(int argc, char **argv);
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