#ifndef TIPOS_H
#define TIPOS_H

#define CAPACIDADE  20
#define TAM_NOME    30
#define QUANTUM      2
#define ARQUIVO_CSV "processos.csv"

typedef struct {
    int  pid;
    char nome[TAM_NOME];
    int  prioridade;
    int  tempoRestante;
} Processo;

typedef struct {
    Processo dados[CAPACIDADE];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

typedef struct {
    int concluidos;
    int cancelados;
    int rodadas;
} Estatisticas;

#endif
