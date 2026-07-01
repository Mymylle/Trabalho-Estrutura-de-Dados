#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "fila.h"
#include "csv.h"

static Estatisticas stats = {0, 0, 0};

/* Lê inteiro e descarta o restante da linha */
static int lerInt(const char *prompt) {
    int v;
    printf("%s", prompt);
    while (scanf("%d", &v) != 1) {
        printf("Entrada invalida. %s", prompt);
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return v;
}

static void lerString(const char *prompt, char *dest, int max) {
    printf("%s", prompt);
    fgets(dest, max, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

static void adicionarProcesso(FilaCircular *f) {
    if (filaCheia(f)) {
        printf("Fila cheia.\n");
        return;
    }

    Processo p;
    p.pid = lerInt("PID: ");

    if (pidExiste(f, p.pid)) {
        printf("PID %d ja existe na fila.\n", p.pid);
        return;
    }

    lerString("Nome: ", p.nome, TAM_NOME);
    p.prioridade    = lerInt("Prioridade: ");
    p.tempoRestante = lerInt("Tempo de execucao: ");

    if (p.tempoRestante <= 0) {
        printf("Tempo invalido.\n");
        return;
    }

    enfileirar(f, p);
    printf("Processo %d adicionado.\n", p.pid);
}

/* Executa um ciclo Round-Robin: retira do inicio, desconta quantum, reinsere se necessario */
static void executarProximo(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("Nenhum processo na fila.\n");
        return;
    }

    Processo p;
    desenfileirar(f, &p);
    stats.rodadas++;

    int executado = (p.tempoRestante > QUANTUM) ? QUANTUM : p.tempoRestante;
    p.tempoRestante -= executado;

    printf("Executando PID %d (%s) por %d unidade(s). Tempo restante: %d\n",
           p.pid, p.nome, executado, p.tempoRestante);

    if (p.tempoRestante > 0) {
        enfileirar(f, p);
    } else {
        printf("Processo %d concluido.\n", p.pid);
        stats.concluidos++;
    }
}

static void cancelarProcesso(FilaCircular *f) {
    int pid = lerInt("PID a cancelar: ");
    if (removerPorPid(f, pid)) {
        printf("Processo %d cancelado.\n", pid);
        stats.cancelados++;
    }
}

static void exibirEstatisticas(void) {
    printf("\n  Rodadas executadas : %d\n", stats.rodadas);
    printf("  Processos concluidos: %d\n", stats.concluidos);
    printf("  Processos cancelados: %d\n\n", stats.cancelados);
}

static void exibirMenu(void) {
    printf("\n  Escalonador Round-Robin\n");
    printf("  -----------------------\n");
    printf("  1. Adicionar processo\n");
    printf("  2. Executar proximo (quantum)\n");
    printf("  3. Consultar proximo\n");
    printf("  4. Listar fila\n");
    printf("  5. Cancelar processo\n");
    printf("  6. Salvar CSV\n");
    printf("  7. Carregar CSV\n");
    printf("  8. Estatisticas\n");
    printf("  0. Sair\n");
    printf("  Opcao: ");
}

int main(void) {
    FilaCircular fila;
    inicializarFila(&fila);
    carregarCSV(&fila); /* tenta carregar dados da sessao anterior */

    int opcao;
    do {
        exibirMenu();
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Opcao: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("\n");

        switch (opcao) {
            case 1: adicionarProcesso(&fila);       break;
            case 2: executarProximo(&fila);          break;
            case 3: {
                Processo p;
                if (consultarProximo(&fila, &p))
                    printf("Proximo: PID %d (%s), tempo restante: %d\n",
                           p.pid, p.nome, p.tempoRestante);
                break;
            }
            case 4: listarFila(&fila);               break;
            case 5: cancelarProcesso(&fila);         break;
            case 6: salvarCSV(&fila);                break;
            case 7: carregarCSV(&fila);              break;
            case 8: exibirEstatisticas();            break;
            case 0: printf("Encerrando.\n");         break;
            default: printf("Opcao invalida.\n");    break;
        }
    } while (opcao != 0);

    return 0;
}
