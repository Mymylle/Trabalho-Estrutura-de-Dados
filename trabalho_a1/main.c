

#include <stdio.h>
#include "playlist.h"


Musica playlist[MAX_MUSICAS];
int    quantidade = 0;

int main(void)
{
    int opcao;

    carregarCSV(); 

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
