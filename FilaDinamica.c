#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaDinamica.h"

Fila * criaFila()
{
    Fila * f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void pushFila(Fila * f, int x)
{
    nodo * novo = (nodo*)malloc(sizeof(nodo));
    novo->reg = x;
    novo->prox = NULL;

    if(f->fim != NULL)
        f->fim->prox = novo;

    f->fim = novo;

    if(f->inicio == NULL)
        f->inicio = novo;
}

int popFila(Fila * f)
{
    int x = f->inicio->reg;
    nodo * prox = f->inicio->prox;
    free(f->inicio);
    f->inicio = prox;

    if(f->inicio == NULL)
        f->fim = NULL;

    return x;
}

void apagaFila(Fila * f)
{
    while(f->inicio != NULL)
    {
        nodo * aux = f->inicio->prox;
        free(f->inicio);
        f->inicio = aux;
    }
}
