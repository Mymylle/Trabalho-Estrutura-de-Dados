/*
 * lista.c
 * Operacoes sobre o vetor de musicas:
 * inserir, listar, buscar por ID, editar e excluir.
 *
 * Disciplina : Estrutura de Dados
 * Curso      : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre   : 3 semestre
 */

#include <stdio.h>
#include <string.h>
#include "playlist.h"

/*
 * buscarPorId
 * Percorre o vetor procurando o ID informado.
 * Retorna o indice da musica, ou -1 se nao encontrar.
 */
int buscarPorId(int id)
{
    int i;
    for (i = 0; i < quantidade; i++) {
        if (playlist[i].id == id) {
            return i;
        }
    }
    return -1;
}

/*
 * inserirMusica
 * Cadastra uma nova musica no final do vetor.
 * Verifica se ha espaco e se o ID ja existe antes de inserir.
 */
void inserirMusica(void)
{
    Musica nova;

    printf("\n--- Inserir Nova Musica ---\n");

    if (quantidade >= MAX_MUSICAS) {
        printf("Playlist cheia! Nao e possivel inserir mais musicas.\n");
        return;
    }

    nova.id = lerInteiro("ID da musica: ");

    if (buscarPorId(nova.id) != -1) {
        printf("Erro: ja existe uma musica com o ID %d!\n", nova.id);
        return;
    }

    lerTexto("Titulo: ",  nova.titulo,  TAM_TITULO);
    lerTexto("Artista: ", nova.artista, TAM_ARTISTA);
    nova.duracao = lerInteiro("Duracao (em segundos): ");
    lerTexto("Genero: ",  nova.genero,  TAM_GENERO);

    playlist[quantidade] = nova;
    quantidade++;

    printf("\nMusica cadastrada com sucesso!\n");
}

/*
 * listarMusicas
 * Exibe todas as musicas cadastradas em formato de tabela.
 * A duracao e convertida de segundos para MM:SS.
 */
void listarMusicas(void)
{
    int i;
    int min, seg;

    printf("\n--- Playlist Atual ---\n");

    if (quantidade == 0) {
        printf("A playlist esta vazia.\n");
        return;
    }

    printf("%-5s %-25s %-25s %-10s %-15s\n",
           "ID", "TITULO", "ARTISTA", "DURACAO", "GENERO");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < quantidade; i++) {
        min = playlist[i].duracao / 60;
        seg = playlist[i].duracao % 60;
        printf("%-5d %-25s %-25s %02d:%02d      %-15s\n",
               playlist[i].id,
               playlist[i].titulo,
               playlist[i].artista,
               min, seg,
               playlist[i].genero);
    }

    printf("\nTotal de musicas: %d\n", quantidade);
}

/*
 * buscarMusica
 * Le um ID do usuario e exibe os dados da musica correspondente.
 */
void buscarMusica(void)
{
    int id, pos;

    printf("\n--- Buscar Musica ---\n");
    id  = lerInteiro("Digite o ID da musica: ");
    pos = buscarPorId(id);

    if (pos == -1) {
        printf("Musica com ID %d nao encontrada.\n", id);
        return;
    }

    printf("\nMusica encontrada:\n");
    printf("ID......: %d\n",   playlist[pos].id);
    printf("Titulo..: %s\n",   playlist[pos].titulo);
    printf("Artista.: %s\n",   playlist[pos].artista);
    printf("Duracao.: %d segundos (%d:%02d)\n",
           playlist[pos].duracao,
           playlist[pos].duracao / 60,
           playlist[pos].duracao % 60);
    printf("Genero..: %s\n",   playlist[pos].genero);
}

/*
 * editarMusica
 * Permite alterar um campo especifico de uma musica existente.
 * O ID nao pode ser alterado.
 */
void editarMusica(void)
{
    int id, pos, opcao;

    printf("\n--- Editar Musica ---\n");
    id  = lerInteiro("Digite o ID da musica que deseja editar: ");
    pos = buscarPorId(id);

    if (pos == -1) {
        printf("Musica com ID %d nao encontrada.\n", id);
        return;
    }

    printf("\nMusica atual:\n");
    printf("1 - Titulo : %s\n", playlist[pos].titulo);
    printf("2 - Artista: %s\n", playlist[pos].artista);
    printf("3 - Duracao: %d segundos\n", playlist[pos].duracao);
    printf("4 - Genero : %s\n", playlist[pos].genero);
    printf("0 - Cancelar\n");

    opcao = lerInteiro("\nQual campo deseja editar? ");

    switch (opcao) {
        case 1:
            lerTexto("Novo titulo: ", playlist[pos].titulo, TAM_TITULO);
            break;
        case 2:
            lerTexto("Novo artista: ", playlist[pos].artista, TAM_ARTISTA);
            break;
        case 3:
            playlist[pos].duracao = lerInteiro("Nova duracao (segundos): ");
            break;
        case 4:
            lerTexto("Novo genero: ", playlist[pos].genero, TAM_GENERO);
            break;
        case 0:
            printf("Edicao cancelada.\n");
            return;
        default:
            printf("Opcao invalida! Nenhuma alteracao foi feita.\n");
            return;
    }

    printf("\nMusica atualizada com sucesso!\n");
}

/*
 * excluirMusica
 * Remove uma musica do vetor deslocando os elementos posteriores
 * uma posicao para tras, mantendo a continuidade do vetor.
 */
void excluirMusica(void)
{
    int id, pos, i;

    printf("\n--- Excluir Musica ---\n");
    id  = lerInteiro("Digite o ID da musica que deseja excluir: ");
    pos = buscarPorId(id);

    if (pos == -1) {
        printf("Musica com ID %d nao encontrada.\n", id);
        return;
    }

    printf("\nMusica a ser excluida: %s - %s\n",
           playlist[pos].titulo, playlist[pos].artista);

    for (i = pos; i < quantidade - 1; i++) {
        playlist[i] = playlist[i + 1];
    }

    quantidade--;

    printf("Musica excluida com sucesso!\n");
}
