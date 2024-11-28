#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
//#include "lista_dupla.h"

struct grafo
{
    int nro_vertices;
    bool eh_valorado; //
    bool eh_orientado;
    // char nome_vertice[nro_vertices][100];
    char **nome_vertice;
    int *vertice; //vetor de vertices numerico, substitui o nome_vertices
    // int matriz[nro_vertices][nro_vertices];
    int **matriz;
    int *visitado;
    int *estimativa;
    int *precedente;
    int nulo; // representa o valor nulo para esse grafo
};
typedef struct grafo Grafo;

Grafo cria_grafo(int nro_vertices,
                 bool eh_orientado,
                 bool eh_valorado, int nulo)
{
    Grafo g;
    int i, j;
    g.nro_vertices = nro_vertices;
    g.eh_orientado = eh_orientado;
    g.eh_valorado = eh_valorado;
    g.matriz = (int **)malloc(sizeof(int *) * nro_vertices);
    g.nome_vertice = (char **)malloc(sizeof(char *) * nro_vertices);
    g.vertice = (int *)malloc(sizeof(int) * nro_vertices);
    g.visitado = (int *)malloc(sizeof(int) * nro_vertices);
    g.estimativa = (int *)malloc(sizeof(int) * nro_vertices);
    g.precedente = (int *)malloc(sizeof(int) * nro_vertices);

    g.nulo = nulo;

    for (i = 0; i < nro_vertices; i++)
    {
        g.matriz[i] = (int *)malloc(sizeof(int) * nro_vertices);
        g.nome_vertice[i] = (char *)malloc(sizeof(char) * 100);
        g.visitado[i] = 0;
        g.estimativa[i] = 0;
        g.precedente[i] = -1;
    }

    for (i = 0; i < nro_vertices; i++)
        for (j = 0; j < nro_vertices; j++)
            g.matriz[i][j] = nulo;
    return g;
}

void prenche_nome_vertices(Grafo g)
{
    int i;
    for (i = 0; i < g.nro_vertices; i++)
    {
        printf("Informe o nome do vertice: ");
        fflush(stdin);
        scanf("%s", g.nome_vertice[i]);
    }
}

void preenche_vertices(Grafo g)
{
    int i;
    for (i = 0; i < g.nro_vertices; i++)
        g.vertice[i] = i + 1;
}

void preenche_arestas(Grafo g)
{
    int i, j;
    for (i = 0; i < g.nro_vertices; i++)
        for (j = 0; j < g.nro_vertices; j++)
            scanf("%d", &g.matriz[i][j]);
}

void limpa(Grafo g)
{
    int i;
    for (i = 0; i < g.nro_vertices; i++)
    {
        g.visitado[i] = 0;
        g.estimativa[i] = INT_MAX;
        g.precedente[i] = -1;
    }
}
/*
aloca area para um int, copia para ela o valor do parametro
e devolve um ponteiro para a area criada ser colocada 
como info na estrutura nod da listad
*/
void* cria_info(int info)
{
    int *w = (int *)malloc(sizeof(int));
    *w = info;
    return w;
 
}
/*

Procedimento BUSCA-AMPlitue - largura (v)---- bfs
   visitado(v)  sim
   Colocar v em uma fila
   Enquanto fila não vazia faça
      w  retirar o elemento da frente da fila
      Para cada vértice i adjacente a w faça
         Se visitado(i) = não então
           visitado(i)  sim
           Colocar i no final da fila
         fim-se
      fim-para
   fim-enquanto
Fim

*/

// void bfs(Grafo g, int v) //v é a origem do percurso
// {

//     int i;
//     g.visitado[v] = 1;
//     Listad *fila = cria_listad();
//     int *info, *w = cria_info(v); 
//     insere_fim_listad(w, fila);
//     while (fila->ini != NULL)
//     {
//         w = remove_inicio_listad(fila)->info;
//         printf("%d ", *w);//printa o nro do vertice
//         for (i = 0; i < g.nro_vertices; i++)
//         {
//             if (g.matriz[*w][i] != g.nulo)
//             {
//                 if (!g.visitado[i])
//                 {
//                     g.visitado[i] = 1;
//                     info = cria_info(i);
//                     insere_fim_listad(info, fila);
//                 }
//             }
//         }
//     }
// }
/*
Procedimento PROF(nó v)
   visitado(v)  sim
   Para cada nó w adjacente a v faça
      Se visitado(w) = não então
         PROF(w)
   fim-para
Fim

*/
void dfs(Grafo g, int v)//v é a origem do percurso
{
    int w = 0;
    g.visitado[v] = 1;
    printf("%d ", v);
    for (w = 0; w < g.nro_vertices; w++)
    {
        if (g.matriz[v][w] != g.nulo)
        {
            if (!g.visitado[w])
            {
                dfs(g, w);
            }
        }
    }
}
int vertice_menor_estimativa(Grafo g) {
    int i, min_estimativa = INT_MAX, vertice = -1;

    for (i = 0; i < g.nro_vertices; i++) {
        if (!g.visitado[i] && g.estimativa[i] < min_estimativa) {
            min_estimativa = g.estimativa[i];
            vertice = i;
        }
    }
    return vertice;
}

/*
Seja G(V,A) um grafo orientado e s um vértice de G:
1. Atribua valor zero à estimativa do custo mínimo do vértice s (a raiz da busca) e infinito às demais estimativas;
2. Atribua um valor qualquer aos precedentes (o precedente de um vértice t é o vértice que precede t no caminho de custo mínimo de s para t);
3. Enquanto houver vértice aberto:
seja k um vértice ainda aberto cuja estimativa seja a menor dentre todos os vértices abertos;
feche o vértice k
Para todo vértice j ainda aberto que seja sucessor de k faça:
some a estimativa do vértice k com o custo do arco que une k a j;
caso esta soma seja melhor que a estimativa anterior para o vértice j, substitua-a e anote k como precedente de j.


*/

void dijkstra(Grafo g, int origem)
{
    int i, k, j, soma;
    for (i = 0; i < g.nro_vertices; i++)
    {
        g.estimativa[i] = INT_MAX;
    }
    g.estimativa[origem] = 0;

    int nro_vertices_abertos = g.nro_vertices;

    while (nro_vertices_abertos > 0)
    {
        k = vertice_menor_estimativa(g);
        g.visitado[k] = 1;
        nro_vertices_abertos--;
        for (j = 0; j < g.nro_vertices; j++)
        {
            if (!g.visitado[j] && g.matriz[k][j] != g.nulo)
            {
                soma = g.estimativa[k] + g.matriz[k][j];
                if (soma < g.estimativa[j])
                {
                    g.estimativa[j] = soma;
                    g.precedente[j] = k;
                }
            }
        }
    }
}

void mostra_caminho(Grafo g, int destino)
{

}


int coord_para_indice(int x, int y, int n) {
    return x * n + y;
}


void preenche_grafo(Grafo g, int **matriz, int n)
{
    int dir;
    int esq;
    int acima;
    int abaixo;
    int atual;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            atual = coord_para_indice(i, j, n);
            if (i > 0)
            { 
                acima = coord_para_indice(i - 1, j, n);
                g.matriz[atual][acima] = matriz[i - 1][j];
            }
            if (i < n - 1)
            { 
                abaixo = coord_para_indice(i + 1, j, n);
                g.matriz[atual][abaixo] = matriz[i + 1][j];
            }
            if (j > 0)
            { 
                esq = coord_para_indice(i, j - 1, n);
                g.matriz[atual][esq] = matriz[i][j - 1];
            }
            if (j < n - 1)
            { 
                dir = coord_para_indice(i, j + 1, n);
                g.matriz[atual][dir] = matriz[i][j + 1];
            }
        }
    }
}

int main() {   
    int num = 0;   
    int **mina;
    Grafo g;

    scanf("%i", &num);

    mina = (int **)malloc(sizeof(int *) * num);
    for (int i = 0; i < num; i++)
    {
        mina[i] = (int *)malloc(sizeof(int) * num);
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            scanf("%i", &mina[i][j]);
        }
    }    

    g = cria_grafo(pow(num,2), true, true, INT_MAX);   
 
    preenche_grafo(g,mina,num);   

    dijkstra(g, 0);    
    printf("%i\n", g.estimativa[num*num-1]);

    free(mina);
    return 0;
}

