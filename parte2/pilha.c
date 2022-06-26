/*
Trabalho 2 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/

//TAD Pilha genérico para a criação da pilha de índices
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include "pilha.h"

struct pilha
{
    int topo;
    int *rrn;
};

pilha_t *cria_pilha()
{
    pilha_t *p = (pilha_t *)malloc(sizeof(pilha_t));
    assert(p != NULL); //retorna erro de cara se p == NULL

        p->topo = -1; //indica que a pilha está vazia
        p->rrn = malloc(1 * sizeof(int));

    return p;
}

void destruir_pilha(pilha_t *p)
{
    if (p != NULL)
        free(p);
}

int pilha_vazia(pilha_t *p)
{
    assert(p != NULL);
    if (p->topo == -1)
        return 1;
    else
        return 0;
}

int push(pilha_t *p, int x)
{
    assert(p != NULL);

    p->topo = p->topo + 1;
    p->rrn = (int *)realloc(p->rrn, (p->topo + 1) * sizeof(int));
    p->rrn[p->topo] = x;

    return 1;
}

int pop(pilha_t *p, int *x)
{
    assert(p != NULL);

    if (pilha_vazia(p) == 1)
    {
        return -1;
    }
    *x = p->rrn[p->topo];
    p->topo -= 1; //remover um elemento do topo
    return 1;
}

int top(pilha_t *p, int *x)
{
    assert(p != NULL);

    if (pilha_vazia(p) == 1)
    {
        return -1;
    }
    *x = p->rrn[p->topo]; //consultar elemento do topo da pilha
         return 1;
}
