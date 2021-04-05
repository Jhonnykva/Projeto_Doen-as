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
        a = inserir_doenca(doenca, a);
        imprime_arvore(a->raiz, 0);
        printf("\n====== %d inserido ======\n", ids[i]);
    }

    elimina_doenca(doenca);
    return 0;
}

//---------------------------- Associação da Tabela Hash com Árvore de doenças
