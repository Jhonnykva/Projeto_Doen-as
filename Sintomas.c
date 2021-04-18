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
        exit(1);
    }
    else if(isFull(H)){
        printf("Nao é possivel inserir sintoma, pois a tabela está cheia");
    }
    else{
        int localInsercao = funcaoHashSintoma(nomeSintoma, H->M);

        //criação e armazenamento do sintoma
        Sintoma *novoSintoma = (Sintoma*)malloc(sizeof(Sintoma));
        strcpy(novoSintoma->nome, nomeSintoma);
        H->N++;

        FILE *arquivoSintoma = fopen(gerarNomeSintoma(nomeSintoma), "w");
        fprintf(arquivoSintoma, "%s\n", novoSintoma->nome);
        fclose(arquivoSintoma);

        H->estrutura_sintoma[localInsercao]=novoSintoma;
    }
}

void removerSintoma(THSintomas *H, char nomeSintoma[]){
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    if(H->estrutura_sintoma[fH]==NULL)
        printf("\nSintoma nao removido porque não existe.\n");
    else{
        //remove(gerarNomeSintoma(nomeSintoma));
        //remove está comentado pois só funciona em linux
        H->estrutura_sintoma[fH]->nome[30]="";
        H->estrutura_sintoma[fH]=NULL;
        H->N--;
    }
}

void buscarSintoma(THSintomas *H, char nomeSintoma[]){
    int fH = funcaoHashSintoma(nomeSintoma, H->M);
    if(strcmp(nomeSintoma, H->estrutura_sintoma[fH])==0){
        FILE *arquivoSintoma = fopen((const)gerarNomeSintoma(nomeSintoma), "r");
        if(arquivoSintoma!= NULL)
            printf("arquivo feito e aberto");
        int *vetorNLinhas = vetor_linhas(arquivoSintoma);

        printf("\n\n\nSintoma encontrado: ");
        printf("\nnome: %s", H->estrutura_sintoma[fH]->nome);
        printf("\nDoencas associadas: ");
        /*imprimirDadosArquivoSintoma(1, 10, arquivoSintoma, vetorNLinhas);
        printf("\n");*/
        fclose(arquivoSintoma);
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
