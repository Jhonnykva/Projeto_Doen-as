#include "ProjetoDoenças.h"

int main(int argc, char **argv)
{
    int status = -2;
    for (int i = 0; status == -2 && i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'o' && i + 1 < argc)
        {

            // printf("%s %d\n", argv[i + 1]), strcmp(argv[i + 1], "lstDoencas");

            if (strcmp(argv[i + 1], "lstDoencas") == 0) // Listar doencas
            {
                status = lstDoencas(argc, argv);
            }
            else if (strcmp(argv[i + 1], "genDoencas") == 0) // Gerar doencas
            {
                status = genDoencas(argc, argv);
            }
            else if (strcmp(argv[i + 1], "buscarDoenca") == 0) // Buscar doenca
            {
                status = buscarDoenca(argc, argv);
            }
            else
            {
                printf("Operação NÃO definida :(\n");
                imprimeOperacoes();
            }
        }
    }

    return status;
}

int lstDoencas(int argc, char **argv)
{
    printf("Listar Doencas\n");
    ArvoreDoencas *doencas = carregaArqArvDoencas();
    if (doencas->nDoencas > 0)
    {
        imprimeDoencas(doencas, getNo(doencas->raiz, doencas));
    }
    else
        printf("Nenhuma doença carregada. :(\n");

    liberarArvoreDoencas(doencas);
    return 0;
}
int genDoencas(int argc, char **argv)
{
    printf("Gerar Doencas\n");
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'o' && i + 1 < argc)
            {
            }
        }
    }
    return 0;
}
int buscarDoenca(int argc, char **argv)
{
    printf("Buscar Doencas\n");
    return 0;
}

void imprimeOperacoes()
{
    printf("-----------------------------\n");
    printf("ARGUMENTOS VÁLIDOS:\n");
    printf("-----------------------------\n");
    printf("op\t\tdesc\t[valores válidos]\n");
    printf("-----------------------------\n");
    printf("-o\t\tDefine a operação a executar\t[lstDoencas genDoencas buscarDoenca]\n");
}