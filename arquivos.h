#include "include_principal.h"

FILE *cria_arquivo();
int  *vetor_linhas(FILE* arquivo);
void imprimir_dados(int linha_inicial, int linha_final, FILE *arquivo);
FILE *inserir_dados(const char *dados, FILE *arquivo);
FILE *remover_dados(char *dados);
char *conersao_int_char(int i);
int conversao_char_int(char *c);
void gerencia_arquivo(FILE *arquivo,const char nome[30]);

