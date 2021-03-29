#include "Projeto_Doenças.h"

Arvore_Doencas Busca(Arvore *a, int chave){//busca alguma chave
    int i=0;
    while((i<a->n)&&(k>a->chave[i])){
        i++;
    }
    if((i<a->n)&&(k==a->chave[i])){
        printf("Encontrado");
    }
    else if(a->folha){
        printf("Nao-Encontrado");
    }
    else{
        return Busca(a->filhos[i], k);
    }
}

Arvore_Doencas *Inserir(Arvore_Doencas *a, int chave)

int main(){

}
