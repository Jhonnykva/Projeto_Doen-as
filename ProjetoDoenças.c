#include "ProjetoDoenças.h"
#include "Doenças.h"
int main(int argc, char **argv)
{
    unsigned int sintomas[3] = {1, 2, 3};
    Arvore_Doencas *a = cria_arvore_doencas();
    Doença *doença = NULL;
    for (int i = 0; i < 100; i++)
    {
        doença = cria_doenca(i, "Doença", 3, &sintomas);
        imprime_doenca(doença);
        a = inserir_doenca(doença, a);
        printf("END %d\n", a == NULL);
    }

    elimina_doenca(doença);
    return 0;
}

//---------------------------- Associação da Tabela Hash com Árvore de doenças
