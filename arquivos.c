#include "arquivos.h"

FILE *cria_arquivo(){
    FILE* novoArquivo;
    return novoArquivo;
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


void imprimir_dados(int linha_inicial, int linha_final, FILE *arquivo){
    //esta função imprimi os dados do começo de uma linha até o final de outra linha
    int *v=vetor_linhas(arquivo);
    char c[1000];

    if(linha_final<linha_inicial){
        printf("ERROR: valor de linhas invalidos.\n");
    }
    fscanf(arquivo, "%s", c);
    printf("\n");
    for(int i=v[linha_inicial];i<v[linha_final+1]-1;i++){
        printf("%c", c[i]);
    }
}

FILE *inserir_dados(const char *dados, FILE *arquivo){
    //insere uma string de dados no arquivo
    fprintf(arquivo, "%s", dados);
    return arquivo;
}

void gerencia_arquivo(FILE *arquivo,const char nome[30]){
    //função responsável por agrupar as relações de um arquivo
    //ainda não sei como vai ser feito, pretendo criar todas as
    //outras funções que vão ser utilizadas e depois pensamos que implementar essa.
    arquivo = fopen(nome, "a");
    //...
    fclose(arquivo);
}