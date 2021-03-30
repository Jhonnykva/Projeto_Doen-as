//----------------------------- Tabela Hash Sintomas
typedef struct sintomas_node
{
  int k; //chave chave pesquisa
  struct node *next;
} sintomas_node;

typedef struct hash
{
  int N_Entradas;
  int N_Chaves_Armazenadas;
  sintomas_node **list;
} Hash;

Hash *create_hash(int N_Entradas);
void inserir(Hash *H, int k);