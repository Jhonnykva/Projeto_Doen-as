#include "sintomas.h"
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
        printf("Nao e possivel inserir sintoma, pois este sintoma ja existe\n");
        return;
    }
    else if(isFull(H)){
        printf("Nao e possivel inserir sintoma, pois a tabela esta cheia");
        return;
    }
    else{
        int localInsercao = funcaoHashSintoma(nomeSintoma, H->M);

        //CRIAÇÃO DE SITNOMA
        Sintoma *novoSintoma = (Sintoma*)malloc(sizeof(Sintoma));
        strcpy(novoSintoma->nome, nomeSintoma);
        H->N++;

        //TRATAMENTO DE COLISÃO
        while(H->estrutura_sintoma[localInsercao] != NULL /*||
              strcmp(H->estrutura_sintoma[localInsercao]->nome, "Sintoma Removido")!=0*/){
            localInsercao= (localInsercao+1)%(H->M);
        }
        //ARMAZENAMENTO DO NOME DO SINTOMA NO ARQUIVO DE NOMES
        FILE *arquivoNomeSintoma = fopen("ArquivoNomeSintoma.txt", "a");
        char fnomeSintoma[30] = "";
        strcat(fnomeSintoma, novoSintoma->nome);
        strcat(fnomeSintoma, ".txt");
        strcat(fnomeSintoma, "\0");
        fprintf(arquivoNomeSintoma, "%s\n", fnomeSintoma);
        fclose(arquivoNomeSintoma);

        //CRIAÇÃO DO ARQUIVO ESPECÍFICO DO SINTOMA

        FILE *fSintoma = fopen(fnomeSintoma, "w");
        fprintf(fSintoma, "%s\n", novoSintoma->nome);
        fclose(fSintoma);

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

        //REMOVENDO O SINTOMA DA TABELA
        H->estrutura_sintoma[fH]->nome[30]="Sintoma Removido";
        H->N--;
        printf("\nSintoma %s removido", nomeSintoma);

        //REMOVENDO SINTOMA DO ARQUIVO DE NOMES DE SINTOMAS
        //AJUSTAR DEPOIS
        FILE *arquivoNomeSintoma = fopen("ArquivoNomeSintoma.txt", "a+");
        char aux[100]= "",dadosArquivo[500]= "", fnSintoma[30]="";
        int i=0, j=0, posicao1=0, posicao2, contAux=0;

        strcat(fnSintoma, nomeSintoma);
        strcat(fnSintoma, ".txt");
        strcat(fnSintoma, "\0");
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

        fclose(arquivoNomeSintoma);
        //arquivoNomeSintoma = fopen("ArquivoNomeSintoma.txt", "w");
        //fputs(dadosArquivo, arquivoNomeSintoma);

        //REMOVENDO DELETANDO ARQUIVO ESPECÍFICO DO SINTOMA

        remove(fnSintoma);

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

void carregarTHSintoma(THSintomas *H){

    FILE *fNomeSintoma = fopen("ArquivoNomeSintoma.txt", "r+");
    char aux[50] = "", dadosArquivo[500] = "", aux2[50];
    int i=0, j=0;
    while(fgets(aux, 50, fNomeSintoma)!=NULL){
        strcat(dadosArquivo, aux);
    }
    while(dadosArquivo[i]!=NULL){
        while(dadosArquivo[i]!='.'){
            aux2[j]=dadosArquivo[i];
            i++;
            j++;
        }
        while(dadosArquivo[i]!='\n'){
            i++;
        }
        aux2[j]='\0';
        inserirSintoma(H, aux2);
        j=0;
        while(aux2[j]!=NULL){
            aux2[j]=NULL;
            j++;
        }
        j=0;
        i++;
    }


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
