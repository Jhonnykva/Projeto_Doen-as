#include "Doenças.h"

/*** 
 * Estrutura de Doenças 
***/

Doença *cria_doenca(unsigned int id, char *nome, unsigned int n_sintomas, unsigned int *sintomas)
{
    // Verifica que os dados sejam válidos
    if (nome == NULL)
    {
        printf("ERROR: Doença::cria_doenca: O nome não pode ser NULL\n");
        exit(1);
    }
    else if (sintomas == NULL)
    {
        printf("ERROR: Doença::cria_doenca: O array de sintomas não pode ser NULL\n");
        exit(1);
    }

    Doença *doença = (Doença *)malloc(sizeof(Doença));
    doença->id = id;
    strcpy(doença->nome, nome); // Falta tratar o tamanho do nome
    doença->n_sintomas = n_sintomas;
    doença->sintomas = sintomas;

    return doença;
}
void elimina_doenca(Doença *doença)
{
    // Falta decidir se alocar nome e sintomas dinamicamente/estaticamente
    free(doença);
};

void imprime_doenca(Doença *doença)
{
    if (doença != NULL)
    {
        printf("%05d - %s \n", doença->id, doença->nome);
    }
}

/*** 
 * Árvore Doenças 
***/

Arvore_Doencas *cria_arvore_doencas()
{
    Arvore_Doencas *a_doencas = (Arvore_Doencas *)malloc(sizeof(Arvore_Doencas));
    a_doencas->n_doencas = 0;
    a_doencas->raiz = NULL;
    return a_doencas;
};

No_Doencas *cria_no_arvore_doencas(int folha)
{
    No_Doencas *no = (No_Doencas *)malloc(sizeof(No_Doencas));
    no->folha = folha;
    no->n_chaves = 0;
    for (int i = 0; i < MAX_CHAVES; i++)
    {
        no->chaves[i] = NULL;
        no->filhos[i] = NULL;
    }
    no->filhos[MAX_FILHOS - 1] = NULL;
    return no;
}

Arvore_Doencas *inserir_doenca(Doença *doenca, Arvore_Doencas *a)
{
    if (a == NULL)
    {
        printf("ERROR: inserir_doenca: arvore não pode ser NULL\n");
        exit(1);
    }
    if (doenca == NULL)
    {
        printf("ERROR: inserir_doenca: doença não pode ser NULL\n");
        exit(1);
    }
    if (a->n_doencas == 0) // CASO: Arvore vazia
    {
        a->raiz = cria_no_arvore_doencas(1);
        a->raiz->chaves[0] = doenca;
        a->raiz->n_chaves = 1;
    }
    else // CASO: Arvore não vazia
    {
        if (a->raiz->n_chaves == MAX_CHAVES) // CASO: raiz completa
        {
            No_Doencas *novo = cria_no_arvore_doencas(0);
            novo->filhos[0] = a->raiz;
            novo->n_chaves = 0;
            novo = dividir_filho(0, novo, a->raiz);

            if (novo->chaves[0]->id < doenca->id)
            {
                novo->filhos[0] = inserir_normal(doenca, novo->filhos[0]);
            }
            else
            {
                novo->filhos[1] = inserir_normal(doenca, novo->filhos[1]);
            }

            a->raiz = novo;
        }
        else // CASO: raiz com espaços livres
        {
            inserir_normal(doenca, a->raiz);
        }
    }
    a->n_doencas++;
    return a;
}

No_Doencas *inserir_normal(Doença *doenca, No_Doencas *a)
{
    printf("INSERINDO %d\n", doenca->id);
    int i = 0;
    if (a->folha) // CASO: No folha
    {
        // Busca posicao e move chaves
        for (i = a->n_chaves - 1; i >= 0 && a->chaves[i]->id > doenca->id; i--)
            a->chaves[i + 1] = a->chaves[i];
        a->chaves[i + 1] = doenca;
        a->n_chaves++;
    }
    else // CASO: No interno
    {
        i = a->n_chaves - 1;
        while (i >= 0 && a->chaves[i]->id > doenca->id) // Busca posicao
        {
            i--;
        }
        if (a->filhos[i + 1]->n_chaves == MAX_CHAVES) // CASO o no esteja completo
        {
            a->filhos[i + 1] = dividir_filho(i + 1, a, a->filhos[i + 1]);
            if (a->chaves[i + 1]->id < doenca->id)
            {
                i++;
            }
        }
        a->filhos[i + 1] = inserir_normal(doenca, a->filhos[i + 1]);
    }
    return a;
}

No_Doencas *dividir_filho(int pos, No_Doencas *no, No_Doencas *filho)
{
    // printf("dividindo... %d %d %d\n", pos, no == NULL, filho == NULL);
    // Variaveis
    int i = 0;
    No_Doencas *novo = cria_no_arvore_doencas(filho->folha);
    novo->n_chaves = MIN_CHAVES;

    // Copia os ultimos elementos para o novo no
    for (i = 0; i < MIN_CHAVES; i++)
        novo->chaves[i] = filho->chaves[T + i];

    // Se o no não é folha, copia os seus filhos para os novos nos
    if (!filho->folha)
        for (i = 0; i < T; i++)
            novo->filhos[i] = filho->filhos[T + i];

    // Atualiza nro. de chaves no filho
    filho->n_chaves = MIN_CHAVES;

    // Prepara lugar o novo filho
    for (i = no->n_chaves; i >= pos + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    // Adiciona novo filho
    no->filhos[pos + 1] = novo;

    // Abre espaco para a nova  chave
    for (i = no->n_chaves - 1; i >= pos; i--)
        no->chaves[i + 1] = no->chaves[i];

    // Copia a mediana do filho para o no
    no->chaves[pos] = filho->chaves[MIN_CHAVES];

    no->n_chaves += 1;

    return no;
}

Arvore_Doencas Busca(Arvore_Doencas *a, int chave)
{
    //busca alguma chave
    // int i = 0;
    // while ((i < a->n) && (k > a->chave[i]))
    // {
    //     i++;
    // }
    // if ((i < a->n) && (k == a->chave[i]))
    // {
    //     printf("Encontrado");
    // }
    // else if (a->folha)
    // {
    //     printf("Nao-Encontrado");
    // }
    // else
    // {
    //     return Busca(a->filhos[i], k);
    // }
}
