// //----------------------------- Tabela Hash Sintomas
// typedef struct sintomas_node
// {
//   char sintoma[50]; //chave pesquisa
//   struct sintomas_node *next;
// } Sintomas_node;

// typedef struct hash
// {
//   int M;//entradas
//   int N;//chaves
//   Sintomas_node **list;
// } Hash;

// Hash *create_hash(int M);
// void inserir(Hash *H,const char *sintoma);
// int funcaoHash(const char *sintoma,int M);