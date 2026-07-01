#include <stdio.h>
#include <string.h>
#include "playlist.h"


void exibirMenu(void)
{
    printf("\n===========================================\n");
    printf("        PLAYLIST DE MUSICAS - MENU\n");
    printf("===========================================\n");
    printf("1 - Inserir nova musica\n");
    printf("2 - Listar playlist\n");
    printf("3 - Buscar musica por ID\n");
    printf("4 - Editar musica\n");
    printf("5 - Excluir musica\n");
    printf("6 - Salvar playlist em arquivo (CSV)\n");
    printf("0 - Salvar e sair\n");
    printf("===========================================\n");
}


void limparBufferEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta o caractere */
    }
}

int lerInteiro(const char *mensagem)
{
    int valor;
    int resultado;

    while (1) {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);

        if (resultado == 1) {
            limparBufferEntrada();
            return valor;
        } else {
            printf("Entrada invalida! Digite um numero inteiro.\n");
            limparBufferEntrada();
        }
    }
}

void lerTexto(const char *mensagem, char *destino, int tamanho)
{
    int len;

    while (1) {
        printf("%s", mensagem);

        if (fgets(destino, tamanho, stdin) != NULL) {
            len = strlen(destino);

            if (len > 0 && destino[len - 1] == '\n') {
                destino[len - 1] = '\0';
                len--;
            }

            if (len == 0) {
                printf("Campo nao pode ficar vazio!\n");
                continue;
            }

            return;
        }
    }
}
