#include <stdio.h>
#include <stdlib.h>
#include "FilaDinamica.h"

int * visitado;
int * enfileirado;

nodo * insere(nodo * lista, int x)
{
    if(lista == NULL)
    {
        nodo * lista = (nodo*)malloc(sizeof(nodo));
        lista->prox = NULL;
        lista->reg = x;

        return lista;
    }
    else
    {
        lista->prox = insere(lista->prox, x);
        return lista;
    }
}

//execucao algoritmo de busca em profundidade
void DFS(nodo * ListaAdj[], int v, int * paiDFS)
{
    nodo * aux = ListaAdj[v];
    visitado[v] = 1;

    while(aux != NULL)
    {
        int pai = v;

        if(!visitado[aux->reg])
        {
            DFS(ListaAdj, aux->reg, paiDFS);
            paiDFS[aux->reg] = pai;
        }

        aux = aux->prox;
    }
}

//execucao algoritmo de busca em largura
void BFS(nodo ** ListaAdj, int r, int * paiBFS)
{
    int aux = 0;
    Fila * f = criaFila();

    pushFila(f, r);
    enfileirado[r] = 1;

    while(f->inicio != NULL)
    {
        aux = popFila(f);
        nodo * pLista = ListaAdj[aux];

        while(pLista != NULL)
        {
            if(enfileirado[pLista->reg] == 0)
            {
                pushFila(f, pLista->reg);
                enfileirado[pLista->reg] = 1;
                paiBFS[pLista->reg] = aux;
            }
            pLista = pLista->prox;
        }
    }

    apagaFila(f);
}

//preenchendo caminho do labirinto DFS
//retorna 0 se ficar preso, senao retorna a quantidade de passos
int preencheLabirinto(int filho, int N, int M, char ** matChar, int * vetPai)
{
    int cont = 0;
    int aux = filho;//cria-se aux da variavel filho pois ela sera usada novamente
    matChar[N][M] = 'x';//ultima posicao do labirinto está sempre vazia

    while(aux != 0)
    {
        if(aux == -1)
            return 0;

        int linha = vetPai[aux] / M;
        int coluna = vetPai[aux] % M;
        matChar[linha+1][coluna+1] = 'x';

        cont++;
        aux = vetPai[aux];
    }

    return cont;
}

//saidas na tela para o algoritmo DFS
void saidas(int N, int M, int passos, char ** matChar, int * vetPai)
{
    int i, j;

    //visualizar labirinto sem paredes
    for(i=1; i<N+1; i++)
    {
        for(j=1; j<M+1; j++)
        {
            printf("%c", matChar[i][j]);
        }
        printf("\n");
    }

    //imprimir passos
    printf("%d passo(s)\n", passos);

    //imprimir vetor de pai
    for(i=0; i<N*M; i++)
        printf("%d ", vetPai[i]);
}

//desfazendo caminho percorrido pela DFS
void desfazCaminho(int filho, int M, char ** matChar, int * vetPai)
{
    int aux = filho;

    while(aux != 0)
    {
        int linha = vetPai[aux] / M;
        int coluna = vetPai[aux] % M;
        matChar[linha+1][coluna+1] = '.';

        aux = vetPai[aux];
    }
}

void apagaLista(nodo * lista)
{
    if(lista == NULL)
        return;

    apagaLista(lista->prox);
    free(lista);
}

int main()
{
    int N, M, i, j, c, k;
    scanf("%d %d", &N, &M);

    //matriz de caracteres para o labirinto recebe mais duas linhas e duas colunas para criar paredes em volta
    char ** matChar = (char**)malloc((N+2) * sizeof(char*));
    int ** matNum = (int**)malloc(N * sizeof(int*));
    nodo ** ListaAdj = (nodo**)malloc((N*M) * sizeof(nodo*));
    visitado = (int*)malloc((N*M) * sizeof(int));
    int * paiDFS = (int*)malloc((N*M) * sizeof(int));
    int * paiBFS = (int*)malloc((N*M) * sizeof(int));
    enfileirado = (int*)malloc((N*M) * sizeof(int));

    //criando labirinto com paredes
    for(i=0; i<N+2; i++)
    {
        matChar[i] = (char*)malloc((M+2) * sizeof(char));

        for(j=0; j<M+2; j++)
        {
            if(i == 0 || i == N+1 || j == 0 || j == M+1)
                matChar[i][j] = '#';
        }
    }

    //preenchendo labirinto
    for(i=1; i<N+1; i++)
    {
        while((c = getchar()) != '\n' && c != EOF);//limpa buffer de entrada

        for(j=1; j<M+1; j++)
        {
            scanf("%c", &matChar[i][j]);
        }
    }

    //criando matriz enumerada, lista de adjacencias e inicializando vetores
    k = 0;
    for(i=0; i<N; i++)
    {
        matNum[i] = (int*)malloc(M * sizeof(int));

        for(j=0; j<M; j++)
        {
            paiDFS[k] = -1;
            paiBFS[k] = -1;
            visitado[k] = 0;
            enfileirado[k] = 0;
            matNum[i][j] = k++;
            ListaAdj[i] = NULL;
        }
    }

    //implementando lista de adjacencias. Usa como matriz auxiliar a matriz enumerada criada acima
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            if(matChar[i+1][j+1] == '.')
            {
                //vizinhos a esquerda
                if(matChar[i+1][j] == '.')
                    ListaAdj[(matNum[i][j])] = insere(ListaAdj[(matNum[i][j])], matNum[i][j-1]);

                //vizinhos a direita
                if(matChar[i+1][j+2] == '.')
                    ListaAdj[(matNum[i][j])] = insere(ListaAdj[(matNum[i][j])], matNum[i][j+1]);

                //vizinhos acima
                if(matChar[i][j+1] == '.')
                    ListaAdj[(matNum[i][j])] = insere(ListaAdj[(matNum[i][j])], matNum[i-1][j]);

                //vizinhos abaixo
                if(matChar[i+2][j+1] == '.')
                    ListaAdj[(matNum[i][j])] = insere(ListaAdj[(matNum[i][j])], matNum[i+1][j]);
            }
        }
    }

    DFS(ListaAdj, 0, paiDFS);
    int filho = (N*M)-1;
    int passos = preencheLabirinto(filho, N, M, matChar, paiDFS);

    if(passos == 0)
    {
        printf("voce esta preso!");
        return 0;
    }

    saidas(N, M, passos, matChar, paiDFS);
    desfazCaminho(filho, M, matChar, paiDFS);
    printf("\n\n");

    //BFS nao precisa checar se 'passos' retorna 0 pois essa condicao foi checada anteriormente
    BFS(ListaAdj, 0, paiBFS);
    passos = preencheLabirinto(filho, N, M, matChar, paiBFS);
    saidas(N, M, passos, matChar, paiBFS);

    //desalocando memória
    free(paiDFS);
    free(paiBFS);
    free(visitado);
    free(enfileirado);

    for(i=0; i<(N+2); i++)
        free(matChar[i]);

    for(i=0; i<N*M; i++)
        apagaLista(ListaAdj[i]);

     for(i=0; i<N; i++)
        free(matNum[i]);

    return 0;
}
