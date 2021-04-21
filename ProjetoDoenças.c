#include "ProjetoDoenças.h"
#include "Doenças.h"
#include "Menu.h"

int main(int argc, char **argv)
{
    unsigned int sintomas[3] = {1, 2, 3};

    ArvoreDoencas *a = criaArvoreDoencas();
    // ArvoreDoencas *a = carregaArvDoencas();

    // imprimeArvore(a, getNo(a->raiz, a), 0);
    // Doenca *d = NULL;
    // d = getDoenca(98, a);
    // imprimeDoenca(d);
    // d = getDoenca(14, a);
    // imprimeDoenca(d);
    // d = getDoenca(12, a);
    // imprimeDoenca(d);
    // liberarArvoreDoencas(a);
    // exit(0);
    // return 0;
    Doenca *doenca = NULL;
    // Loop para teste
    unsigned int ids[] = {10, 43, 1, 4, 7, 6, 2, 56, 12, 45, 65, 3, 14, 13, 11, 98, 79};
    int max_ids = 17;
    for (int i = 0; i < max_ids; i++)
    {
        doenca = criaDoenca(ids[i], "Doenca", 3, &sintomas);
        // imprimeDoenca(doenca);
        inserirDoenca(doenca, a);
        // imprimeArvore(a->raiz, 0);
        printf("\n====== %d inserido ======\n", ids[i]);
        putchar('\n');
        // for (int i = 0; i < a->nosAbertos->n; i++)
        //     printf(" %d", a->nosAbertos->nos[i]->id);
        // putchar('\n');
    }
    //imprimeArvore(a, getNo(a->raiz, a), 0);
    removerDoenca(a, 7);
    printf("\n====== Removido 7 ======\n");
    //imprimeArvore(a, getNo(a->raiz, a), 0);
    removerDoenca(a, 43);
    printf("\n====== Removido 43 ======\n");
    //imprimeArvore(a, getNo(a->raiz, a), 0);
    removerDoenca(a, 10);
    printf("\n====== Removido 10 ======\n");
    imprimeArvore(a, getNo(a->raiz, a), 0);
    putchar('\n');
    // for (int i = 0; i < a->nosAbertos->n; i++)
    //     printf(" %d", a->nosAbertos->nos[i]->id);
    // putchar('\n');
    // putchar('-');
    // putchar('\n');
    NoDoencas *teste = carregaArqNo(5);
    // eliminaDoenca(doenca);
    return 0;
}

//---------------------------- Associação da Tabela Hash com Árvore de doenças
