#ifndef FilaDinamica_h
#define FilaDinamica_h

typedef struct nodo
{
    int reg;
    struct nodo * prox;
} nodo;

typedef struct
{
    nodo * inicio;
    nodo * fim;
} Fila;

Fila * criaFila();

void pushFila(Fila * f, int x);

int popFila(Fila * f);

void apagaFila(Fila * f);

#endif //FilaDinamica_h

