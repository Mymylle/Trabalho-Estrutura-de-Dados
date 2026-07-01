#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

void limpar_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}


void limpar_buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    
    }
}


void exibir_chamada(Chamada c)
{
    printf("  +------------------------------------------+\n");
    printf("  | Protocolo : %-28d |\n", c.protocolo);
    printf("  | Local     : %-28s |\n", c.local);
    printf("  | Tipo      : %-28s |\n", c.tipo);
    printf("  | Horario   : %-28s |\n", c.horario);
    printf("  +------------------------------------------+\n");
}


int exibir_menu(void)
{
    int opcao;
    int resultado;

    printf("\n");
    printf("  ============================================\n");
    printf("  SISTEMA DE CHAMADAS DE EMERGENCIA\n");
    printf("  ============================================\n");
    printf("  1. Registrar chamada (push)\n");
    printf("  2. Atender chamada   (pop)\n");
    printf("  3. Consultar ultima  (peek)\n");
    printf("  4. Listar chamadas\n");
    printf("  5. Salvar em arquivo CSV\n");
    printf("  6. Carregar do arquivo CSV\n");
    printf("  0. Encerrar programa\n");
    printf("  --------------------------------------------\n");
    printf("  Opcao: ");

    resultado = scanf("%d", &opcao);
    limpar_buffer();

    if (resultado != 1) {
        return -1; /* entrada invalida */
    }

    return opcao;
}


void menu_registrar(Chamada pilha[], int *topo)
{
    Chamada nova;
    int     protocolo;
    int     resultado;

    printf("\n  --- REGISTRAR CHAMADA ---\n");

    /* Leitura e validacao do protocolo */
    printf("  Protocolo (numero inteiro positivo): ");
    resultado = scanf("%d", &protocolo);
    limpar_buffer();

    if (resultado != 1 || protocolo <= 0) {
        printf("  ERRO: protocolo invalido. Informe um numero inteiro positivo.\n");
        return;
    }

    if (protocolo_existe(pilha, *topo, protocolo)) {
        printf("  ERRO: protocolo %d ja cadastrado.\n", protocolo);
        return;
    }

    nova.protocolo = protocolo;

    /* local */
    printf("  Local da emergencia: ");
    fgets(nova.local, sizeof(nova.local), stdin);
    limpar_newline(nova.local);

    if (strlen(nova.local) == 0) {
        printf("  ERRO: campo 'local' nao pode ser vazio.\n");
        return;
    }

    /* tipo */
    printf("  Tipo da ocorrencia : ");
    fgets(nova.tipo, sizeof(nova.tipo), stdin);
    limpar_newline(nova.tipo);

    if (strlen(nova.tipo) == 0) {
        printf("  ERRO: campo 'tipo' nao pode ser vazio.\n");
        return;
    }

    /* horario */
    printf("  Horario (HH:MM)    : ");
    fgets(nova.horario, sizeof(nova.horario), stdin);
    limpar_newline(nova.horario);

    if (strlen(nova.horario) == 0) {
        printf("  ERRO: campo 'horario' nao pode ser vazio.\n");
        return;
    }

    /*pilha */
    if (push(pilha, topo, nova)) {
        printf("  Chamada registrada com sucesso.\n");
        exibir_chamada(nova);
    } else {
        printf("  ERRO: pilha cheia. Nao e possivel registrar nova chamada.\n");
    }
}


void menu_atender(Chamada pilha[], int *topo)
{
    Chamada removida;

    printf("\n  --- ATENDER CHAMADA (TOPO) ---\n");

    if (pop(pilha, topo, &removida)) {
        printf("  Chamada atendida e removida da pilha:\n");
        exibir_chamada(removida);
    } else {
        printf("  Nenhuma chamada na pilha para atender.\n");
    }
}


void menu_consultar(Chamada pilha[], int topo)
{
    Chamada consultada;

    printf("\n  --- CONSULTAR ULTIMA CHAMADA (TOPO) ---\n");

    if (peek(pilha, topo, &consultada)) {
        printf("  Ultima chamada registrada (nao removida):\n");
        exibir_chamada(consultada);
    } else {
        printf("  A pilha esta vazia. Nenhuma chamada para consultar.\n");
    }
}
