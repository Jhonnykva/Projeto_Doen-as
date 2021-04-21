#include "Menu.h"

Menu *criaMenu()
{
  return NULL;
}

Menu *liberaMenu(Menu *menu)
{
  return NULL;
}

void adicionaPagina(int page, Menu *menu)
{
  MenuPage *p = (MenuPage *)malloc(sizeof(MenuPage));
  p->page = page;
  p->data = NULL;
  p->next = menu->pagesStack;
  menu->pagesStack = p;
}

void runMenu(Menu *menu)
{
  switch (menu->pagesStack->page)
  {
  case PTypePrincipal:
    _runPrincipal(menu);
    break;
  case PTypeRegDoenca:
    _runRegDoenca(menu);
    break;
  case PTypeMsg:
    _runMsg(menu);
    break;
  default:
    printf("Menu inválido\n");
    break;
  }
}

void _runPrincipal(Menu *menu)
{
  printf("Menu principal\n");
}

void _runRegDoenca(Menu *menu)
{
  printf("Menu Registro doenças\n");
}

void _runMsg(Menu *menu)
{
  printf("Mensagem\n");
}

int isEmpty(Menu *menu)
{
  return menu->pagesStack == NULL;
}