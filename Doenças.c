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
    doenca->id = id;
    strcpy(doenca->nome, nome); // Falta tratar o tamanho do nome
    doenca->n_sintomas = n_sintomas;
    doenca->sintomas = sintomas;

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

Arvore_Doencas *inserir_doenca(Arvore_Doencas *a, Doença *doenca){
/*
     if(a==NULL){
        a= (Arvore_Doencas*)malloc(sizeof(Arvore_Doencas));
        a->chave=doenca->id;//trocar id por string futuramente
        a->folha=1;//é uma folha por enquanto
        for(int i=0; i<MAX_CHAVES; i++){
            a->chaves[i]=NULL;//garante que  todos os ponteiros para 
                              //subárvores estejam nulos e prontos para uso
        }
        return a;
    }
 
    int i=0, j=0;
    while((i<MAX_CHAVES) && (doenca->id > a->chaves[i])){
        i++;
    }//percorre até achar o ponto em que a doença deve ser inserida
    while(a->folha==0){
        inserir_doenca(a->filhos[i], doenca->id);
    }//desce até o último nível da árvore

    //CASO 1 - árvore possui espaço para colocar folha
    if(a->chaves[MAX_CHAVES]==NULL){


    }//testa se a subárvore não está cheia, vendo se há elemento na última posição das chaves


    //CASO 2 - árvore possui espaço para colocar folha e necessita de um rearranjo*/
}