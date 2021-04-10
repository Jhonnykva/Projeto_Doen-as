#include "include_principal.h"

FILE *cria_arquivo(char* nome);
int  *vetor_informar_linhas(FILE* arquivo);
void imprimir_dados(int linha_inicial, int linha_final);
FILE *inserir_dados(char *dados);
FILE *remover_dados(char *dados);
char *conersao_int_char(int i);
int conversao_char_int(char *c);
FILE *gerencia_arquivo(FILE arquivo);

