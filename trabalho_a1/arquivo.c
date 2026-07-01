

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"


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

void carregarCSV(void)
{
    FILE  *arquivo;
    char   linha[300];
    char  *token;
    Musica m;
    int    numero_linha = 1;

    arquivo = fopen(NOME_ARQUIVO, "r");

    if (arquivo == NULL) {
        return;
    }

    quantidade = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL
           && quantidade < MAX_MUSICAS) {

        numero_linha++;

       
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) {
            continue;
        }

        /* id */
        token = strtok(linha, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (id ausente).\n", numero_linha);
            continue;
        }
        m.id = atoi(token);

        /*  titulo */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (titulo ausente).\n", numero_linha);
            continue;
        }
        strncpy(m.titulo, token, TAM_TITULO - 1);
        m.titulo[TAM_TITULO - 1] = '\0';

        /*artista */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (artista ausente).\n", numero_linha);
            continue;
        }
        strncpy(m.artista, token, TAM_ARTISTA - 1);
        m.artista[TAM_ARTISTA - 1] = '\0';

        /*  duracao */
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Aviso: linha %d ignorada (duracao ausente).\n", numero_linha);
            continue;
        }
        m.duracao = atoi(token);

        /* genero */
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
