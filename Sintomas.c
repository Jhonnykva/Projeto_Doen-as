#include "Sintomas.h"

/**
 * Sintomas
 * **/

Sintoma *criaSintoma(char *nomeSintoma)
{
    Sintoma *sintoma = (Sintoma *)malloc(sizeof(Sintoma));
    sintoma->nDoencas = 0;
    sintoma->doencaAssociada = NULL;
    strcpy(sintoma->nome, nomeSintoma);
    return sintoma;
}
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

int funcaoHashSintoma(char nomeS[], int M)
{
    int i, h = nomeS[0];
    for (i = 1; nomeS[i] != '\0'; i++)
        h = (h * 256 + nomeS[i]) % M;
    return h;
}

THSintomas *criarTHSintomas(int M)
{
    THSintomas *novaTabela = (THSintomas *)malloc(sizeof(THSintomas));
    novaTabela->M = M;
    novaTabela->N = 0;
    novaTabela->estrutura_sintoma = (Sintoma **)malloc(M * sizeof(Sintoma *));
    // Inicia ponteiros da lista
    for (int i = 0; i < novaTabela->M; i++)
        novaTabela->estrutura_sintoma[i] = NULL;
    return novaTabela;
}

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
    // Aumenta nro de items
    H->N++;
    // Tratamento de colisão
    while (H->estrutura_sintoma[localInsercao] != NULL &&
           strcmp(H->estrutura_sintoma[localInsercao]->nome, FLAG_SINT_RM) != 0)
        localInsercao = (localInsercao + 1) % (H->M);

    // Adiciona sintoma à tabela
    H->estrutura_sintoma[localInsercao] = sintoma;
#if DEBUG
    printf("Sintoma %s inserido\n", sintoma->nome);
#endif
}

void removerSintoma(THSintomas *H, char *nomeSintoma)
{
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    // Verifica se o sintoma existe
    if (H->estrutura_sintoma[fH] == NULL)
    {
        printf("\nSintoma nao removido porque não existe.\n");
        return;
    }
    //remove(gerarNomeSintoma(nomeSintoma));
    //remove está comentado pois só funciona em linux

    //REMOVENDO O SINTOMA DA TABELA
    liberaSintoma(H->estrutura_sintoma[fH]);
    H->estrutura_sintoma[fH] = criaSintoma(FLAG_SINT_RM);
    H->N--;
#if DEBUG
    printf("Sintoma %s removido\n", nomeSintoma);
#endif
    //REMOVENDO SINTOMA DO ARQUIVO DE NOMES DE SINTOMAS
    //AJUSTAR DEPOIS
    // FILE *arquivoNomeSintoma = fopen("ArquivoNomeSintoma.txt", "a+");
    // char aux[100] = "", dadosArquivo[500] = "", fnSintoma[30] = "";
    // int i = 0, j = 0, posicao1 = 0, posicao2, contAux = 0;

    // strcat(fnSintoma, nomeSintoma);
    // strcat(fnSintoma, ".txt");
    // strcat(fnSintoma, "\0");
    /*
        if(arquivoNomeSintoma==NULL){
            printf("ArquivoNomeSintoma.txt não foi aberto");
        }

        while(fgets(aux, 100, arquivoNomeSintoma)!=NULL){
            strcat(dadosArquivo, aux);
        }*/
    /*while(fnSintoma[contAux]!='\0'){
            contAux++;
        }
        for(i=0; dadosArquivo[i]!=NULL; i++){

            if(dadosArquivo[i] == fnSintoma[j]){
                posicao1=i;
                while(dadosArquivo[i] == fnSintoma[j]){
                    i++;
                    j++;
                    if(j==contAux){
                        posicao2=i;
                    }
                }
            }
            if(posicao2!=0){
                break;
            }
            else{
                i=posicao1;
            }
        }
        while(dadosArquivo[posicao2+1]!=NULL){
            dadosArquivo[posicao1]=dadosArquivo[posicao2+1];
            posicao1++;
            posicao2++;
        }
        dadosArquivo[posicao2+1]='\0';*/
    //printf("\n%s", dadosArquivo);

    // fclose(arquivoNomeSintoma);
    //arquivoNomeSintoma = fopen("ArquivoNomeSintoma.txt", "w");
    //fputs(dadosArquivo, arquivoNomeSintoma);

    //REMOVENDO DELETANDO ARQUIVO ESPECÍFICO DO SINTOMA

    // remove(fnSintoma);
}

void buscarSintoma(THSintomas *H, char *nomeSintoma)
{
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    int encontrado = 0;
    if (H->estrutura_sintoma[fH] == NULL)
    {
        printf("\nSintoma %s nao existente", nomeSintoma);
    }
    else
    {
        while (H->estrutura_sintoma[fH] != NULL || strcmp(nomeSintoma, H->estrutura_sintoma[fH]->nome) != 0)
        {
            if (strcmp(nomeSintoma, H->estrutura_sintoma[fH]->nome) == 0)
            {
                encontrado = 1;
                break;
            }
            else
            {
                fH++;
            }
        }
    }
    if (encontrado == 1)
    {
        //ABRINDO ARQUIVO
        /*FILE *arquivoSintoma = fopen(gerarNomeSintoma(nomeSintoma), "r");
        if(arquivoSintoma!= NULL)
            printf("\narquivo de %s aberto", nomeSintoma);
        int *vetorNLinhas = vetor_linhas(arquivoSintoma);*/

        //MOSTRANDO DADOS DO SINTOMA
        printf("\n\nnome: %s", H->estrutura_sintoma[fH]->nome);
        printf("\nDoencas associadas: ");
        //imprimirDadosArquivoSintoma(1, sizeof(vetorNLinhas)/4, arquivoSintoma, vetorNLinhas);
        //printf("\n");
        //fclose(arquivoSintoma);
    }
}

void liberaTHSintomas(THSintomas *H)
{
    for (int i = 0; i < H->M; i++)
    {
        if (H->estrutura_sintoma[i] != NULL) // Libera sintomas
            liberaSintoma(H->estrutura_sintoma[i]);
    }
    // Libera vetor de sintomas
    free(H->estrutura_sintoma);
    // Libera tabela
    free(H);
}

int verificaSintomaExistente(char *sintoma, THSintomas *H)
{
    //verifica se um dado sintoma já existe verificando o seu nome
    if ((H->estrutura_sintoma[funcaoHashSintoma(sintoma, H->M)] != NULL) && (strcpy(sintoma, H->estrutura_sintoma[funcaoHashSintoma(sintoma, H->M)]->nome) == 0))
        return 1;
    //trocar o valor do strcpm assim que possuir acesso ao nome
    else
        return 0;
}

int isFull(THSintomas *H)
{
    return H->N >= H->M;
}

void imprimirTHCompleta(THSintomas *H)
{
    printf("\n\nTabela Completa: \n");
    for (int i = 0; i < H->M; i++)
    {
        if (H->estrutura_sintoma[i] != NULL)
        {
            printf("%d - %s -", i, H->estrutura_sintoma[i]->nome);
            for (int j = 0; j < H->estrutura_sintoma[i]->nDoencas; j++)
                printf(" %d", H->estrutura_sintoma[i]->doencaAssociada[j]);
            printf("\n");
        }
    }
}

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
    if (H->estrutura_sintoma[fH] != NULL)
    {
        int i = 0;
        // Percorre tabela até encontrar o sintoma
        while (i < H->M && H->estrutura_sintoma[fH + i] != NULL)
        {
            if (strcmp(nomeSintoma, H->estrutura_sintoma[fH + i]->nome) == 0)
                return H->estrutura_sintoma[fH + i]; // Retorna ponteiro do sintoma
            i++;
        }
    }
    return NULL;
}

// Carga/Persistencia THSintomas
int salvarTHSSintoma(THSintomas *h)
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
    fprintf(arq, "%d %d\n", h->N, h->M);
    // Chaves
    for (int i = 0; i < h->M; i++)
    {
        Sintoma *sintoma = h->estrutura_sintoma[i];
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
        sintomas->estrutura_sintoma[i] = sintoma;
    }
    fclose(arq);
    return sintomas;
}

/*char *gerarNomeSintoma(const char nomeSintoma[]){
    //adiciona ".txt" à string do nome do sintoma para fazer um arquivo
    char nome[30] = "";
    strcat(nome, nomeSintoma);
    strcat(nome, ".txt");
    return nome;
}*/
/*
void imprimirDadosArquivoSintoma(int linhaInicial, int linhaFinal, FILE *arquivo, int* v){
    //esta função imprime os dados do começo de uma linha até o final de outra linha
    char c[1000];

    if(linhaFinal<linhaInicial){
        printf("ERROR: valor de linhas invalidos.\n");
    }
    fscanf(arquivo, "%s", c);
    printf("\n");
    for(int i=v[linhaInicial];i<(v[linhaFinal+1]-1);i++){
        printf("%c", c[i]);
    }
}*/
/*
int *vetor_linhas(FILE* arquivo){
    //esta função gera um vetor cujo o índice representa a linha e o
    //valor do índice representa em qual caracter a linha se inicia.
    int *vetor=(int*)malloc(sizeof(int));
    int i=0, j=1;
    char dados[1000];
    fscanf(arquivo, "%s", dados);
    vetor[0]=0;
    while(dados[i]!=NULL){
        if(dados[i]=='\n'){
            vetor[j]=i;
            j++;
        }
        i++;
    }
    return i;
}*/
