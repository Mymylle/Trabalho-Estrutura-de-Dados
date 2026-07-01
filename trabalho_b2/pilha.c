#include <stdio.h>
#include <string.h>
#include "pilha.h"


int pilha_cheia(int topo)
{
    return (topo == MAX - 1);
}


int pilha_vazia(int topo)
{
    return (topo == -1);
}


int protocolo_existe(Chamada pilha[], int topo, int protocolo)
{
    int i;

    for (i = 0; i <= topo; i++) {
        if (pilha[i].protocolo == protocolo) {
            return 1;
        }
    }

    return 0;
}


int push(Chamada pilha[], int *topo, Chamada nova)
{
    if (pilha_cheia(*topo)) {
        return 0;
    }

    (*topo)++;
    pilha[*topo] = nova;

    return 1;
}


int pop(Chamada pilha[], int *topo, Chamada *removida)
{
    if (pilha_vazia(*topo)) {
        return 0;
    }

    *removida = pilha[*topo];
    (*topo)--;

    return 1;
}


int peek(Chamada pilha[], int topo, Chamada *consultada)
{
    if (pilha_vazia(topo)) {
        return 0;
    }

    *consultada = pilha[topo];

    return 1;
}

void listar(Chamada pilha[], int topo)
{
    int i;

    if (pilha_vazia(topo)) {
        printf("  Nenhuma chamada registrada na pilha.\n");
        return;
    }

    printf("  %-10s %-30s %-20s %-15s\n",
           "Protocolo", "Local", "Tipo", "Horario");
    printf("  ");

    for (i = 0; i < 78; i++) {
        printf("-");
    }

    printf("\n");

    for (i = topo; i >= 0; i--) {
        printf("  %-10d %-30s %-20s %-15s\n",
               pilha[i].protocolo,
               pilha[i].local,
               pilha[i].tipo,
               pilha[i].horario);
    }
}
