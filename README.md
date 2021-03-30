# Projeto Doenças

Projeto realizado para a matéria de **Estrutura de Dados II**. O projeto consiste em um sistema que permite relacionar doenças com seus respectivos sintomas, e possiveis remédios para tratamento.

## Integrantes

- Jhonny Kristyan Vaz-Tostes de Assis
- Matheus Kunnen Ledesma

## Utilidade

Facilitar pesquisas quando necessário para médicos ou até permitir consulta de pessoas não formadas para que se conscientizem de que problema possam estar passando.

## Metodologia

Uso de duas árvores b para armazenar doenças é remédios; além de uma tabela hash para os sintomas.
A tabela hash vai ter relações para diferentes doenças, onde a árvore vai ser utilizada para pesquisar de forma eficiente as mesmas. E o mesmo com doenças e remédios.

## Implementação

- ###s Estrutura de Doenças

```
    typedef struct doenca
    {
      unsigned int id;
      char nome[MAX_NOME];
      unsigned int n_sintomas;
      unsigned int *sintomas;

    } Doença;
```
