#include "ProjetoDoenças.h"
#include "Doenças.h"
int main(int argc, char **argv)
{
    unsigned int sintomas[3] = {1, 2, 3};
    Doença *doença = NULL;
    doença = cria_doenca(1, "Doença", 3, &sintomas);
    imprime_doenca(doença);
    elimina_doenca(doença);
    return 0;
}

//---------------------------- Associação da Tabela Hash com Árvore de doenças
