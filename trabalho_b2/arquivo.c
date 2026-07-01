/*
 * arquivo.c
 * Funcoes responsaveis pela persistencia dos dados em arquivo CSV.
 * Implementa salvamento e carregamento da pilha de chamadas.
 *
 * Disciplina : Estrutura de Dados
 * Curso      : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre   : 3 semestre
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

/*
 * salvar_csv
 * Grava todas as chamadas da pilha no arquivo CSV.
 * O arquivo e sobrescrito a cada salvamento.
 * Parametros: pilha[] - vetor de chamadas.
 *             topo    - indice atual do topo.
 * Retorno   : 1 em caso de sucesso, 0 em caso de erro.
 */
int salvar_csv(Chamada pilha[], int topo)
{
    FILE *arquivo;
    int   i;

    arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("  ERRO: nao foi possivel abrir o arquivo para escrita.\n");
        return 0;
    }

    /* Grava o cabecalho conforme norma do trabalho */
    fprintf(arquivo, "%s\n", CABECALHO_CSV);

    /*
     * Grava da base ao topo para que, ao recarregar,
     * a ordem LIFO seja reconstituida corretamente.
     */
    for (i = 0; i <= topo; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                pilha[i].protocolo,
                pilha[i].local,
                pilha[i].tipo,
                pilha[i].horario);
    }

    fclose(arquivo);

    printf("  Dados salvos com sucesso em '%s'.\n", ARQUIVO_CSV);

    return 1;
}

/*
 * carregar_csv
 * Le o arquivo CSV e popula a pilha com os registros encontrados.
 * Linhas invalidas sao informadas e ignoradas.
 * Parametros: pilha[] - vetor de chamadas a ser preenchido.
 *             topo    - ponteiro para o indice do topo.
 * Retorno   : numero de registros carregados, ou -1 se arquivo nao existe.
 */
int carregar_csv(Chamada pilha[], int *topo)
{
    FILE   *arquivo;
    char    linha[256];
    char   *campo;
    Chamada temp;
    int     carregados = 0;
    int     numero_linha = 1; /* comeca em 1 pois linha 0 e cabecalho */

    arquivo = fopen(ARQUIVO_CSV, "r");

    if (arquivo == NULL) {
        /* Arquivo inexistente na primeira execucao: comportamento normal */
        return -1;
    }

    /* Ignora a primeira linha (cabecalho) */
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numero_linha++;

        /* Remove possivel '\n' ao final da linha */
        linha[strcspn(linha, "\n")] = '\0';

        /* Ignora linhas em branco */
        if (strlen(linha) == 0) {
            continue;
        }

        /* Campo 1: protocolo */
        campo = strtok(linha, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (protocolo ausente).\n",
                   numero_linha);
            continue;
        }
        temp.protocolo = atoi(campo);

        /* Campo 2: local */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (local ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.local, campo, sizeof(temp.local) - 1);
        temp.local[sizeof(temp.local) - 1] = '\0';

        /* Campo 3: tipo */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (tipo ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.tipo, campo, sizeof(temp.tipo) - 1);
        temp.tipo[sizeof(temp.tipo) - 1] = '\0';

        /* Campo 4: horario */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (horario ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.horario, campo, sizeof(temp.horario) - 1);
        temp.horario[sizeof(temp.horario) - 1] = '\0';

        /* Verifica protocolo duplicado antes de inserir */
        if (protocolo_existe(pilha, *topo, temp.protocolo)) {
            printf("  AVISO: protocolo %d ja existe. Linha %d ignorada.\n",
                   temp.protocolo, numero_linha);
            continue;
        }

        /* Insere na pilha */
        if (!push(pilha, topo, temp)) {
            printf("  AVISO: pilha cheia. Registros restantes nao carregados.\n");
            break;
        }

        carregados++;
    }

    fclose(arquivo);

    return carregados;
}
