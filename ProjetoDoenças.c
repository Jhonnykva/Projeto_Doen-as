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
    srand(time(NULL));
    // Obtem parametros
    int n = -1;
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'n' && i + 1 < argc)
                sscanf(argv[i + 1], "%d", &n);
        }
    // Valida nro de doencas a gerar
    if (n <= 0)
    {
        printf("Número de doencas inválido. :(\n");
        exit(1);
    }
    if (n >= INT32_MAX)
    {
        n = INT32_MAX / 2;
    }
    // Cria estruturas de dados
    ArvoreDoencas *aDoencas = criaArvoreDoencas();
    THSintomas *tSintomas = criarTHSintomas(n * 2);

    int nSintomas = n, nDoencas = n;
    printf("Gerando %d sintomas.\n", n);
    // Gera sintomas
    Sintoma **sintomas = (Sintoma **)malloc((nSintomas - 1) * 2 * sizeof(Sintoma *));
    int i = -1;
    for (i = 0; i < nSintomas; i++)
    {
        // Gera nome sintoma
        char nome[MAX_NOME] = "";
        sprintf(nome, "Sintoma %d", i);
        // Cria sintoma
        sintomas[i] = criaSintoma(nome);
        // Insere sintoma na tabela
        inserirSintoma(tSintomas, sintomas[i]);
    }
    printf("Gerando %d doencas.\n", n);
    // Gera doenças
    Doenca **doencas = (Doenca **)malloc(n * sizeof(Doenca *));
    for (i = 0; i < nSintomas; i++)
    {
        int nSintD = MIN_SINTOMAS + rand() % (MAX_SINTOMAS + 1);
        char nome[MAX_NOME] = "", label[7] = "";
        // Gera nome
        if (nSintD == MIN_SINTOMAS)
            strcpy(label, "LEVE");
        else if (nSintD == MAX_SINTOMAS)
            strcpy(label, "GRAVE");
        else
            strcpy(label, "NORMAL");
        sprintf(nome, "Doenca %d (%s)", i, label);
        // Cria doenca
        doencas[i] = criaDoenca(i, nome, 0, NULL);
        // Relaciona doenca e sintomas
        adicionaSintoma(doencas[i], sintomas[i]->nome);
        adicionaDoencaSintoma(sintomas[i], doencas[i]->id);
        for (int j = 1; j < nSintD; j++)
        {
            adicionaSintoma(doencas[i], sintomas[(i + j * nSintD) % nSintomas]);
            adicionaDoencaSintoma(sintomas[(i + j * nSintD) % nSintomas], doencas[i]->id);
        }
        // Insere doenca na arvores
        // inserirDoenca(doencas[i], aDoencas);
    }
    for (i = 0; i < nDoencas; i++)
    {
        int j = rand() % nDoencas;
        Doenca *tmp = doencas[i];
        doencas[i] = doencas[j];
        doencas[j] = tmp;
    }
    for (i = 0; i < nDoencas; i++)

    {
        printf("INSERINDO %d\n", doencas[i]->id);
        inserirDoenca(doencas[i], aDoencas);
    }

    // Persiste Arvore de doencas e Tabela de sintomas
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Imprime doencas geradas
    // imprimeDoencas(aDoencas, getNo(aDoencas->raiz, aDoencas));
    // Libera estruturas
    liberarArvoreDoencas(aDoencas);
    liberaTHSintomas(tSintomas);
    // Libera vetores de ajuda
    free(sintomas);
    free(doencas);
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
    // TESTES
    // THSintomas *sintomas = criarTHSintomas(100);
    // inserirSintoma(sintomas, "Sintoma A");
    // inserirSintoma(sintomas, "Sintoma B");
    // inserirSintoma(sintomas, "Sintoma C");
    // inserirSintoma(sintomas, "Sintoma D");

    // Sintoma *a = getSintoma(sintomas, "Sintoma A");
    // adicionaDoencaSintoma(a, 40);
    // adicionaDoencaSintoma(a, 41);
    // adicionaDoencaSintoma(a, 42);
    // adicionaDoencaSintoma(a, 43);
    // adicionaDoencaSintoma(a, 44);
    // removerDoencaSintoma(a, 41);

    // Sintoma *b = getSintoma(sintomas, "Sintoma B");
    // adicionaDoencaSintoma(b, 40);
    // adicionaDoencaSintoma(b, 41);
    // adicionaDoencaSintoma(b, 42);
    // removerDoencaSintoma(b, 29);
    // removerDoencaSintoma(b, 1);
    // adicionaDoencaSintoma(b, 42);

    // salvarTHSSintoma(sintomas);

    // THSintomas *sintomas2 = carregaArqTHSintomas(100);
    // imprimirTHCompleta(sintomas);
    // imprimirTHCompleta(sintomas2);
    // liberaTHSintomas(sintomas);
    // liberaTHSintomas(sintomas2);

    // ArvoreDoencas *a = criaArvoreDoencas();
    // Doenca *doenca = NULL;
    // // Loop para teste
    // unsigned int ids[] = {10, 43, 1, 4, 7, 6, 2, 56, 12, 45, 65, 3, 14, 13, 11, 98, 79};
    // int max_ids = 17;
    // for (int i = 0; i < max_ids; i++)
    // {
    //     char **sintomas = (char **)malloc(3 * sizeof(char *));
    //     sintomas[0] = (char *)malloc(MAX_NOME * sizeof(char));
    //     strcpy(sintomas[0], "Sintoma A\0");
    //     sintomas[1] = (char *)malloc(MAX_NOME * sizeof(char));
    //     strcpy(sintomas[1], "Sintoma B\0");
    //     sintomas[2] = (char *)malloc(MAX_NOME * sizeof(char));
    //     strcpy(sintomas[2], "Sintoma C\0");
    //     doenca = criaDoenca(ids[i], "Doenca A A", 3, sintomas);
    //     inserirDoenca(doenca, a);
    //     printf("\n====== %d inserido ======\n", ids[i]);
    //     putchar('\n');
    // }

    // ArvoreDoencas *a = carregaArvDoencas();
    // imprimeDoencas(a, getNo(a->raiz, a));
    // Doenca *d = getDoenca(43, a);
    // strcpy(d->nome, "Super Doença");
    // adicionaSintoma(d, "Sintoma M");
    // removeSintoma(d, "Sintoma B");
    // persistirArvDoencas(a);
    // imprimeDoencas(a, getNo(a->raiz, a));
    // liberarArvoreDoencas(a);
}