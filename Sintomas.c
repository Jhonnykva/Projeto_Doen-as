// #include "Sintomas.h"

// Hash *create_hash(int M){
//     Hash *newHash = (Hash*)malloc(sizeof(Hash));
//     newHash->M = M;
//     newHash->N = 0;
//     newHash->list = (Sintomas_node**)malloc(M*sizeof(Sintomas_node*));
//     for(int i=0; i< newHash->M; i++){
//         newHash->list[i]=NULL;
//     }
//     return newHash;
// }

// void insert_sintoma(Hash *H,const char *sintoma){
//     int valueSintoma = hash_function(sintoma, H->M);
//     Sintomas_node *newSN = (Sintomas_node*) malloc(sizeof(Sintomas_node));
//     strcpy(newSN->sintoma, sintoma);
//     newSN->next = H->list[valueSintoma];
//     H->list[valueSintoma] = newSN;
//     H->N++;//talvez seja retirado
// }

// int hash_function (char *sintoma, int M) {
//     int i;
//     int s = sintoma[0];
//     for (i = 1; sintoma[i] != '\0'; i++){
//         s = ((s * 256) + sintoma[i]) % M;
//     }
//     return s;
// }
