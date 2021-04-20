#include "Sintomas.h"
//--------TABELA HASH - FUNÇÕES PRINCIPAIS
int funcaoHashSintoma(char nome_sintoma[], int M) {

    int i, s=0;
    for (i = 0; nome_sintoma[i] != '\0'; i++){
        s+=nome_sintoma[i];
    }
    return (s%M);
}

THSintomas *criarTHSintomas(int M){
    THSintomas *novaTabela =(THSintomas*)malloc(sizeof(THSintomas));
    novaTabela->M=M;
    novaTabela->N=0;
    novaTabela->estrutura_sintoma = (Sintoma**)malloc(M*sizeof(Sintoma*));
    for(int i=0; i< novaTabela->M; i++){
        //seta todos os ponteiros da lista pra nulo
        novaTabela->estrutura_sintoma[i]=NULL;
    }
    return novaTabela;
}


void inserirSintoma(THSintomas *H, char nomeSintoma[]){
    //esta função adiciona o sintoma a tabela hash e cria o
    //arquivo que representa este sintoma
    if(verificaSintomaExistente(nomeSintoma, H)){
        printf("Nao e possivel inserir sintoma, pois este sintoma ja existe");
        return;
    }
    else if(isFull(H)){
        printf("Nao é possivel inserir sintoma, pois a tabela está cheia");
        return;
    }
    else{
        int localInsercao = funcaoHashSintoma(nomeSintoma, H->M);

        //CRIAÇÃO E ARMAZENAMENTO DE SITNOMA
        Sintoma *novoSintoma = (Sintoma*)malloc(sizeof(Sintoma));
        strcpy(novoSintoma->nome, nomeSintoma);
        H->N++;
        /*
        FILE *arquivoSintoma = fopen(gerarNomeSintoma(nomeSintoma), "w");
        fprintf(arquivoSintoma, "%s\n", novoSintoma->nome);
        fclose(arquivoSintoma);*/

        //TRATAMENTO DE COLISÃO
        while(H->estrutura_sintoma[localInsercao] != NULL /*||
              strcmp(H->estrutura_sintoma[localInsercao]->nome, "Sintoma Removido")!=0*/){
            localInsercao= (localInsercao+1)%(H->M);
        }
        //ANEXANDO O SINTOMA À TABELA
        H->estrutura_sintoma[localInsercao]=novoSintoma;
        printf("\nSintoma %s inserido", nomeSintoma);
    }
}

void removerSintoma(THSintomas *H, char nomeSintoma[]){
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    if(H->estrutura_sintoma[fH]==NULL)
        printf("\nSintoma nao removido porque não existe.\n");
    else{
        //remove(gerarNomeSintoma(nomeSintoma));
        //remove está comentado pois só funciona em linux
        H->estrutura_sintoma[fH]->nome[30]="Sintoma Removido";
        H->N--;
        printf("\nSintoma %s removido", nomeSintoma);
    }
}

void buscarSintoma(THSintomas *H, char nomeSintoma[]){
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    int encontrado=0;
    if(H->estrutura_sintoma[fH]==NULL){
        printf("\nSintoma %s nao existente", nomeSintoma);
    }
    else{

        while(H->estrutura_sintoma[fH]!=NULL || strcmp(nomeSintoma, H->estrutura_sintoma[fH]->nome)!=0){
            if(strcmp(nomeSintoma, H->estrutura_sintoma[fH]->nome)==0){
                encontrado=1;
                break;
            }
            else{
                fH++;
            }

        }
    }
    if(encontrado==1){
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

void freeTHSintomas(THSintomas *H){
    for(int i=0;i<H->M;i++){
        free(H->estrutura_sintoma[i]);
    }
    free(H);
}

//--------TABELA HASH - FUNÇÕES SECUNDÁRIAS
int verificaSintomaExistente(char sintoma[], THSintomas *H){
    //verifica se um dado sintoma já existe verificando o seu nome
    if((H->estrutura_sintoma[funcaoHashSintoma(sintoma, H->M)]!= NULL)
       && (strcpy(sintoma, H->estrutura_sintoma[funcaoHashSintoma(sintoma, H->M)]->nome)==0))
        return 1;
    //trocar o valor do strcpm assim que possuir acesso ao nome
    else
        return 0;
}

int isFull(THSintomas *H){
    if(H->N >= H->M)
        return 1;
    else
        return 0;
}

void imprimirTHCompleta(THSintomas *H){
    printf("\n\nTabela Completa: \n");
    for(int i=0; i<H->M; i++){
        if(H->estrutura_sintoma[i]!=NULL){
            printf("%d - %s\n", i, H->estrutura_sintoma[i]->nome);
        }
    }
}

//-------ARQUIVOS---------
char *gerarNomeSintoma(const char nomeSintoma[]){
    //adiciona ".txt" à string do nome do sintoma para fazer um arquivo
    char nome[30] = "";
    strcat(nome, nomeSintoma);
    strcat(nome, ".txt");
    return nome;
}

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
}

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
}
