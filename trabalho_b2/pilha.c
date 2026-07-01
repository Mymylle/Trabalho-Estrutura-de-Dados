/*
 * pilha.c
 * Implementacao das funcoes de manipulacao da pilha de chamadas
 * de emergencia: push, pop, peek, listagem e verificacoes.
 *
 * Disciplina : Estrutura de Dados
 * Curso      : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre   : 3 semestre
 */

#include <stdio.h>
#include <string.h>
#include "pilha.h"

/* ---------------------------------------------------------- */
/* Funcoes de controle da pilha                               */
/* ---------------------------------------------------------- */

/*
 * pilha_cheia
 * Verifica se a pilha atingiu sua capacidade maxima.
 * Parametro: topo - indice atual do topo da pilha.
 * Retorno  : 1 se cheia, 0 caso contrario.
 */
int pilha_cheia(int topo)
{
    return (topo == MAX - 1);
}

/*
 * pilha_vazia
 * Verifica se a pilha nao possui nenhum elemento.
 * Parametro: topo - indice atual do topo da pilha.
 * Retorno  : 1 se vazia, 0 caso contrario.
 */
int pilha_vazia(int topo)
{
    return (topo == -1);
}

/*
 * protocolo_existe
 * Percorre a pilha em busca de um protocolo ja cadastrado.
 * Parametros: pilha[]   - vetor de chamadas.
 *             topo      - indice do topo.
 *             protocolo - numero a ser verificado.
 * Retorno   : 1 se encontrado, 0 caso contrario.
 */
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

/* ---------------------------------------------------------- */
/* Operacoes principais da pilha                             */
/* ---------------------------------------------------------- */

/*
 * push
 * Insere uma nova chamada no topo da pilha.
 * Parametros: pilha[] - vetor de chamadas.
 *             topo    - ponteiro para o indice do topo.
 *             nova    - chamada a ser inserida.
 * Retorno   : 1 em caso de sucesso, 0 se a pilha estiver cheia.
 */
int push(Chamada pilha[], int *topo, Chamada nova)
{
    if (pilha_cheia(*topo)) {
        return 0;
    }

    (*topo)++;
    pilha[*topo] = nova;

    return 1;
}

/*
 * pop
 * Remove a chamada do topo da pilha e a retorna via ponteiro.
 * Parametros: pilha[]   - vetor de chamadas.
 *             topo      - ponteiro para o indice do topo.
 *             removida  - ponteiro para receber a chamada removida.
 * Retorno   : 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int pop(Chamada pilha[], int *topo, Chamada *removida)
{
    if (pilha_vazia(*topo)) {
        return 0;
    }

    *removida = pilha[*topo];
    (*topo)--;

    return 1;
}

/*
 * peek
 * Consulta a chamada do topo sem remover.
 * Parametros: pilha[]    - vetor de chamadas.
 *             topo       - indice atual do topo.
 *             consultada - ponteiro para receber a chamada.
 * Retorno   : 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int peek(Chamada pilha[], int topo, Chamada *consultada)
{
    if (pilha_vazia(topo)) {
        return 0;
    }

    *consultada = pilha[topo];

    return 1;
}

/*
 * listar
 * Exibe todas as chamadas da pilha do topo ate a base.
 * Parametros: pilha[] - vetor de chamadas.
 *             topo    - indice atual do topo.
 */
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

    /* Percorre do topo ate a base (LIFO) */
    for (i = topo; i >= 0; i--) {
        printf("  %-10d %-30s %-20s %-15s\n",
               pilha[i].protocolo,
               pilha[i].local,
               pilha[i].tipo,
               pilha[i].horario);
    }
}
