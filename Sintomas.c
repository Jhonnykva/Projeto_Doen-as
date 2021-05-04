#include "Sintomas.h"

/**
 * Sintomas
 * **/

/** 
 * Essa função é encarregada de alocar memoria para um novo sintoma.
 * Parámetros: 
 *      - char* nomeSintoma: nome do sintoma a ser criado.
 * Valor de retorno: retorna o ponteiro do sintoma criado.
 * */
Sintoma *criaSintoma(char *nomeSintoma)
{
    Sintoma *sintoma = (Sintoma *)malloc(sizeof(Sintoma));
    sintoma->nDoencas = 0;
    sintoma->doencaAssociada = NULL;
    strcpy(sintoma->nome, nomeSintoma);
    return sintoma;
}

/** 
 * Essa função é encarregada de associar uma doença ao sintoma especificado.
 * Parámetros: 
 *      - Sintoma* sintoma: ponteiro do sintoma.
 *      - int idDoenca: identificador da doença a ser associada.
 * */
void adicionaDoencaSintoma(Sintoma *sintoma, int idDoenca)
{
    // Verifica que o ponteiro seja valido
    if (sintoma == NULL)
        return;
    if (sintoma->nDoencas == 0) // CASO: não tenha nenhum sintoma
    {
        sintoma->nDoencas += 1;
        sintoma->doencaAssociada = (int *)malloc(sizeof(int));
        sintoma->doencaAssociada[0] = idDoenca;
    }
    else // CASO: já tenha algum sintoma
    {
        sintoma->nDoencas += 1;
        sintoma->doencaAssociada = (int *)realloc(sintoma->doencaAssociada, sintoma->nDoencas * sizeof(int));
        sintoma->doencaAssociada[sintoma->nDoencas - 1] = idDoenca;
    }
}

/** 
 * Essa função é encarregada de desassociar uma doença do sintoma especificado.
 * Parámetros: 
 *      - Sintoma* sintoma: ponteiro do sintoma.
 *      - int idDoenca: identificador da doença a ser desassociada.
 * */
void removerDoencaSintoma(Sintoma *sintoma, int idDoenca)
{
    // Verifica que o ponteiro seja valido
    if (sintoma == NULL)
        return;
    int pos = -1;
    do
    {
        pos++;
    } while (pos < sintoma->nDoencas && sintoma->doencaAssociada[pos] != idDoenca);

    if (pos < sintoma->nDoencas)
    {
        sintoma->doencaAssociada[pos] = -1;
        sintoma->nDoencas -= 1;
        for (int i = pos; i < sintoma->nDoencas; i++)
            sintoma->doencaAssociada[i] = sintoma->doencaAssociada[i + 1];
        sintoma->doencaAssociada = (int *)realloc(sintoma->doencaAssociada, sintoma->nDoencas * sizeof(int));
    }
}

/** 
 * Essa função é encarregada de liberar a memoria ocupada por um sintoma.
 * Parámetros: 
 *      - Sintoma* sintoma: ponteiro do sintoma a ser liberado.
 * */
void liberaSintoma(Sintoma *sintoma)
{
    // Libera vetor de doencas
    free(sintoma->doencaAssociada);
    // Libera sintoma
    free(sintoma);
}

/**
 * Tabela Hash de sintomas
 * **/

/** 
 * Essa função é encarregada de gerar o hash a partir do nome do sintoma,
 * utilizando o método de Horner.
 * Parámetros: 
 *      - char * nomeS: nome do sintoma.
 *      - int M: tamanho da tabela hash. 
 * Valor de retorno: retorna o hash gerado a partir do nome.
 * */
int funcaoHashSintoma(char nomeS[], int M)
{
    int i, h = nomeS[0];
    for (i = 1; nomeS[i] != '\0'; i++)
        h = (h * 256 + nomeS[i]) % M;
    return h;
}

/** 
 * Essa função é encarregada de alocar memoria e inicializar as 
 * variáveis da tabela hash de sintomas.
 * Parámetros: 
 *      - int M: tamanho da tabela a ser criada.
 * Valor de retorno: retorna o ponteiro da tabela de sintomas criada.
 * */
THSintomas *criarTHSintomas(int M)
{
    //Cria a tabela hash e retorna-a
    THSintomas *novaTabela = (THSintomas *)malloc(sizeof(THSintomas));
    novaTabela->M = M;
    novaTabela->N = 0;
    novaTabela->sintomas = (Sintoma **)malloc(M * sizeof(Sintoma *));
    // Inicia ponteiros da lista
    for (int i = 0; i < novaTabela->M; i++)
        novaTabela->sintomas[i] = NULL;
    return novaTabela;
}

/** 
 * Essa função é encarregada de verificar se existe e inserir um novo sintoma à tabela.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela de sintomas.
 *      - Sintoma* sintoma: ponteiro do sintoma a ser inserido.
 * */
void inserirSintoma(THSintomas *H, Sintoma *sintoma)
{
    // Validacoes
    if (getSintoma(H, sintoma->nome) != NULL)
    {
        printf("Nao e possível inserir sintoma, pois este sintoma ja existe\n");
        exit(1);
    }
    else if (isFull(H))
    {
        printf("Nao e possível inserir sintoma, pois a tabela esta cheia\n");
        exit(1);
    }
    // Obtem local de inserção
    int localInsercao = funcaoHashSintoma(sintoma->nome, H->M);
    // Aumenta número de itens
    H->N++;
    // Tratamento de colisão
    while (H->sintomas[localInsercao] != NULL &&
           strcmp(H->sintomas[localInsercao]->nome, FLAG_SINT_RM) != 0)
        localInsercao = (localInsercao + 1) % (H->M);

    // Adiciona sintoma à tabela
    H->sintomas[localInsercao] = sintoma;
#if DEBUG
    printf("Sintoma %s inserido\n", sintoma->nome);
#endif
}

/** 
 * Essa função é encarregada de eliminar o sintoma especificado da tabela.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela onde o sintoma será removido.
 *      - char* nomeSintoma: nome do sintoma a ser removido.
 * */
void removerSintoma(THSintomas *H, char *nomeSintoma)
{
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    // Verifica se o sintoma existe
    if (H->sintomas[fH] == NULL)
    {
        printf("\nSintoma nao removido porque não existe.\n");
        return;
    }

    //REMOVENDO O SINTOMA DA TABELA
    liberaSintoma(H->sintomas[fH]);
    H->sintomas[fH] = criaSintoma(FLAG_SINT_RM);
    H->N--;
#if DEBUG
    printf("Sintoma %s removido\n", nomeSintoma);
#endif
}

/** 
 * Essa função é encarregada liberar a memoria ocupada pela 
 * tabela de sintomas especificada.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela a ser liberada.
 * */
void liberaTHSintomas(THSintomas *H)
{
    for (int i = 0; i < H->M; i++)
    {
        if (H->sintomas[i] != NULL) // Libera sintomas
            liberaSintoma(H->sintomas[i]);
    }
    // Libera vetor de sintomas
    free(H->sintomas);
    // Libera tabela
    free(H);
}

/** 
 * Essa função é encarregada de verificar se um sintoma já existe 
 * na tabela especificada.
 * Parámetros: 
 *      - char* sintoma: nome do sintoma a ser pesquisado.
 *      - THSintomas *H: ponteiro da tabela no qual o sintoma será pesquisado.
 * Valor de retorno:
 *      - 1 caso o sintoma exista.
 *      - 0 caso o sintoma não exista.
 * */
int verificaSintomaExistente(char *sintoma, THSintomas *H)
{
    // Verifica se sintoma existe
    if ((H->sintomas[funcaoHashSintoma(sintoma, H->M)] != NULL) && (strcpy(sintoma, H->sintomas[funcaoHashSintoma(sintoma, H->M)]->nome) == 0))
        return 1;
    else
        return 0;
}

/** 
 * Essa função é encarregada de verificar se a tabela encontra-se cheia.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela a ser verificada.
 * Valor de retorno: 
 *      - 1 caso a tabela encontre-se cheia.
 *      - 0 caso a tabela não encontre-se cheia.
 * */
int isFull(THSintomas *H)
{
    // Verifica se a tabela está cheia
    return H->N >= H->M;
}

/** 
 * Essa função foi utilizada no desenvolvimento para imprimir na consola todos
 * os sintomas da tabela, para verificar o funcionamento das operações desenvolvidas.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela a ser impressa.
 * */
void imprimirTHCompleta(THSintomas *H)
{
    //Esta função imprime a tabela hash completa
    printf("\n\nTabela Completa: \n");
    for (int i = 0; i < H->M; i++)
    {
        if (H->sintomas[i] != NULL)
        {
            printf("%d - %s -", i, H->sintomas[i]->nome);
            for (int j = 0; j < H->sintomas[i]->nDoencas; j++)
                printf(" %d", H->sintomas[i]->doencaAssociada[j]);
            printf("\n");
        }
    }
}

/** 
 * Essa função é encarregada de pesquisar un sintoma especificado
 * na tabela de sintomas.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela onde será pesquisado o sintoma.
 *      - char *nomeSintoma: nome do sintoma a ser pesquisado.
 * Valor de retorno: retorna o ponteiro do sintoma pesquisado; ou NULL caso não exista.
 * */
Sintoma *getSintoma(THSintomas *H, char *nomeSintoma)
{
    if (nomeSintoma == NULL)
    {
        printf("ERROR:getSintoma: nome de sintoma nulo. :(\n");
        exit(1);
    }
    // Obtem posicao inicial
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    // Verifica se a posicao inicial contem um ponteiro valido
    if (H->sintomas[fH] != NULL)
    {
        int i = 0;
        // Percorre tabela até encontrar o sintoma
        while (i < H->M && H->sintomas[fH + i] != NULL)
        {
            if (strcmp(nomeSintoma, H->sintomas[fH + i]->nome) == 0)
                return H->sintomas[fH + i]; // Retorna ponteiro do sintoma
            i++;
        }
    }
    return NULL;
}

/** 
 * Essa função é encarregada de salvar todos os sintomas contidos na tabela
 * de sintomas no seu arquivo.
 * Parámetros: 
 *      - THSintomas* H: ponteiro da tabela a ser salvada.
 * Valor de retorno: 
 *      - 1 caso o arquivo seja salvado corretamente.
 *      - 0 caso o arquivo não seja salvado corretamente.
 * */
int salvarTHSSintoma(THSintomas *H)
{
#if DEBUG
    printf("Persistindo THSintomas\n");
#endif
    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "";
    strcat(fName, DATA_HOME);
    strcat(fName, SINTOMAS_ARQ);
    strcat(fName, "\0");
    // Remove arquivo anterior
    remove(fName);
    FILE *arq = fopen(fName, "w");
    // Verifica se o arquivo foi aberto
    if (arq == NULL)
    {
        printf("ERROR:salvarTHSSintoma: não foi possível abrir o arquivo \"%s\".\n", fName);
        exit(1);
    }
    // Salva informacoes base da tabela hash
    fprintf(arq, "%d %d\n", H->N, H->M);
    // Chaves
    for (int i = 0; i < H->M; i++)
    {
        Sintoma *sintoma = H->sintomas[i];
        if (sintoma != NULL)
        {
            fprintf(arq, "%s\n", sintoma->nome);
            fprintf(arq, "%d %d\n", i, sintoma->nDoencas);
            for (int j = 0; j < sintoma->nDoencas; j++)
                fprintf(arq, "%d\n", sintoma->doencaAssociada[j]);
        }
    }
    return fclose(arq) == 0;
}

/** 
 * Essa função é encarregada de carregar em memoria a tabela de 
 * sintomas desde seu arquivo; ou criar uma nova tabela caso o arquivo não exista.
 * Parámetros: 
 *      - int _M: tamanho da tabela a ser criada caso o arquivo não exista.
 * Valor de retorno: retorna o ponteiro da tabela de sintomas carregada/criada.
 * */
THSintomas *carregaArqTHSintomas(int _M)
{
    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "";
    strcat(fName, DATA_HOME);
    strcat(fName, SINTOMAS_ARQ);
    strcat(fName, "\0");

    FILE *arq = fopen(fName, "r");
    // Verifica se o arquivo existe
    if (arq == NULL)
        return _M > 0 ? criarTHSintomas(_M) : NULL;

    // Obtem informacoes base da tabela
    int N = -1, M = -1;
    fscanf(arq, "%d %d\n", &N, &M);
    if (_M > 0 && _M != M)
    {
        printf("ERROR:carregaArqTHSintomas inconsistencia entre o tamanho esperado e obtido da tabela hash %d-%d\n", _M, M);
        exit(1);
    }
    // Aloca memoria para a tabela
    THSintomas *sintomas = criarTHSintomas(M);
    sintomas->N = N;

    // Obtem Chaves
    for (int n = 0; n < N; n++)
    {
        int i = -1;
        char buffer[MAX_NOME] = "";
        // Carrega nome
        buffer[0] = '\0';
        fgets(buffer, MAX_NOME, arq);
        buffer[strcspn(buffer, "\n")] = 0;
        Sintoma *sintoma = criaSintoma(buffer);
        // Carrega indice e nro de doencas
        fscanf(arq, "%d %d\n", &i, &sintoma->nDoencas);
        // Carrega doencas associadas
        sintoma->doencaAssociada = (int *)malloc(sintoma->nDoencas * sizeof(int));
        for (int j = 0; j < sintoma->nDoencas; j++)
            fscanf(arq, "%d\n", &sintoma->doencaAssociada[j]);
        // Coloca sintoma no seu indice
        sintomas->sintomas[i] = sintoma;
    }
    fclose(arq);
    return sintomas;
}
