#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"


int salvar_csv(Chamada pilha[], int topo)
{
    FILE *arquivo;
    int   i;

    arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("  ERRO: nao foi possivel abrir o arquivo para escrita.\n");
        return 0;
    }

   
    fprintf(arquivo, "%s\n", CABECALHO_CSV);

   
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


int carregar_csv(Chamada pilha[], int *topo)
{
    FILE   *arquivo;
    char    linha[256];
    char   *campo;
    Chamada temp;
    int     carregados = 0;
    int     numero_linha = 1; 

    arquivo = fopen(ARQUIVO_CSV, "r");

    if (arquivo == NULL) {
       
        return -1;
    }

    
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numero_linha++;

        
        linha[strcspn(linha, "\n")] = '\0';

       
        if (strlen(linha) == 0) {
            continue;
        }

        /* protocolo */
        campo = strtok(linha, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (protocolo ausente).\n",
                   numero_linha);
            continue;
        }
        temp.protocolo = atoi(campo);

        /*  local */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (local ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.local, campo, sizeof(temp.local) - 1);
        temp.local[sizeof(temp.local) - 1] = '\0';

        /* tipo */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (tipo ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.tipo, campo, sizeof(temp.tipo) - 1);
        temp.tipo[sizeof(temp.tipo) - 1] = '\0';

        /* horario */
        campo = strtok(NULL, ";");
        if (campo == NULL) {
            printf("  AVISO: linha %d ignorada (horario ausente).\n",
                   numero_linha);
            continue;
        }
        strncpy(temp.horario, campo, sizeof(temp.horario) - 1);
        temp.horario[sizeof(temp.horario) - 1] = '\0';


        
        if (protocolo_existe(pilha, *topo, temp.protocolo)) {
            printf("  AVISO: protocolo %d ja existe. Linha %d ignorada.\n",
                   temp.protocolo, numero_linha);
            continue;
        }

        
        
        if (!push(pilha, topo, temp)) {
            printf("  AVISO: pilha cheia. Registros restantes nao carregados.\n");
            break;
        }

        carregados++;
    }

    fclose(arquivo);

    return carregados;
}
