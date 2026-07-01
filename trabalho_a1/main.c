/*
 * main.c
 * Arquivo principal do sistema de playlist de musicas.
 * Declara o vetor de musicas e a variavel de controle,
 * e executa o loop principal do menu.
 *
 * Tema      : A1 - Playlist de Musicas
 * Disciplina: Estrutura de Dados
 * Curso     : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre  : 3 semestre
 */

#include <stdio.h>
#include "playlist.h"

/*
 * Declaracao do vetor de musicas e da variavel de controle.
 * Sao definidas aqui e referenciadas nos outros arquivos via extern.
 */
Musica playlist[MAX_MUSICAS];
int    quantidade = 0;

int main(void)
{
    int opcao;

    carregarCSV(); /* tenta carregar dados salvos anteriormente */

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                inserirMusica();
                break;
            case 2:
                listarMusicas();
                break;
            case 3:
                buscarMusica();
                break;
            case 4:
                editarMusica();
                break;
            case 5:
                excluirMusica();
                break;
            case 6:
                salvarCSV();
                break;
            case 0:
                salvarCSV();
                printf("\nDados salvos. Saindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
