#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------ Árvore Doenças
#define T 10

typedef struct node{
    int n;  //número da chave
    int folha; //bool
    int chaves[2*T-1];  //limite superior
    struct node *filhos[2*T];

}Arvore_Doencas;

Arvore_Doencas Busca_Doenca(Arvore_Doencas *a, int chave);
Arvore_Doencas *Inserir_Doenca(Arvore_Doencas *a, int chave);
void Remover_Doença(Arvore_Doencas *a, int chave);
void Balacear_Arvore_Doenca(Arvore_Doencas *a);

//----------------------------- Tabela Hash Sintomas

typedef struct node{
    int k; //chave chave pesquisa
    struct node *next;
}No_THash;

typedef struct hash{
    int N_Entradas;
    int N_Chaves_Armazenadas
}


