#include <stdio.h>2
#include "pilha.h"

int main(void)
{

    Chamada pilha[MAX];
    int     topo = -1;

    int opcao;
    int carregados;

    printf("\n  Iniciando sistema de chamadas de emergencia...\n");

    carregados = carregar_csv(pilha, &topo);

    if (carregados == -1) {
        printf("  Arquivo '%s' nao encontrado. Iniciando com pilha vazia.\n",
               ARQUIVO_CSV);
    } else {
        printf("  %d chamada(s) carregada(s) do arquivo '%s'.\n",
               carregados, ARQUIVO_CSV);
    }

    /* Loop principal */
    do {
        opcao = exibir_menu();

        switch (opcao) {
            case 1:
                menu_registrar(pilha, &topo);
                break;

            case 2:
                menu_atender(pilha, &topo);
                break;

            case 3:
                menu_consultar(pilha, topo);
                break;

            case 4:
                printf("\n  --- LISTA DE CHAMADAS (TOPO ATE A BASE) ---\n");
                listar(pilha, topo);
                break;

            case 5:
                printf("\n  --- SALVAR EM ARQUIVO ---\n");
                salvar_csv(pilha, topo);
                break;

            case 6:
                printf("\n  --- CARREGAR DO ARQUIVO ---\n");

                topo = -1;
                carregados = carregar_csv(pilha, &topo);

                if (carregados == -1) {
                    printf("  Arquivo '%s' nao encontrado.\n", ARQUIVO_CSV);
                } else {
                    printf("  %d chamada(s) carregada(s) com sucesso.\n",
                           carregados);
                }

                break;

            case 0:
                printf("\n  Encerrando o programa.\n");
                printf("  Os dados nao salvos serao perdidos.\n");
                break;

            default:
                printf("\n  ERRO: opcao invalida. Escolha entre 0 e 6.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
