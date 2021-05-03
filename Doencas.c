#include "Doencas.h"

/*** 
 * Estrutura de Doencas 
***/

Doenca *criaDoenca(unsigned int id, char *nome, unsigned int nSintomas, char **sintomas)
{
    // Verifica que os dados sejam válidos
    if (nome == NULL)
    {
        printf("ERROR: Doenca::criaDoenca: O nome não pode ser NULL\n");
        exit(1);
    }
    else if (nSintomas > 0 && sintomas == NULL)
    {
        printf("ERROR: Doenca::criaDoenca: O array de sintomas não pode ser NULL\n");
        exit(1);
    }

    Doenca *doenca = (Doenca *)malloc(sizeof(Doenca));
    doenca->id = id;
    strcpy(doenca->nome, nome);
    doenca->nSintomas = nSintomas;
    doenca->sintomas = nSintomas > 0 ? sintomas : NULL;

    return doenca;
}

void eliminaDoenca(Doenca *doenca)
{
    //Esta função elimima uma doença do banco de dados, juntamento com suas associações
    if (doenca == NULL)
        return;
    // Libera vetor de sintomas
    for (int i = 0; i < doenca->nSintomas; i++)
        free(doenca->sintomas[i]);
    free(doenca->sintomas);
    free(doenca);
};

void imprimeDoenca(Doenca *doenca)
{
    //Imprime uma determinada doença juntamente com suas associações/informações pertinentes
    if (doenca != NULL)
    {
        printf("%8d || %-30s \t|| ", doenca->id, doenca->nome);
        for (int j = 0; j < doenca->nSintomas; j++)
            printf("%s, ", doenca->sintomas[j]);
        putchar('\n');
    }
}

void adicionaSintoma(Doenca *doenca, char *nomeSintoma)
{
    // Esta função adiciona algum sintoma na lista de sintomas de alguma determinada doença

    // Verifica que o ponteiro seja valido
    if (doenca == NULL)
        return;
    if (doenca->nSintomas == 0) // CASO: não tenha nenhum sintoma
        doenca->sintomas = NULL;

    doenca->nSintomas += 1;
    doenca->sintomas = (char **)realloc(doenca->sintomas, doenca->nSintomas * sizeof(char *));

    doenca->sintomas[doenca->nSintomas - 1] = (char *)malloc(MAX_NOME * sizeof(char));
    strcpy(doenca->sintomas[doenca->nSintomas - 1], nomeSintoma);
}

void removeSintoma(Doenca *doenca, char *nomeSintoma)
{
    // Esta função remoe algum sintoma na lista de sintomas de alguma determinada doença

    // Verifica que o ponteiro seja valido
    if (doenca == NULL)
        return;
    // Busca posição do sintoma
    int pos = -1;
    do
        pos++;
    while (pos < doenca->nSintomas && strcmp(doenca->sintomas[pos], nomeSintoma) != 0);
    // Verifica validez da posição
    if (pos < doenca->nSintomas)
    {
        // Libera memoria
        free(doenca->sintomas[pos]);
        // Atualiza nro de sintomas
        doenca->nSintomas -= 1;
        // Move lugar vazio para o final
        for (int i = pos; i < doenca->nSintomas; i++)
            doenca->sintomas[i] = doenca->sintomas[i + 1];
        // Atualiza tamanho do vetor
        doenca->sintomas = (char **)realloc(doenca->sintomas, doenca->nSintomas * sizeof(char *));
    }
}

/*** 
 * Árvore Doencas 
***/

ArvoreDoencas *criaArvoreDoencas()
{
    // Cria e retorna uma árvore de doenças
    ArvoreDoencas *a = (ArvoreDoencas *)malloc(sizeof(ArvoreDoencas));
    a->nDoencas = 0;
    a->raiz = NO_DOENCA_VAZIO;
    a->nosAbertos = (Vnos *)malloc(sizeof(Vnos));
    a->nosAbertos->n = 0;
    a->nosAbertos->max = V_SIZE;
    a->nosAbertos->nos = (NoDoencas **)malloc(a->nosAbertos->max * sizeof(NoDoencas *));
    return a;
};

NoDoencas *criaNoArvoreDoencas(ArvoreDoencas *r, int folha)
{
    // Esta função cria um novo nó na árvore de doenças

    NoDoencas *no = (NoDoencas *)malloc(sizeof(NoDoencas));
    no->id = r != NULL ? r->maxNoId++ : -1;
    no->folha = folha;
    no->nChaves = 0;
    for (int i = 0; i < MAX_CHAVES; i++)
    {
        no->chaves[i] = NULL;
        no->filhos[i] = -1;
    }
    if (r != NULL)
    {
        // Verifica se é necesario expandir o cache de nos abertos
        if (r->nosAbertos->n == r->nosAbertos->max)
        {
            r->nosAbertos->max += V_SIZE;
            r->nosAbertos->nos = realloc(r->nosAbertos->nos, r->nosAbertos->max * sizeof(NoDoencas *));
        }
        r->nosAbertos->nos[r->nosAbertos->n++] = no;
    }
    return no;
}

void liberarNoArvoreDoencas(NoDoencas *no)
{
    // Libera memoria das chaves
    for (int i = 0; i < no->nChaves; i++)
    {
        eliminaDoenca(no->chaves[i]);
    }
    // Libera no
    free(no);
}

void liberarArvoreDoencas(ArvoreDoencas *a)
{
    if (a == NULL)
        return;
    // Libera nos  abertos
    liberarNosAbertos(a);
    // Libera raiz
    liberarNo(a->raiz, a);
    // Libera memoria
    free(a);
}

void inserirDoenca(Doenca *doenca, ArvoreDoencas *a)
{
    if (a == NULL)
    {
        printf("ERROR: inserirDoenca: arvore não pode ser NULL\n");
        exit(1);
    }
    if (doenca == NULL)
    {
        printf("ERROR: inserirDoenca: doenca não pode ser NULL\n");
        exit(1);
    }
    // Limpa cache de nos
#if AUTO_SALVAR
    liberarNosAbertos(a);
#endif
    if (a->nDoencas == 0) // CASO: Arvore vazia
    {
        NoDoencas *n_raiz = criaNoArvoreDoencas(a, 1);
        a->raiz = n_raiz->id;
        n_raiz->chaves[0] = doenca;
        n_raiz->nChaves = 1;
    }
    else // CASO: Arvore não vazia
    {
        if (getNo(a->raiz, a)->nChaves == MAX_CHAVES) // CASO: raiz completa
        {
            NoDoencas *novo = criaNoArvoreDoencas(a, 0);
            novo->filhos[0] = a->raiz;
            dividirFilho(a, 0, novo, getNo(a->raiz, a));

            if (novo->chaves[0]->id > doenca->id)
            {
                novo->filhos[0] = inserirNo(a, doenca, getNo(novo->filhos[0], a))->id;
            }
            else
            {
                novo->filhos[1] = inserirNo(a, doenca, getNo(novo->filhos[1], a))->id;
            }
            a->raiz = novo->id;
        }
        else // CASO: raiz com espaços livres
        {
            inserirNo(a, doenca, getNo(a->raiz, a));
        }
    }
    a->nDoencas += 1;
#if AUTO_SALVAR
    persistirArvDoencas(a);
#endif
}

NoDoencas *inserirNo(ArvoreDoencas *r, Doenca *doenca, NoDoencas *a)
{
    int i = 0;
    if (a->folha) // CASO: No folha
    {
        // Busca posicao e move chaves
        for (i = a->nChaves - 1; i >= 0 && a->chaves[i]->id > doenca->id; i--)
            a->chaves[i + 1] = a->chaves[i];
        a->chaves[i + 1] = doenca;
        a->nChaves += 1;
    }
    else // CASO: No interno
    {
        i = a->nChaves - 1;
        while (i >= 0 && a->chaves[i]->id > doenca->id) // Busca posicao
        {
            i--;
        }

        if (getNo(a->filhos[i + 1], r)->nChaves == MAX_CHAVES) // CASO: no esteja completo
        {
            dividirFilho(r, i + 1, a, getNo(a->filhos[i + 1], r));
            if (a->chaves[i + 1]->id < doenca->id)
            {
                i++;
            }
        }
        a->filhos[i + 1] = inserirNo(r, doenca, getNo(a->filhos[i + 1], r))->id;
    }
    return a;
}

void dividirFilho(ArvoreDoencas *r, int pos, NoDoencas *no, NoDoencas *filho)
{
    // Variaveis
    int i = 0;
    NoDoencas *novo = criaNoArvoreDoencas(r, filho->folha);
    novo->nChaves = MIN_CHAVES;

    // Copia os ultimos elementos para o novo no
    for (i = 0; i < MIN_CHAVES; i++)
        novo->chaves[i] = filho->chaves[T + i];

    // Se o no não é folha, copia os seus filhos para os novos nos
    if (!filho->folha)
        for (i = 0; i < T; i++)
            novo->filhos[i] = filho->filhos[T + i];

    // Atualiza nro. de chaves no filho
    filho->nChaves = MIN_CHAVES;

    // Prepara lugar para o novo filho
    for (i = no->nChaves; i >= pos + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    // Adiciona novo filho
    no->filhos[pos + 1] = novo->id;

    // Abre espaco para a nova chave
    for (i = no->nChaves - 1; i >= pos; i--)
        no->chaves[i + 1] = no->chaves[i];

    // Copia a mediana do filho para o no e atualiza nro chaves
    no->chaves[pos] = filho->chaves[MIN_CHAVES];
    no->nChaves += 1;
}

void removerDoenca(ArvoreDoencas *a, int id)
{
    if (id < 0)
    {
        printf("ERROR: removerDoenca: id não poder ser menor que 0\n");
        exit(0);
    }
    // Caso a arvore esteja vazia, ignora remoção
    if (a->nDoencas == 0)
        return;
    liberarNosAbertos(a);
    // Remove chave
    remover(a, id, getNo(a->raiz, a));

    // Verifica se a raiz ficou vazia
    if (isVazio(getNo(a->raiz, a)))
    {
        NoDoencas *tmp = getNo(a->raiz, a);
        if (isFolha(getNo(a->raiz, a)))
            a->raiz = NO_DOENCA_VAZIO;
        else
            a->raiz = getNo(a->raiz, a)->filhos[0];

        // Desaloca raiz antiga
        liberarNo(tmp->id, a);
    }
    persistirArvDoencas(a);
}

void remover(ArvoreDoencas *r, int id, NoDoencas *a)
{
    int pos = 0;
    // Busca posicao da chave ou da primeira chave maior
    while (pos < a->nChaves && a->chaves[pos]->id < id)
        ++pos;
    // CASO: Nó contem a chave
    if (pos < a->nChaves && a->chaves[pos]->id == id)
    {
        if (isFolha(a))
            removerDeFolha(r, a, pos); // CASO 1
        else
            removerDeInterno(r, a, pos);
    }
    else // CASO: Nó não contem a chave
    {
        // CASO: valor nao existe na arvore
        if (isFolha(a))
        {
            return;
        }

        int ultima_chave = pos == a->nChaves;

        // Verifica se a sub-arvore precisa emprestar chaves
        if (getNo(a->filhos[pos], r)->nChaves < T)
        {
            // Verifica se a sub-arvore da esquerda pode doar
            if (pos != 0 && getNo(a->filhos[pos - 1], r)->nChaves >= T)
                DoadorEsquerda(r, a, pos);
            // Verifica se a sub-arvore da direita pode doar
            else if (pos != a->nChaves && getNo(a->filhos[pos + 1], r)->nChaves >= T)
                DoadorDireita(r, a, pos);
            // Caso nenhuma possa doar, combinar arvores
            else if (pos != a->nChaves)
                combinarFilhos(r, a, pos);
            else
                combinarFilhos(r, a, pos - 1);
        }
        // Se a ultima chave foi combinada com uma sub-arvore,
        // ir a sub-arvore anterior
        if (ultima_chave && pos > a->nChaves)
            remover(r, id, getNo(a->filhos[pos - 1], r));
        else
            remover(r, id, getNo(a->filhos[pos], r));
    }
}

void removerDeInterno(ArvoreDoencas *r, NoDoencas *a, int pos)
{
    Doenca *doenca = a->chaves[pos];
    // Verifica se a sub-arvore esquerda tem chaves suficientes
    if (getNo(a->filhos[pos], r)->nChaves > MIN_CHAVES)
    {
        // Busca a maior chave da esquerda
        NoDoencas *tmp = getNo(a->filhos[pos], r);
        while (!isFolha(tmp))
            tmp = getNo(tmp->filhos[tmp->nChaves], r);

        a->chaves[pos] = tmp->chaves[tmp->nChaves - 1];
        tmp->chaves[tmp->nChaves - 1] = doenca;

        // Remove recursivamente a chave extra
        remover(r, doenca->id, getNo(a->filhos[pos], r));
    }
    // Verifica se a sub-arvore direita tem chaves suficientes
    else if (getNo(a->filhos[pos + 1], r)->nChaves > MIN_CHAVES)
    {
        // Busca a menor chave da direita
        NoDoencas *tmp = getNo(a->filhos[pos + 1], r);
        while (!isFolha(tmp))
            tmp = getNo(tmp->filhos[0], r);

        a->chaves[pos] = tmp->chaves[0];
        tmp->chaves[0] = doenca;

        // Remove recursivamente a chave extra
        remover(r, doenca->id, getNo(a->filhos[pos + 1], r));
    }
    // Se nenhuma sub-arvore tem chaves suficientes,
    // combinamos as arvores
    else
    {
        combinarFilhos(r, a, pos);
        remover(r, doenca->id, getNo(a->filhos[pos], r));
    }
}

void removerDeFolha(ArvoreDoencas *r, NoDoencas *a, int pos)
{
    // Libera chaves
    eliminaDoenca(a->chaves[pos]);
    a->chaves[pos] = NULL;
    a->nChaves -= 1;

    // Arruma ordem de chaves
    for (int i = pos + 1; i < a->nChaves + 1; ++i)
        a->chaves[i - 1] = a->chaves[i];
}

void combinarFilhos(ArvoreDoencas *r, NoDoencas *a, int pos)
{
    NoDoencas *esq = getNo(a->filhos[pos], r),
              *dir = getNo(a->filhos[pos + 1], r);

    esq->chaves[MIN_CHAVES] = a->chaves[pos];

    // Move chaves para a outra chave
    for (int i = 0; i < dir->nChaves; ++i)
        esq->chaves[i + T] = dir->chaves[i];

    // CASO no interno, move filhos da outra subarvore
    if (!isFolha(esq))
        for (int i = 0; i <= dir->nChaves; ++i)
            esq->filhos[i + T] = dir->filhos[i];

    // Move chaves do no para suas posicoes corretas
    for (int i = pos + 1; i < a->nChaves; ++i)
        a->chaves[i - 1] = a->chaves[i];

    // Move os filhos para suas posicoes corretas
    for (int i = pos + 2; i <= a->nChaves; ++i)
        a->filhos[i - 1] = a->filhos[i];

    // Atualiza nro de chaves
    esq->nChaves += dir->nChaves + 1;
    a->nChaves--;

    // Libera no
    dir->nChaves = -1;
    liberarNo(dir->id, r);
}

void DoadorDireita(ArvoreDoencas *r, NoDoencas *a, int pos)
{
    NoDoencas *filho = getNo(a->filhos[pos], r),
              *dir = getNo(a->filhos[pos + 1], r);

    filho->chaves[filho->nChaves] = a->chaves[pos];

    // Caso seja um no interno move o filho do no doador
    if (!isFolha(filho))
        filho->filhos[filho->nChaves + 1] = dir->filhos[0];

    // Sobe primeira chave da direita
    a->chaves[pos] = dir->chaves[0];

    // Ajusta posicao das chaves
    for (int i = 1; i < dir->nChaves; ++i)
        dir->chaves[i - 1] = dir->chaves[i];

    // Caso seja um no interno ajusta posicao dos nos
    if (!isFolha(dir))
        for (int i = 1; i <= dir->nChaves; ++i)
            dir->filhos[i - 1] = dir->filhos[i];

    // Atualiza nro de chaves
    filho->nChaves += 1;
    dir->nChaves -= 1;

    return;
}

void DoadorEsquerda(ArvoreDoencas *r, NoDoencas *a, int pos)
{
    NoDoencas *filho = getNo(a->filhos[pos], r),
              *esq = getNo(a->filhos[pos - 1], r);
    // Move todas as chaves do filho uma posicao à direita
    for (int i = filho->nChaves - 1; i >= 0; --i)
        filho->chaves[i + 1] = filho->chaves[i];

    // Caso seja um no interno ajusta posicao dos nos
    if (!isFolha(filho))
        for (int i = filho->nChaves; i >= 0; --i)
            filho->filhos[i + 1] = filho->filhos[i];

    // Move chave ao filho
    filho->chaves[0] = a->chaves[pos - 1];

    // Move ultimo filho do doador a arvore destino
    if (!isFolha(filho))
        filho->filhos[0] = esq->filhos[esq->nChaves];

    // Sobe chave da esquerda para o no
    a->chaves[pos - 1] = esq->chaves[esq->nChaves - 1];

    // Atualiza nro. de chaves
    filho->nChaves += 1;
    esq->nChaves -= 1;
}

void imprimeArvore(ArvoreDoencas *r, NoDoencas *a, int h)
{
    int i;
    for (i = 0; i < a->nChaves; i++)
    {
        if (!a->folha)
            imprimeArvore(r, getNo(a->filhos[i], r), h + 1);
        for (int j = 0; j < h; j++)
            putchar('\t');
        printf(" %d", a->chaves[i]->id);
        putchar('\n');
    }

    if (!a->folha)
        imprimeArvore(r, getNo(a->filhos[i], r), h + 1);
}

void imprimeDoencas(ArvoreDoencas *r, NoDoencas *a)
{
    int i;
    for (i = 0; i < a->nChaves; i++)
    {
        if (!a->folha)
        {
            imprimeDoencas(r, getNo(a->filhos[i], r));
            liberarNo(a->filhos[i], r);
        }
        imprimeDoenca(a->chaves[i]);
    }
    if (!a->folha)
    {
        imprimeDoencas(r, getNo(a->filhos[i], r));
        liberarNo(a->filhos[i], r);
    }
}

int isCheio(NoDoencas *a)
{
    return a->nChaves == MAX_CHAVES;
}

int isVazio(NoDoencas *a)
{
    return a->nChaves == 0;
}

int isFolha(NoDoencas *a)
{
    return a->folha && a->filhos[0] == NO_DOENCA_VAZIO;
}

Doenca *getDoenca(int id, ArvoreDoencas *a)
{
    // Verifica validez de arvore
    if (a == NULL)
        return NULL;
    // Busca e retorna ponteiro da doenca
    return getChave(id, getNo(a->raiz, a), a);
};

Doenca *getChave(int id, NoDoencas *n, ArvoreDoencas *a)
{
    // Busca chave ou a primeira chave maior que o id
    int i = 0;
    while (i < n->nChaves && id > n->chaves[i]->id)
    {
        i++;
    };

    // Verifica se é a chave buscada
    if (i < n->nChaves && n->chaves[i]->id == id)
        return n->chaves[i];

    // Se estamos em uma folha, a chave não existe
    if (isFolha(n))
        return NULL;

    // Busca recursivamente no filho selecionado
    return getChave(id, getNo(n->filhos[i], a), a);
}

// Carga/Persistencia de nos;
ArvoreDoencas *carregaArvDoencas()
{
    ArvoreDoencas *a = carregaArqArvDoencas();
    // Caso não exista arquivo de arvore, cria uma nova
    if (a == NULL)
        return criaArvoreDoencas();

    return a;
}

NoDoencas *getNo(int idNo, ArvoreDoencas *a)
{

    // Busca no entre os nos abertos
    for (int i = 0; i < a->nosAbertos->n; i++)
        if (a->nosAbertos->nos[i]->id == idNo)
            return a->nosAbertos->nos[i];

    // CASO o no nao esteja carregado.
    NoDoencas *no = carregaArqNo(idNo);
#if DEBUG
    printf("CARREGANDO...%d\n", idNo);
#endif
    // Caso de erro termina execução
    if (no == NULL)
    {
        printf("ERROR:getNo: não foi possível carregar o no %d desde seu arquivo.\n", idNo);
        exit(1);
    }

    // Verifica se é necesario expandir o cache de nos abertos
    if (a->nosAbertos->n == a->nosAbertos->max)
    {
        a->nosAbertos->max += V_SIZE;
        a->nosAbertos->nos = (NoDoencas **)realloc(a->nosAbertos->nos, a->nosAbertos->max * sizeof(NoDoencas *));
    }

    // Adiciona ao nos abertos
    a->nosAbertos->nos[a->nosAbertos->n++] = no;

    return no;
}

void persistirArvDoencas(ArvoreDoencas *a)
{
    int status = 1;
    status = status && persisteCabDoencas(a);
    // Persiste nós
    for (int i = a->nosAbertos->n - 1; status && i >= 0; i--)
        status = status && persisteNoArq(a->nosAbertos->nos[i]);
    // Verifica estado final da operação
    if (!status)
    {
        printf("ERROR:persistirArvDoencas: não foi possível persistir as doencas.");
        exit(1);
    }
}

void persistirNo(int id, ArvoreDoencas *a)
{
    int i = a->nosAbertos->n - 1;
    // Pesquisa posição de nó
    while (i >= 0 && a->nosAbertos->nos[i]->id == id)
        --i;
    if (i < 0)
        return;
    // Persiste nó
    persisteNoArq(a->nosAbertos->nos[i]);
}

void liberarNosAbertos(ArvoreDoencas *a)
{
    while (a->nosAbertos->n > 0)
        liberarNo(a->nosAbertos->nos[0]->id, a);
}

void liberarNo(int id, ArvoreDoencas *a)
{
#if DEBUG
    printf("LIBERANDO...%d %d\n", id, a->nosAbertos->n);
#endif

    int i = a->nosAbertos->n - 1;
    while (i >= 0 && a->nosAbertos->nos[i]->id != id)
        --i;

    if (i < 0)
        return;

    NoDoencas *no = a->nosAbertos->nos[i];

    if (i == a->nosAbertos->n - 1) // Caso esteja no final do vetor
    {
        a->nosAbertos->nos[i] = NULL;
    }
    else // Caso esteja no meio do vetor
    {
        while (i < a->nosAbertos->n - 1)
        {
            a->nosAbertos->nos[i] = a->nosAbertos->nos[i + 1];
            i++;
        }
    }
    // Libera no de memoria
    a->nosAbertos->n -= 1;
    liberarNoArvoreDoencas(no);
}

int persisteNoArq(NoDoencas *no)
{
#if DEBUG
    printf("PERSISTINDO...%d\n", no->id);
#endif
    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "", s_id[10];
    sprintf(s_id, "%05d", no->id);
    strcat(fName, DATA_HOME);
    strcat(fName, DOENCAS_N_PRE);
    strcat(fName, s_id);
    strcat(fName, DOENCAS_N_EXT);
    strcat(fName, "\0");
    // Remove arquivo anterior
    remove(fName);

    FILE *arq = fopen(fName, "w");
    // Verifica se o arquivo foi aberto
    if (arq == NULL)
    {
        printf("ERROR:persisteNoArq: não foi possível abrir o arquivo \"%s\".\n", fName);
        exit(1);
    }
    fprintf(arq, "%d %d %d %d\n", no->id, no->nChaves, no->folha, T);

    // Chaves
    for (int i = 0; i < no->nChaves; i++)
    {
        Doenca *doenca = no->chaves[i];
        fprintf(arq, "%s\n", doenca->nome);
        fprintf(arq, "%d %d\n", doenca->id, doenca->nSintomas);
        for (int j = 0; j < doenca->nSintomas; j++)
            fprintf(arq, "%s\n", doenca->sintomas[j]);
    }

    // Filhos
    if (!isFolha(no))
        for (int i = 0; i < no->nChaves + 1; i++)
            fprintf(arq, "%d\n", no->filhos[i]);

    return fclose(arq) == 0;
}

NoDoencas *carregaArqNo(int id)
{
    if (id < 0)
        return NULL;

    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "", s_id[10];
    sprintf(s_id, "%05d", id);
    strcat(fName, DATA_HOME);
    strcat(fName, DOENCAS_N_PRE);
    strcat(fName, s_id);
    strcat(fName, DOENCAS_N_EXT);
    strcat(fName, "\0");

    FILE *arq = fopen(fName, "r");

    NoDoencas *no = criaNoArvoreDoencas(NULL, 1);

    // Verifica se o arquivo foi aberto
    if (arq == NULL)
    {
        printf("ERROR:carregaArqNo: não foi possível abrir o arquivo \"%s\".\n", fName);
        exit(1);
    }

    int t = -2;
    fscanf(arq, "%d %d %d %d\n", &no->id, &no->nChaves, &no->folha, &t);

    if (no->id != id || t != T)
    {
        printf("ERROR:carregaArqNo: inconsistência de informações. (%s)\n", fName);
        exit(1);
    }
    // Chaves
    for (int i = 0; i < no->nChaves; i++)
    {
        int nSintomas;
        char nome[MAX_NOME] = "";
        // Carrega nome
        nome[0] = '\0';
        fgets(nome, MAX_NOME, arq);
        nome[strcspn(nome, "\n")] = 0;
        fscanf(arq, "%d %d\n", &id, &nSintomas);
        char **sintomas = (char **)malloc(nSintomas * sizeof(char *));
        for (int j = 0; j < nSintomas; j++)
        {
            sintomas[j] = (char *)malloc(MAX_NOME * sizeof(char));
            fgets(sintomas[j], MAX_NOME, arq);
            sintomas[j][strcspn(sintomas[j], "\n")] = 0;
        }
        no->chaves[i] = criaDoenca(id, nome, nSintomas, sintomas);
    }
    // Filhos
    if (!isFolha(no))
        for (int i = 0; i < no->nChaves + 1; i++)
            fscanf(arq, "%d\n", &no->filhos[i]);

    fclose(arq);
    return no;
}

int persisteCabDoencas(ArvoreDoencas *a)
{
#if DEBUG
    printf("PESISTINDO CAB...\n");
#endif
    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "";
    strcat(fName, DATA_HOME);
    strcat(fName, DOENCAS_CAB);
    strcat(fName, "\0");

    // Remove arquivo anterior
    remove(fName);

    FILE *arq = fopen(fName, "w");
    // Verifica se o arquivo foi aberto
    if (arq == NULL)
    {
        printf("ERROR:persisteCabDoencas: não foi possível abrir o arquivo \"%s\".\n", fName);
        exit(1);
    }

    fprintf(arq, "%d %d %d %d\n", a->nDoencas, a->maxNoId, a->raiz, T);
    return fclose(arq) == 0;
}

ArvoreDoencas *carregaArqArvDoencas()
{
    // Gera nome arquivo
    char fName[MAX_ARQ_BUFFER] = "";
    strcat(fName, DATA_HOME);
    strcat(fName, DOENCAS_CAB);
    strcat(fName, "\0");

    FILE *arq = fopen(fName, "r");
    // Verifica se o arquivo foi aberto
    if (arq == NULL)
    {
        printf("ERROR:carregaArqArvDoencas: não foi possível abrir o arquivo \"%s\".\n", fName);
        exit(1);
    }

    ArvoreDoencas *a = criaArvoreDoencas();
    int t = -1;

    fscanf(arq, "%d %d %d %d\n", &(a->nDoencas), &(a->maxNoId), &(a->raiz), &t);
    fclose(arq);
    if (t != T)
    {
        printf("ERROR:carregaArqArvDoencas: inconsistência de dados.\n");
        exit(1);
    }
    return a;
}