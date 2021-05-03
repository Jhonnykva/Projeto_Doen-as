#include "ProjetoDoencas.h"

int main(int argc, char **argv)
{
// Verifica que a pasta de dados sempre  exista
#if defined(_WIN32)
    _mkdir(DATA_HOME);
#else
    mkdir(DATA_HOME, 0777);
#endif

    int status = -2;
    for (int i = 0; status == -2 && i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'o' && i + 1 < argc)
        {
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
            else if (strcmp(argv[i + 1], "buscarDoencas") == 0) // Buscar doencas por sintomas
            {
                status = buscarDoencas(argc, argv);
            }
            else if (strcmp(argv[i + 1], "addDoenca") == 0) // Adicionar doenca
            {
                status = addDoenca(argc, argv);
            }
            else if (strcmp(argv[i + 1], "rmDoenca") == 0) // Remover doenca
            {
                status = rmDoenca(argc, argv);
            }
            else if (strcmp(argv[i + 1], "addSintoma") == 0) // Adicionar Sintoma
            {
                status = addSintoma(argc, argv);
            }
            else if (strcmp(argv[i + 1], "rmSintoma") == 0) // Remover Sintoma
            {
                status = rmSintoma(argc, argv);
            }
            else
            {
                printf("Operação NÃO definida :(\n");
                imprimeOperacoes();
            }
        }
        else if (argv[i][0] == '-' && argv[i][1] == 'h')
        {
            imprimeOperacoes();
            break;
        }
    }
    putchar('\n');
    return status;
}

int lstDoencas(int argc, char **argv)
{
    printf("Listar Doencas\n");
    ArvoreDoencas *doencas = carregaArqArvDoencas();

    if (doencas->nDoencas > 0)
        imprimeDoencas(doencas, getNo(doencas->raiz, doencas));
    else
        printf("Nenhuma doença carregada. :(\n");

    liberarArvoreDoencas(doencas);
    return 0;
}

int genDoencas(int argc, char **argv)
{
    srand(time(NULL));
    // Obtem parametros
    int n = -1, print = 0;
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'n' && i + 1 < argc)
                sscanf(argv[++i], "%d", &n);
            else if (argv[i][1] == 'p')
                print = 1;
        }
    // Valida nro de doencas a gerar
    if (n <= 0)
    {
        printf("Número de doencas inválido. :(\n");
        exit(1);
    }
    if (n >= INT_MAX)
        n = INT_MAX / 2;
    // Cria estruturas de dados
    ArvoreDoencas *aDoencas = criaArvoreDoencas();
    THSintomas *tSintomas = criarTHSintomas(n + n / 5);

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
            adicionaSintoma(doencas[i], sintomas[(i + j * nSintD) % nSintomas]->nome);
            adicionaDoencaSintoma(sintomas[(i + j * nSintD) % nSintomas], doencas[i]->id);
        }
    }
    printf("Baralhando doenças...\n");
    // Desorganiza vetor
    for (i = 0; i < nDoencas; i++)
    {
        int j = rand() % nDoencas;
        Doenca *tmp = doencas[i];
        doencas[i] = doencas[j];
        doencas[j] = tmp;
    }
    // Insere doencas na arvore
    printf("Inserindo doenças...\n");
    for (i = 0; i < nDoencas; i++)
        inserirDoenca(doencas[i], aDoencas);

    // Persiste Arvore de doencas e Tabela de sintomas
    printf("Persistindo dados...\n");
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Imprime doencas geradas
    if (print)
        imprimeDoencas(aDoencas, getNo(aDoencas->raiz, aDoencas));
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
    // Obtem parametros
    int n = -1, id = -1;
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-id") == 0 && i + 1 < argc)
                sscanf(argv[++i], "%d", &id);
        }
    }
    if (id < 0)
    {
        printf("ID inválido. :(\n");
        return 1;
    }
    // Carrega arvore
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    // Busca doenca
    Doenca *doenca = getDoenca(id, aDoencas);
    // Imprime doenca caso exista
    if (doenca == NULL)
        printf("Doença %d não encontrada. :(\n", id);
    else
        imprimeDoenca(doenca);
    //  Libera memoria
    liberarArvoreDoencas(aDoencas);
    return 0;
}

int buscarDoencas(int argc, char **argv)
{
    printf("Buscar Doencas\n");
    // Obtem parametros
    int nSintomas = 0;                                                    // Nro. de sintomas
    char bSintomas[MAX_BUFFER_SINTOMAS + 1] = "",                         // Buffer de string de sintomas
        *aux = NULL;                                                      // Ponteiro auxiliar
    char **nomeSintomas = (char **)malloc(MAX_SINTOMAS * sizeof(char *)); // Vetor de sintomas
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-sintomas") == 0 && i + 1 < argc)
                strncat(bSintomas, argv[++i], MAX_NOME - 1);
        }
    }

    // Separa nome de sintomas
    aux = strtok(bSintomas, ",");
    while (aux != NULL && nSintomas < MAX_SINTOMAS - 1)
    {
        if (aux != NULL)
            nomeSintomas[nSintomas++] = aux;
        aux = strtok(NULL, ",");
    }

    // Valida nro de sintomas
    if (nSintomas <= 0)
    {
        printf("Sem sintomas válidos. :(\n");
        return 1;
    }
    // Carrega estruturas
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    THSintomas *tSintomas = carregaArqTHSintomas(-1);
    // Busca sintomas
    Sintoma **sintomas = (Sintoma **)malloc(nSintomas * sizeof(Sintoma *));
    int nSintVal = 0;
    for (int i = 0; i < nSintomas; i++)
    {
        Sintoma *sintoma = getSintoma(tSintomas, nomeSintomas[i]);

        if (sintoma != NULL)
            sintomas[nSintVal++] = sintoma;
    }

    int maxDoencas = MAX_SINTOMAS * nSintVal, nDoencas = 0;
    BuscaDoencas *doencas = (BuscaDoencas *)malloc(maxDoencas * sizeof(BuscaDoencas));
    // Busca doencas
    for (int i = 0; i < nSintVal; i++)
    {
        for (int j = 0; j < sintomas[i]->nDoencas; j++)
        {
            Doenca *doenca = getDoenca(sintomas[i]->doencaAssociada[j], aDoencas);
            if (doenca != NULL)
            {
                // Atualiza contador de nro de sintomas que levam a mesma doenca
                int k;
                for (k = 0; k < nDoencas; k++)
                {
                    if (doencas[k].doenca->id == doenca->id)
                        doencas[k].n += 1;
                }
                if (k >= nDoencas)
                {
                    if (nDoencas + 1 >= maxDoencas)
                    {
                        maxDoencas += maxDoencas / 2;
                        doencas = (BuscaDoencas *)realloc(doencas, maxDoencas * sizeof(BuscaDoencas));
                    }
                    doencas[k].doenca = doenca;
                    doencas[k].n = 1;
                    nDoencas++;
                }
            }
        }
    }

    printf("SINTOMAS %d/%d -> DOENCAS %d\n", nSintVal, nSintomas, nDoencas);
    // Utiliza heap-sort para organizar por nro de sintomas que contem a doenca
    heap_sort(doencas, nDoencas);
    for (int i = 0; i < nDoencas; i++)
    {
        printf("%d/%d ||\t", doencas[i].n, nSintomas);
        imprimeDoenca(doencas[i].doenca);
    }

    // Libera memoria
    liberaTHSintomas(tSintomas);
    liberarArvoreDoencas(aDoencas);
    free(nomeSintomas);
    free(sintomas);
    free(doencas);

    return 0;
}

int addDoenca(int argc, char **argv)
{
    // Obtem parametros
    int n = -1, nSintomas = 0;
    char nome[MAX_NOME] = "",
         bSintomas[MAX_BUFFER_SINTOMAS] = "",
         **nomeSintomas = (char **)malloc(MAX_SINTOMAS * sizeof(char *));
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-nome") == 0 && i + 1 < argc)
                strncat(nome, argv[++i], MAX_NOME - 1);
            else if (strcmp(argv[i], "-sintomas") == 0 && i + 1 < argc)
                strncat(bSintomas, argv[++i], MAX_BUFFER_SINTOMAS - 1);
        }
    }
    // Separa nome de sintomas
    char *aux = strtok(bSintomas, ",");
    while (aux != NULL && nSintomas < MAX_SINTOMAS)
    {
        if (aux != NULL)
            nomeSintomas[nSintomas++] = aux;
        aux = strtok(NULL, ",");
    }
    //Validacoes
    if (strlen(nome) <= 0)
    {
        printf("Nome inválido. :(\n");
        return 1;
    }
    else if (nSintomas <= 0)
    {
        printf("Ingrese pelo menos 1 sintoma. :(\n");
        return 1;
    }
    // Carrega estruturas
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    THSintomas *tSintomas = carregaArqTHSintomas(-1);
    // Cria doenca
    Doenca *doenca = criaDoenca(aDoencas->nDoencas, nome, 0, NULL);
    // Relaciona doenca com seus sintomas
    for (int i = 0; i < nSintomas; i++)
    {
        Sintoma *sintoma = getSintoma(tSintomas, nomeSintomas[i]);
        // Cria sintoma caso ele não exista
        if (sintoma == NULL)
        {
            sintoma = criaSintoma(nomeSintomas[i]);
            inserirSintoma(tSintomas, sintoma);
        }
        adicionaDoencaSintoma(sintoma, doenca->id);
        adicionaSintoma(doenca, sintoma->nome);
    }
    inserirDoenca(doenca, aDoencas);
    // Persiste dados
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Imprime doenca
    printf("Doenca registrada! :)\n");
    imprimeDoenca(doenca);
    //  Libera memoria
    liberarArvoreDoencas(aDoencas);
    liberaTHSintomas(tSintomas);
    return 0;
}

int rmDoenca(int argc, char **argv)
{
    // Obtem parametros
    int id = -1;
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
            if (strcmp(argv[i], "-id") == 0 && i + 1 < argc)
                sscanf(argv[++i], "%d", &id);
    }
    //Validacoes
    if (id < 0)
    {
        printf("ID %d inválido. :(\n", id);
        return 1;
    }
    // Carrega estruturas
    printf("Carregando doenças...\n");
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    THSintomas *tSintomas = carregaArqTHSintomas(-1);
    // Busca doenca
    Doenca *doenca = getDoenca(id, aDoencas);
    if (doenca == NULL)
    {
        printf("Doença %d não encontrada. :(\n", id);
        return 1;
    }
    // Remove relações sintoma -> doença
    for (int i = 0; i < doenca->nSintomas; i++)
    {
        Sintoma *sintoma = getSintoma(tSintomas, doenca->sintomas[i]);
        removerDoencaSintoma(sintoma, doenca->id);
    }
    // Remove Doença
    removerDoenca(aDoencas, doenca->id);
    // Persiste dados
    printf("Salvando mudanças...\n");
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Notificação
    printf("Doenca %d removida! :)\n", id);
    //  Libera memoria
    liberarArvoreDoencas(aDoencas);
    liberaTHSintomas(tSintomas);
    return 0;
}

int addSintoma(int argc, char **argv)
{
    // Obtem parametros
    int nDoencas = 0, doencas[MAX_DOENCAS];
    char nomeSintoma[MAX_NOME] = "", sDoencas[MAX_BUFFER_DOENCAS] = "";
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-nome") == 0 && i + 1 < argc)
                strncat(nomeSintoma, argv[++i], MAX_NOME - 1);
            else if (strcmp(argv[i], "-doencas") == 0 && i + 1 < argc)
                strncat(sDoencas, argv[++i], MAX_BUFFER_DOENCAS - 1);
        }
    }
    //Validacoes
    if (strlen(nomeSintoma) <= 0)
    {
        printf("Nome de sintoma inválido. :(\n");
        return 1;
    }
    // Separa id de doencas
    char *aux = strtok(sDoencas, ",");
    while (aux != NULL && nDoencas < MAX_DOENCAS)
    {
        int idTmp = -1;
        if (aux != NULL)
        {
            sscanf(aux, "%d", &idTmp);
            if (idTmp >= 0)
                doencas[nDoencas++] = idTmp;
        }
        aux = strtok(NULL, ",");
    }
    // Carrega estruturas
    printf("Carregando doenças & sintomas...\n");
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    THSintomas *tSintomas = carregaArqTHSintomas(-1);
    // Busca sintoma
    Sintoma *sintoma = getSintoma(tSintomas, nomeSintoma);
    // Valida sintoma
    if (sintoma != NULL)
    {
        printf("Sintoma \"%s\" já existe. :(\n", nomeSintoma);
        return 1;
    }
    sintoma = criaSintoma(nomeSintoma);
    // Cria relacoes
    for (int i = 0; i < nDoencas; i++)
    {
        Doenca *doenca = getDoenca(doencas[i], aDoencas);
        if (doenca != NULL)
        {
            adicionaSintoma(doenca, sintoma->nome);
            adicionaDoencaSintoma(sintoma, doenca->id);
        }
    }
    // Adiciona sintoma
    inserirSintoma(tSintomas, sintoma);
    // Persiste dados
    printf("Persistindo dados...\n");
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Notificação
    printf("Sintoma \"%s\" adicionado! :)\n", nomeSintoma);
    // Libera memoria
    liberarArvoreDoencas(aDoencas);
    liberaTHSintomas(tSintomas);
    return 0;
}

int rmSintoma(int argc, char **argv)
{
    // Obtem parametros
    char nomeSintoma[MAX_NOME] = "";
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
            if (strcmp(argv[i], "-nome") == 0 && i + 1 < argc)
                strncat(nomeSintoma, argv[++i], MAX_NOME - 1);
    }
    //Validacoes
    if (strlen(nomeSintoma) <= 0)
    {
        printf("Nome de sintoma inválido. :(\n");
        return 1;
    }
    // Carrega estruturas
    printf("Carregando doenças & sintomas...\n");
    ArvoreDoencas *aDoencas = carregaArqArvDoencas();
    THSintomas *tSintomas = carregaArqTHSintomas(-1);
    // Busca sintoma
    Sintoma *sintoma = getSintoma(tSintomas, nomeSintoma);
    // Valida sintoma
    if (sintoma == NULL)
    {
        printf("Sintoma \"%s\" NĀO existe. :(\n", nomeSintoma);
        return 1;
    }
    // Remove relações
    for (int i = 0; i < sintoma->nDoencas; i++)
    {
        Doenca *doenca = getDoenca(sintoma->doencaAssociada[i], aDoencas);
        if (doenca != NULL)
            removeSintoma(doenca, sintoma->nome);
    }
    // Remove sintoma
    removerSintoma(tSintomas, sintoma->nome);
    // Persiste dados
    printf("Persistindo dados...\n");
    persistirArvDoencas(aDoencas);
    salvarTHSSintoma(tSintomas);
    // Notificação
    printf("Sintoma \"%s\" removido! :)\n", nomeSintoma);
    // Libera memoria
    liberarArvoreDoencas(aDoencas);
    liberaTHSintomas(tSintomas);
    return 0;
}

void imprimeOperacoes()
{
    printf("OPERAÇŌES VÁLIDAS:\n");
    putchar('\n');
    printf("-> Inserção de uma doença\n");
    printf("\t -o addDoenca -nome <Nome da doença> -sintomas \"<Nome de sintomas separados por ',' sem espaços entre sintomas>\"\n");
    printf("-> Remoção de uma doença\n");
    printf("\t -o rmDoenca -id <ID da doença>\n");
    printf("-> Inserção de um sintoma\n");
    printf("\t -o addDoenca -nome \"<Nome da doença>\" -sintomas \"<Nome de sintomas separados por ',' sem espaços entre sintomas>\"\n");
    printf("-> Remoção de um sintoma\n");
    printf("\t -o rmDoenca -nome \"<Nome do sintoma>\"\n");
    printf("-> Busca de doença por ID\n");
    printf("\t -o buscarDoenca -id <ID da doença>\n");
    printf("-> Busca de doencas por sintomas\n");
    printf("\t -o buscarDoencas -sintomas \"<Nome de sintomas separados por ',' sem espaços entre sintomas>\"\n");
    printf("-> Geração de doenças\n");
    printf("\t -o genDoencas -n <Nro. de doenças a serem geradas>\n");
}

/**
 * HeapSort para busca de doencas p/ Sintomas
 * **/
int esquerda(int i)
{
    return (i * 2) + 1;
}

int direita(int i)
{
    return (i * 2) + 2;
}

void trocar(BuscaDoencas v[], int a, int b)
{
    BuscaDoencas aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void max_heapify(BuscaDoencas *v, int n, int i)
{
    int esq = esquerda(i),
        dir = direita(i),
        maior = i;

    if (esq < n && v[maior].n <= v[esq].n)
        maior = esq;

    if (dir < n && v[maior].n <= v[dir].n)
        maior = dir;

    if (maior != i)
    {
        trocar(v, i, maior);
        max_heapify(v, n, maior);
    }
}
void build_max_heap(BuscaDoencas *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(v, n, i);
}

void heap_sort(BuscaDoencas v[], int n)
{
    build_max_heap(v, n);
    for (int i = n - 1; i >= 1; i--)
    {
        trocar(v, 0, i);
        max_heapify(v, --n, 0);
    }
}