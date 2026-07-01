#include <stdio.h>
#include <string.h>
#include "fila.h"

void inicializarFila(FilaCircular *f) {
    f->inicio    = 0;
    f->fim       = 0;
    f->quantidade = 0;
}

int filaVazia(const FilaCircular *f) { return f->quantidade == 0; }
int filaCheia(const FilaCircular *f) { return f->quantidade == CAPACIDADE; }

int enfileirar(FilaCircular *f, Processo p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Processo %d nao pode ser adicionado.\n", p.pid);
        return 0;
    }
    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % CAPACIDADE;
    f->quantidade++;
    return 1;
}

int desenfileirar(FilaCircular *f, Processo *saida) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return 0;
    }
    *saida = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE;
    f->quantidade--;
    return 1;
}

int consultarProximo(const FilaCircular *f, Processo *saida) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return 0;
    }
    *saida = f->dados[f->inicio];
    return 1;
}

void listarFila(const FilaCircular *f) {
    if (filaVazia(f)) {
        printf("Fila de prontos vazia.\n");
        return;
    }
    printf("\n  %-6s  %-20s  %-10s  %s\n", "PID", "Nome", "Prioridade", "Tempo Rest.");
    printf("  %-6s  %-20s  %-10s  %s\n",
           "------", "--------------------", "----------", "-----------");
    for (int i = 0; i < f->quantidade; i++) {
        int idx = (f->inicio + i) % CAPACIDADE;
        const Processo *p = &f->dados[idx];
        printf("  %-6d  %-20s  %-10d  %d\n",
               p->pid, p->nome, p->prioridade, p->tempoRestante);
    }
    printf("\n  %d processo(s) na fila.\n", f->quantidade);
}

int pidExiste(const FilaCircular *f, int pid) {
    for (int i = 0; i < f->quantidade; i++) {
        if (f->dados[(f->inicio + i) % CAPACIDADE].pid == pid)
            return 1;
    }
    return 0;
}

/* Remove processo pelo PID reconstruindo a fila sem ele */
int removerPorPid(FilaCircular *f, int pid) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return 0;
    }

    Processo temp[CAPACIDADE];
    int novo = 0, encontrou = 0;

    for (int i = 0; i < f->quantidade; i++) {
        int idx = (f->inicio + i) % CAPACIDADE;
        if (f->dados[idx].pid == pid && !encontrou)
            encontrou = 1;
        else
            temp[novo++] = f->dados[idx];
    }

    if (!encontrou) {
        printf("PID %d nao encontrado.\n", pid);
        return 0;
    }

    f->inicio    = 0;
    f->fim       = novo;
    f->quantidade = novo;
    for (int i = 0; i < novo; i++)
        f->dados[i] = temp[i];

    return 1;
}
