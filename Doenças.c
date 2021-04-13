#include "Doenças.h"

/*** 
 * Estrutura de Doenças 
***/

Doenca *cria_doenca(unsigned int id, char *nome, unsigned int n_sintomas, unsigned int *sintomas)
{
    // Verifica que os dados sejam válidos
    if (nome == NULL)
    {
        printf("ERROR: Doenca::cria_doenca: O nome não pode ser NULL\n");
        exit(1);
    }
    else if (sintomas == NULL)
    {
        printf("ERROR: Doenca::cria_doenca: O array de sintomas não pode ser NULL\n");
        exit(1);
    }

    Doenca *doenca = (Doenca *)malloc(sizeof(Doenca));
    doenca->id = id;
    strcpy(doenca->nome, nome); // Falta tratar o tamanho do nome
    doenca->n_sintomas = n_sintomas;
    doenca->sintomas = sintomas;

    return doenca;
}
void elimina_doenca(Doenca *doença)
{
    // Falta decidir se alocar nome e sintomas dinamicamente/estaticamente
    free(doença);
};

void imprime_doenca(Doenca *doença)
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
    Arvore_Doencas *a = (Arvore_Doencas *)malloc(sizeof(Arvore_Doencas));
    a->n_doencas = 0;
    a->raiz = NULL;
    a->nos_abertos = (V_Nos *)malloc(sizeof(V_Nos));
    a->nos_abertos->n = 0;
    a->nos_abertos->max = V_SIZE;
    a->nos_abertos->nos = (No_Doencas **)malloc(a->nos_abertos->max * sizeof(No_Doencas *));

    a->arquivo_tmp = (V_Nos *)malloc(sizeof(V_Nos));
    a->arquivo_tmp->n = 0;
    a->arquivo_tmp->max = 100;
    a->arquivo_tmp->nos = (No_Doencas **)malloc(a->arquivo_tmp->max * sizeof(No_Doencas *));

    return a;
};

No_Doencas *cria_no_arvore_doencas(Arvore_Doencas *r, int folha)
{
    No_Doencas *no = (No_Doencas *)malloc(sizeof(No_Doencas));
    no->id = r->max_no_id++;
    no->folha = folha;
    no->n_chaves = 0;
    for (int i = 0; i < MAX_CHAVES; i++)
    {
        no->chaves[i] = NULL;
        no->filhos[i] = NULL;
    }

    // Verifica se é necesario expandir o cache de nos abertos
    if (r->nos_abertos->n == r->nos_abertos->max)
    {
        r->nos_abertos->max += V_SIZE;
        r->nos_abertos->nos = realloc(r->nos_abertos->nos, r->nos_abertos->max * sizeof(No_Doencas *));
    }
    printf("%d\n", no->id);
    r->nos_abertos->nos[r->nos_abertos->n++] = no;
    r->arquivo_tmp->nos[r->arquivo_tmp->n++] = no;
    return no;
}

void liberar_no_arvore_doencas(No_Doencas *no)
{
    // Libera memoria das chaves
    for (int i = 0; i < no->n_chaves; i++)
    {
        free(no->chaves[i]);
    }
    // Libera no
    free(no);
}

void inserir_doenca(Doenca *doenca, Arvore_Doencas *a)
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
        a->raiz = cria_no_arvore_doencas(a, 1);
        a->raiz->chaves[0] = doenca;
        a->raiz->n_chaves = 1;
    }
    else // CASO: Arvore não vazia
    {
        if (a->raiz->n_chaves == MAX_CHAVES) // CASO: raiz completa
        {
            No_Doencas *novo = cria_no_arvore_doencas(a, 0);
            novo->filhos[0] = a->raiz;
            dividir_filho(a, 0, novo, a->raiz);

            if (novo->chaves[0]->id > doenca->id)
            {
                novo->filhos[0] = inserir_no(a, doenca, novo->filhos[0]);
            }
            else
            {
                novo->filhos[1] = inserir_no(a, doenca, novo->filhos[1]);
            }
            a->raiz = novo;
        }
        else // CASO: raiz com espaços livres
        {
            inserir_no(a, doenca, a->raiz);
        }
    }
    a->n_doencas += 1;
}

No_Doencas *inserir_no(Arvore_Doencas *r, Doenca *doenca, No_Doencas *a)
{
    int i = 0;
    if (a->folha) // CASO: No folha
    {
        // Busca posicao e move chaves
        for (i = a->n_chaves - 1; i >= 0 && a->chaves[i]->id > doenca->id; i--)
            a->chaves[i + 1] = a->chaves[i];
        a->chaves[i + 1] = doenca;
        a->n_chaves += 1;
    }
    else // CASO: No interno
    {
        i = a->n_chaves - 1;
        while (i >= 0 && a->chaves[i]->id > doenca->id) // Busca posicao
        {
            i--;
        }

        if (a->filhos[i + 1]->n_chaves == MAX_CHAVES) // CASO: no esteja completo
        {
            dividir_filho(r, i + 1, a, a->filhos[i + 1]);
            if (a->chaves[i + 1]->id < doenca->id)
            {
                i++;
            }
        }
        a->filhos[i + 1] = inserir_no(r, doenca, a->filhos[i + 1]);
    }
    return a;
}

void dividir_filho(Arvore_Doencas *r, int pos, No_Doencas *no, No_Doencas *filho)
{
    // Variaveis
    int i = 0;
    No_Doencas *novo = cria_no_arvore_doencas(r, filho->folha);
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

    // Prepara lugar para o novo filho
    for (i = no->n_chaves; i >= pos + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    // Adiciona novo filho
    no->filhos[pos + 1] = novo;

    // Abre espaco para a nova chave
    for (i = no->n_chaves - 1; i >= pos; i--)
        no->chaves[i + 1] = no->chaves[i];

    // Copia a mediana do filho para o no e atualiza nro chaves
    no->chaves[pos] = filho->chaves[MIN_CHAVES];
    no->n_chaves += 1;
}

void imprime_arvore(No_Doencas *a, int h)
{
    int i;
    for (i = 0; i < a->n_chaves; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!a->folha)
            imprime_arvore(a->filhos[i], h + 1);
        for (int j = 0; j < h; j++)
            putchar('\t');
        printf(" %d", a->chaves[i]->id);
        putchar('\n');
    }

    // Print the subtree rooted with last child
    if (!a->folha)
        imprime_arvore(a->filhos[i], h + 1);
}

void remover_doenca(Arvore_Doencas *a, int id)
{
    if (id < 0)
    {
        printf("ERROR: remover_doenca: id não poder ser menor que 0\n");
        exit(0);
    }
    // Caso a arvore esteja vazia, ignora remoção
    if (a->n_doencas == 0)
        return;

    // Remove chave
    remover(a, id, a->raiz);

    // Verifica se a raiz ficou vazia
    if (is_vazio(a->raiz))
    {
        No_Doencas *tmp = a->raiz;
        if (is_folha(a->raiz))
            a->raiz = NULL;
        else
            a->raiz = a->raiz->filhos[0];

        // Desaloca raiz antiga
        free(tmp);
    }
}

void remover(Arvore_Doencas *r, int id, No_Doencas *a)
{
    int pos = 0;
    // Busca posicao da chave ou da primeira chave maior
    while (pos < a->n_chaves && a->chaves[pos]->id < id)
        ++pos;
    // CASO: Nó contem a chave
    if (pos < a->n_chaves && a->chaves[pos]->id == id)
    {
        if (is_folha(a))
            remover_de_folha(r, a, pos); // CASO 1
        else
            remover_de_interno(r, a, pos);
    }
    else // CASO: Nó não contem a chave
    {
        // CASO: valor nao existe na arvore
        if (is_folha(a))
        {
            return;
        }

        int ultima_chave = pos == a->n_chaves;

        // Verifica se a sub-arvore precisa emprestar chaves
        if (a->filhos[pos]->n_chaves < T)
        {
            // Verifica se a sub-arvore da esquerda pode doar
            if (pos != 0 && a->filhos[pos - 1]->n_chaves >= T)
                doador_esquerda(r, a, pos);
            // Verifica se a sub-arvore da direita pode doar
            else if (pos != a->n_chaves && a->filhos[pos + 1]->n_chaves >= T)
                doador_direita(r, a, pos);
            // Caso nenhuma possa doar, combinar arvores
            else if (pos != a->n_chaves)
                combinar_filhos(r, a, pos);
            else
                combinar_filhos(r, a, pos - 1);
        }
        // Se a ultima chave foi combinada com uma sub-arvore,
        // ir a sub-arvore anterior
        if (ultima_chave && pos > a->n_chaves)
            remover(r, id, a->filhos[pos - 1]);
        else
            remover(r, id, a->filhos[pos]);
    }
}

void remover_de_interno(Arvore_Doencas *r, No_Doencas *a, int pos)
{
    Doenca *doenca = a->chaves[pos];

    // Verifica se a sub-arvore esquerda tem chaves suficientes
    if (a->filhos[pos]->n_chaves > MIN_CHAVES)
    {
        // Busca a maior chave da esquerda
        No_Doencas *tmp = a->filhos[pos];
        while (!is_folha(tmp))
            tmp = tmp->filhos[tmp->n_chaves];

        a->chaves[pos] = tmp->chaves[tmp->n_chaves - 1];
        tmp->chaves[tmp->n_chaves - 1] = doenca;

        // Remove recursivamente a chave extra
        remover(r, doenca->id, a->filhos[pos]);
    }
    // Verifica se a sub-arvore direita tem chaves suficientes
    else if (a->filhos[pos + 1]->n_chaves > MIN_CHAVES)
    {
        // Busca a menor chave da direita
        No_Doencas *tmp = a->filhos[pos + 1];
        while (!is_folha(tmp))
            tmp = tmp->filhos[0];

        a->chaves[pos] = tmp->chaves[0];
        tmp->chaves[0] = doenca;

        // Remove recursivamente a chave extra
        remover(r, doenca->id, a->filhos[pos + 1]);
    }
    // Se nenhuma sub-arvore tem chaves suficientes,
    // combinamos as arvores
    else
    {
        combinar_filhos(r, a, pos);
        remover(r, doenca->id, a->filhos[pos]);
    }
}

void remover_de_folha(Arvore_Doencas *r, No_Doencas *a, int pos)
{
    // Libera chaves
    free(a->chaves[pos]);
    a->chaves[pos] = NULL;
    a->n_chaves -= 1;

    // Arruma ordem de chaves
    for (int i = pos + 1; i < a->n_chaves + 1; ++i)
        a->chaves[i - 1] = a->chaves[i];
}

void combinar_filhos(Arvore_Doencas *r, No_Doencas *a, int pos)
{
    No_Doencas *esq = a->filhos[pos],
               *dir = a->filhos[pos + 1];

    esq->chaves[MIN_CHAVES] = a->chaves[pos];

    // Move chaves para a outra chave
    for (int i = 0; i < dir->n_chaves; ++i)
        esq->chaves[i + T] = dir->chaves[i];

    // CASO no interno, move filhos da outra subarvore
    if (!is_folha(esq))
        for (int i = 0; i <= dir->n_chaves; ++i)
            esq->filhos[i + T] = dir->filhos[i];

    // Move chaves do no para suas posicoes corretas
    for (int i = pos + 1; i < a->n_chaves; ++i)
        a->chaves[i - 1] = a->chaves[i];

    // Move os filhos para suas posicoes corretas
    for (int i = pos + 2; i <= a->n_chaves; ++i)
        a->filhos[i - 1] = a->filhos[i];

    // Atualiza nro de chaves
    esq->n_chaves += dir->n_chaves + 1;
    a->n_chaves--;

    // Libera no
    free(dir);
}

void doador_direita(Arvore_Doencas *r, No_Doencas *a, int pos)
{
    No_Doencas *filho = a->filhos[pos],
               *dir = a->filhos[pos + 1];

    filho->chaves[filho->n_chaves] = a->chaves[pos];

    // Caso seja um no interno move o filho do no doador
    if (!is_folha(filho))
        filho->filhos[filho->n_chaves + 1] = dir->filhos[0];

    // Sobe primeira chave da direita
    a->chaves[pos] = dir->chaves[0];

    // Ajusta posicao das chaves
    for (int i = 1; i < dir->n_chaves; ++i)
        dir->chaves[i - 1] = dir->chaves[i];

    // Caso seja um no interno ajusta posicao dos nos
    if (!is_folha(dir))
        for (int i = 1; i <= dir->n_chaves; ++i)
            dir->filhos[i - 1] = dir->filhos[i];

    // Atualiza nro de chaves
    filho->n_chaves += 1;
    dir->n_chaves -= 1;

    return;
}

void doador_esquerda(Arvore_Doencas *r, No_Doencas *a, int pos)
{
    No_Doencas *filho = a->filhos[pos],
               *esq = a->filhos[pos - 1];

    // Move todas as chaves do filho uma posicao à direita
    for (int i = filho->n_chaves - 1; i >= 0; --i)
        filho->chaves[i + 1] = filho->chaves[i];

    // Caso seja um no interno ajusta posicao dos nos
    if (!is_folha(filho))
        for (int i = filho->n_chaves; i >= 0; --i)
            filho->filhos[i + 1] = filho->filhos[i];

    // Move chave ao filho
    filho->chaves[0] = a->chaves[pos - 1];

    // Move ultimo filho do doador a arvore destino
    if (!is_folha(filho))
        filho->filhos[0] = esq->filhos[esq->n_chaves];

    // Sobe chave da esquerda para o no
    a->chaves[pos - 1] = esq->chaves[esq->n_chaves - 1];

    // Atualiza nro. de chaves
    filho->n_chaves += 1;
    esq->n_chaves -= 1;
}

int is_cheio(No_Doencas *a)
{
    return a->n_chaves == MAX_CHAVES;
}

int is_vazio(No_Doencas *a)
{
    return a->n_chaves == 0;
}

int is_folha(No_Doencas *a)
{
    return a->folha && a->filhos[0] == NULL;
}

// Carga/Persistencia de nos;
Arvore_Doencas *carregar_arvore_doencas()
{
    // Falta carregar arvores base desde arquivo
    return cria_arvore_doencas();
}

No_Doencas *get_no(int id_no, Arvore_Doencas *a)
{
    printf("++ %d\n", id_no);
    // Busca no entre os nos abertos
    for (int i = 0; i < a->nos_abertos->n; i++)
        if (a->nos_abertos->nos[i]->id == id_no)
            return a->nos_abertos->nos[i];

    // CASO o no nao esteja carregado.
    // Carrega o no usando seu arquivo
    // Temporalmente uso de um vetor para simular acesso a arquivos
    for (int i = 0; i < a->arquivo_tmp->n; i++)
        if (a->arquivo_tmp->nos[i]->id == id_no)
        {
            // Verifica se é necesario expandir o cache de nos abertos
            if (a->nos_abertos->n == a->nos_abertos->max)
            {
                a->nos_abertos->max += V_SIZE;
                a->nos_abertos->nos = (No_Doencas **)realloc(a->nos_abertos->nos, a->nos_abertos->max * sizeof(No_Doencas *));
            }
            a->nos_abertos->nos[a->nos_abertos->n++] = a->arquivo_tmp->nos[i];
            return a->arquivo_tmp->nos[i];
        }
}

void persistir_nos_abertos(Arvore_Doencas *a)
{
    for (int i = a->nos_abertos->n - 1; i >= 0; i--)
    {
        persistir_no(a->nos_abertos->nos[i]->id, a);
    }
}

void persistir_no(int id, Arvore_Doencas *a)
{
    int i = a->nos_abertos->n - 1;
    while (i >= 0 && a->nos_abertos->nos[i])
        --i;

    if (i < 0)
        return;

    No_Doencas *no = a->nos_abertos->nos[i];

    // Caso esteja no final do vetor
    if (i == a->nos_abertos->n - 1)
    {
        a->nos_abertos->nos[i] = NULL;
    }
    // Caso esteja no meio do vetor
    else
    {
        while (i < a->nos_abertos->n - 1)
        {
            a->nos_abertos->nos[i] = a->nos_abertos->nos[i + 1];
            i++;
        }
    }

    /*
        Falta implementar persistencia no arquivo
    */
    // Desabilitado até utilizar arquivos
    // liberar_no_arvore_doencas(no);
}

void liberar_nos_abertos(Arvore_Doencas *a)
{
    for (int i = a->nos_abertos->n - 1; i >= 0; i--)
    {
        liberar_no(a->nos_abertos->nos[i]->id, a);
    }
}

void liberar_no(int id, Arvore_Doencas *a)
{
    int i = a->nos_abertos->n - 1;
    while (i >= 0 && a->nos_abertos->nos[i])
        --i;

    if (i < 0)
        return;

    No_Doencas *no = a->nos_abertos->nos[i];

    // Caso esteja no final do vetor
    if (i == a->nos_abertos->n - 1)
    {
        a->nos_abertos->nos[i] = NULL;
    }
    // Caso esteja no meio do vetor
    else
    {
        while (i < a->nos_abertos->n - 1)
        {
            a->nos_abertos->nos[i] = a->nos_abertos->nos[i + 1];
            i++;
        }
    }

    // Desabilitado até utilizar arquivos
    // liberar_no_arvore_doencas(no);
}

// Arvore_Doencas Busca(Arvore_Doencas *a, int chave)
// {
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
// }

// Arvore_Doencas *inserir_doenca(Arvore_Doencas *a, Doenca *doenca)
// {
/*
     if(a==NULL){
        a= (Arvore_Doencas*)malloc(sizeof(Arvore_Doencas));//Não tenho certeza, talvez seja ponteiro de ponteiro
        a->chave=doenca->id;//trocar id por string futuramente
        a->folha=1;//é uma folha por enquanto
        for(int c=0; c<MAX_CHAVES; c++){
            a->chaves[i]=NULL;//garante que  todos os ponteiros para 
                              //subárvores estejam nulos e prontos para uso
        }
        return a;
    }
    if(!testaFolha(a)){
        a->folha=0;
    }//Verifica se os filhos não NULL, se alguém deles não for então não é folha mais.
 
    int i=0, j=0, aux1, aux2;
    while((i<MAX_CHAVES) && (doenca->id > a->chaves[i])){
        i++;
    }//percorre até achar o ponto em que a doença deve ser inserida
    while(a->folha==0){
        inserir_doenca(a->filhos[i], doenca->id);
    }//desce até o último nível da árvore
    //Obs: ao usar a recursão juntamente com o if(a==NULL), ele vai criando os filhos automaticamente,
    //não tenho certeza, mas da forma que foi implementado talvez ele crie 1 filho a menos.

    //CASO 1 - árvore possui espaço para colocar folha
    if(a->chaves[MAX_CHAVES]==NULL){
        aux1=doenca->id;
        while(i<MAX_CHAVES){
            aux2=a->chaves[i];
            a->chaves[i]=aux1;
            aux1=aux2;
            i++;
        }//Coloca a chave no lugar certo.
         //acredito que testar até MAX_CHAVES não dê problema porque setei inicialmente todos os 
         //valores das chaves como nulo, porém não tenho certeza se posso colocar um inteiro como nulo em c
         //qualquer coisa, é só trocar os "NULL" por 0 depois

    }//testa se a subárvore não está cheia, vendo se há elemento na última posição das chaves


    //CASO 2 - árvore não possui espaço para colocar folha e necessita de um rearranjo*/
// }

// int testaFolha(Arvore_Doencas *a)
// {
/*
    for(int i=0;i<(2*T);i++){
        if(a->filhos[i]!=NULL){
            return 0;
        }
        
    }
    return 1;
*/
// }