#include "lista_dupla.h"

Listad *cria_listad()
{
    Listad *L = (Listad *)malloc(sizeof(Listad));
    L->ini = L->fim = NULL;
    return L;
}

Nod *cria_nod(void *info)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->info = info;
    novo->ant = novo->prox = NULL;
    return novo;
}

void insere_inicio_listad(void *info, Listad *L)
{
    Nod *novo = cria_nod(info);

    if (L->ini == NULL)
    {
        L->ini = L->fim = novo;
    }
    else
    {
        novo->prox = L->ini;
        L->ini->ant = novo;
        L->ini = novo;
    }
}

void insere_fim_listad(void *info, Listad *L)
{
    Nod *novo = cria_nod(info);

    if (L->ini == NULL)
    {
        L->ini = L->fim = novo;
    }
    else
    {
        novo->ant = L->fim;
        L->fim->prox = novo;
        L->fim = novo;
    }
}

Listad *libera_listad(Listad *L)
{
    Nod *aux;

    while (L->ini != NULL)
    {
        aux = L->ini;
        L->ini = L->ini->prox;
        free(aux);
    }
    free(L);
    return NULL;
}

Nod *remove_inicio_listad(Listad *L)
{
    Nod *aux = NULL;
    if (L != NULL && L->fim != NULL) // caso haja elemento
    {
        aux = L->ini;
        if (L->ini == L->fim)
        {
            L->ini = L->fim = NULL;
        }
        else
        {
            L->ini = L->ini->prox;
            L->ini->ant = NULL;
        }
    }
    return aux;
}

Nod *remove_fim_listad(Listad *L)
{
    Nod *aux;
    if (L->fim != NULL)
    {
        aux = L->fim;
       
        if (L->ini != L->fim)
        {
            L->fim = L->fim->ant;
            L->fim->prox = NULL;
        }
        
        else
        {
            L->ini = L->fim = NULL;
        }
        aux->prox = aux->ant = NULL;
    }
    return aux;
}

Listad *divide_listad(Listad *L, int qtde_elementos_primeira_lista)
{
    Listad *L2 = cria_listad();
    Nod *aux = L->ini;
    int i = 0;
    while (i < qtde_elementos_primeira_lista)
    {
        i++;
        aux = aux->prox;
    }
    L2->ini = aux;
    L2->fim = L->fim;
    L->fim = aux->ant;
    L2->ini->ant = NULL;
    L->fim->prox = NULL;
    return L2;
}
/*
void insere_ordenado(Listad *L, int *ch)
{

    Nod *aux = L->ini;
    Nod *novo_no;
    if (L->ini == NULL)
    {
        insere_inicio_listad(ch, L);
    }
    else
    {
        if (ch->valorChave < getChave(L->ini))
            insere_inicio_listad(ch, L);
        else if (ch->valorChave > getChave(L->fim))
            insere_fim_listad(ch, L);
        else
        {
            while (ch->valorChave > getChave(aux))
                aux = aux->prox;
            novo_no = cria_nod(ch);
            novo_no->ant = aux->ant;
            novo_no->prox = aux;
            aux->ant = novo_no;
            novo_no->ant->prox = novo_no;
        }
    }
}
*/