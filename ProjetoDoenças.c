#include "ProjetoDoenças.h"
#include "Doenças.h"
int main(int argc, char **argv)
{
    unsigned int sintomas[3] = {1, 2, 3};

    Arvore_Doencas *a = cria_arvore_doencas();
    Doenca *doenca = NULL;
    // Loop para teste
    unsigned int ids[] = {10, 43, 1, 4, 7, 6, 2, 56, 12, 45, 65, 3, 14, 13, 11, 98, 79};
    int max_ids = 17;
    for (int i = 0; i < max_ids; i++)
    {
        doenca = cria_doenca(ids[i], "Doenca", 3, &sintomas);
        // imprime_doenca(doenca);
        inserir_doenca(doenca, a);
        // imprime_arvore(a->raiz, 0);
        printf("\n====== %d inserido ======\n", ids[i]);
    }
    imprime_arvore(a->raiz, 0);
    remover_doenca(a, 7);
    printf("\n====== Removido 7 ======\n");
    imprime_arvore(a->raiz, 0);
    remover_doenca(a, 43);
    printf("\n====== Removido 43 ======\n");
    imprime_arvore(a->raiz, 0);
    remover_doenca(a, 10);
    printf("\n====== Removido 10 ======\n");
    imprime_arvore(a->raiz, 0);

    elimina_doenca(doenca);
    return 0;
}

//---------------------------- Associação da Tabela Hash com Árvore de doenças
