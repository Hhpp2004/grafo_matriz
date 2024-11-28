#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H
#include <stdio.h>
#include <stdlib.h>
struct nod
{
    void* info;
    struct nod *prox;
    struct nod *ant;
};
typedef struct nod Nod;
struct listad
{
    Nod *ini, *fim;
};
typedef struct listad Listad;
Listad* cria_listad();
Nod* cria_nod(void* info);
void insere_inicio_listad(void* info, Listad *L);
void insere_fim_listad(void* info, Listad *L);
Nod* remove_inicio_listad(Listad *L);
Nod* remove_fim_listad(Listad *L);
Listad* libera_listad(Listad *L);
Listad* divide_listad(Listad *L, int n);


#endif