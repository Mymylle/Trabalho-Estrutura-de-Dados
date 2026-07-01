/*
 * arquivo.c
 * Funcoes de persistencia: salvar e carregar a playlist em arquivo CSV.
 *
 * Disciplina : Estrutura de Dados
 * Curso      : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre   : 3 semestre
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

/*
 * salvarCSV
 * Grava todas as musicas da playlist no arquivo CSV.
 * O arquivo e sobrescrito a cada salvamento.
 * Formato: id;titulo;artista;duracao;genero
 */
void salvarCSV(void)
{
    FILE *arquivo;
    int   i;

    arquivo = fopen(NOME_ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    fprintf(arquivo, "id;titulo;artista;duracao;genero\n");

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%s\n",
                playlist[i].id,
                playlist[i].titulo,
                playlist[i].artista,
                playlist[i].duracao,
                playlist[i].genero);
    }

    fclose(arquivo);
    printf("\nPlaylist salva no arquivo \"%s\" com sucesso!\n", NOME_ARQUIVO);
}

/*
 * carregarCSV
 * Le o arquivo CSV e reconstroi o vetor de musicas.
 * A primeira linha (cabecalho) e ignorada.
 * Linhas invalidas sao informadas e puladas.
 */
void carregarCSV(void)
{
    FILE  *arquivo;
    char   linha[300];
    char  *token;
    Musica m;
    int    numero_linha = 1;

    arquivo = fopen(NOME_ARQUIVO, "r");

    if (arquivo == NULL) {
        /* arquivo nao existe ainda: comportamento normal na primeira execucao */
        return;
    }

    quantidade = 0;

    /* ignora a linha de cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL
           && quantidade < MAX_MUSICAS) {

        numero_linha++;

        /* remove o '\n' do final */
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) {
            continue;
        }

        /* campo 1: id */
        token = strtok(linha, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (id ausente).\n", numero_linha);
            continue;
        }
        m.id = atoi(token);

        /* campo 2: titulo */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (titulo ausente).\n", numero_linha);
            continue;
        }
        strncpy(m.titulo, token, TAM_TITULO - 1);
        m.titulo[TAM_TITULO - 1] = '\0';

        /* campo 3: artista */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (artista ausente).\n", numero_linha);
            continue;
        }
        strncpy(m.artista, token, TAM_ARTISTA - 1);
        m.artista[TAM_ARTISTA - 1] = '\0';

        /* campo 4: duracao */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (duracao ausente).\n", numero_linha);
            continue;
        }
        m.duracao = atoi(token);

        /* campo 5: genero */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (genero ausente).\n", numero_linha);
            continue;
        }
        strncpy(m.genero, token, TAM_GENERO - 1);
        m.genero[TAM_GENERO - 1] = '\0';

        playlist[quantidade] = m;
        quantidade++;
    }

    fclose(arquivo);
    printf("Playlist carregada do arquivo \"%s\" (%d musica(s)).\n",
           NOME_ARQUIVO, quantidade);
}
