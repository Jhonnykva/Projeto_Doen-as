#include "Doenças.h"

/*** 
 * Estrutura de Doenças 
***/

Doença *cria_doenca(unsigned int id, char *nome, unsigned int n_sintomas, unsigned int *sintomas)
{
    // Verifica que os dados sejam válidos
    if (nome == NULL)
    {
        printf("ERROR: Doença::cria_doenca: O nome não pode ser NULL\n");
        exit(1);
    }
    else if (sintomas == NULL)
    {
        printf("ERROR: Doença::cria_doenca: O array de sintomas não pode ser NULL\n");
        exit(1);
    }

    Doença *doença = (Doença *)malloc(sizeof(Doença));
    doença->id = id;
    strcpy(doença->nome, nome); // Falta tratar o tamanho do nome
    doença->n_sintomas = n_sintomas;
    doença->sintomas = sintomas;

    return doença;
}
void elimina_doenca(Doença *doença)
{
    // Falta decidir se alocar nome e sintomas dinamicamente/estaticamente
    free(doença);
};

void imprime_doenca(Doença *doença)
{
    if (doença != NULL)
    {
        printf("%05d - %s \n", doença->id, doença->nome);
    }
}

/*** 
 * Árvore Doenças 
***/

Arvore_Doencas *cria_arvore_doencas()
{
    return NULL;
};

Arvore_Doencas Busca(Arvore_Doencas *a, int chave)
{
    //busca alguma chave
    // int i = 0;
    // while ((i < a->n) && (k > a->chave[i]))
    // {
    //     i++;
    // }
    // if ((i < a->n) && (k == a->chave[i]))
    // {
    //     printf("Encontrado");
    // }
    // else if (a->folha)
    // {
    //     printf("Nao-Encontrado");
    // }
    // else
    // {
    //     return Busca(a->filhos[i], k);
    // }
}
