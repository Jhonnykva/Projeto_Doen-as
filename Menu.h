#include "include_principal.h"

#define PTypePrincipal 0
#define PTypeRegDoenca 1
#define PTypeMsg 2

typedef struct menu_page
{
  int page;
  void *data;
  struct menu_page *next;
} MenuPage;

typedef struct menu
{
  MenuPage *pagesStack;
} Menu;

Menu *criaMenu();
Menu *liberaMenu(Menu *menu);
void adicionaPagina(int page, Menu *menu);
void runMenu(Menu *menu);
void _runPrincipal(Menu *menu);
void _runRegDoenca(Menu *menu);
void _runMsg(Menu *menu);
int isEmpty(Menu *menu);