#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "fila.h"

/*
 * Função responsável por exportar os processos da fila para um ficheiro de texto (.csv)
 * Utiliza o ponto e vírgula (;) como separador de colunas
 */
int salvarCSV(const FilaCircular *f) {
    /* * Abre o ficheiro em modo de escrita ("w" ou write)
     * Se o ficheiro já existir, o seu conteúdo é apagado e reescrito
     * Se não existir, é criado um novo
     */
    FILE *arq = fopen(ARQUIVO_CSV, "w");
    if (!arq) {
        printf("Erro ao abrir ficheiro para escrita.\n");
        return 0;
    }

    /* Escreve a primeira linha do ficheiro, que serve apenas como cabeçalho das colunas */
    fprintf(arq, "pid;nome;prioridade;tempoRestante\n");

    /* Percorre todos os elementos válidos que estão atualmente na fila circular */
    for (int i = 0; i < f->quantidade; i++) {
        /* * Calcula a posição real do processo no vetor (array)
         * A operação módulo (% CAPACIDADE) é essencial aqui para garantir que o 
         * índice dá a volta ao vetor se ultrapassar o final
         */
        int idx = (f->inicio + i) % CAPACIDADE;
        const Processo *p = &f->dados[idx];
        
        /* Escreve os dados do processo separados por ponto e vírgula, com uma quebra de linha no fim */
        fprintf(arq, "%d;%s;%d;%d\n", p->pid, p->nome, p->prioridade, p->tempoRestante);
    }

    /* Fecha o ficheiro para libertar a memória e garantir que os dados são guardados no disco */
    fclose(arq);
    printf("Fila guardada em '%s'.\n", ARQUIVO_CSV);
    return 1;
}

/*
 * Função responsável por importar os processos de um ficheiro CSV de volta para a memória
 * Lê o texto e reconstrói as estruturas de dados (structs) na Fila Circular
 */
int carregarCSV(FilaCircular *f) {
    /* Abre o ficheiro em modo de leitura ("r" - read). */
    FILE *arq = fopen(ARQUIVO_CSV, "r");
    if (!arq) {
        /* Se o ficheiro não for encontrado (ex: primeira vez a executar o programa), 
           retorna 0 sem gerar erros graves. */
        return 0;
    }

    char linha[128];
    
    /* Lê a primeira linha do ficheiro (o cabeçalho) e descarta-a, pois não contém dados dos processos */
    fgets(linha, sizeof(linha), arq); 

    /* Garante que a fila está completamente limpa antes de começar a inserir os processos importados */
    inicializarFila(f);

    /* Lê o ficheiro linha a linha até não haver mais texto (fim do ficheiro) */
    while (fgets(linha, sizeof(linha), arq)) {
        Processo p;

        if (sscanf(linha, "%d;%29[^;];%d;%d",
                   &p.pid, p.nome, &p.prioridade, &p.tempoRestante) == 4) {
            
            enfileirar(f, p);
        }
    }

    /* Fecha o ficheiro após a leitura estar concluída */
    fclose(arq);
    printf("Fila carregada de '%s'.\n", ARQUIVO_CSV);
    return 1;
}