#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 10

typedef struct node{
    int n;  //número de chaves
    int folha; //bool
    int chaves[2*T-1];  //limite superior
    struct node *filhos[2*T];

}Arvore_Doencas;

Arvore_Doencas Busca(Arvore_Doencas *a, int chave);
Arvore_Doencas *Inserir(Arvore_Doencas *a, int chave);


