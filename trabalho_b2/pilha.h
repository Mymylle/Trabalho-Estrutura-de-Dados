/*
 * pilha.h
 * Definicoes de tipos, constantes e prototipos de funcoes
 * para o sistema de pilha de chamadas de emergencia.
 */

#ifndef PILHA_H
#define PILHA_H

/* Capacidade maxima da pilha */
#define MAX 100

/* Nome do arquivo de persistencia */
#define ARQUIVO_CSV "chamadas.csv"

/* Cabeçalho do CSV conforme norma do trabalho */
#define CABECALHO_CSV "protocolo;local;tipo;horario"

/*
 * Estrutura que representa uma chamada de emergencia.
 * Cada campo corresponde a um dado coletado no momento do registro.
 */
typedef struct {
    int  protocolo;    /* Numero unico de identificacao da chamada */
    char local[50];    /* Local onde ocorreu a emergencia          */
    char tipo[30];     /* Tipo da ocorrencia (ex: incendio)        */
    char horario[20];  /* Horario em que a chamada foi registrada  */
} Chamada;

/* --- Prototipos das funcoes da pilha --- */

/*
 * Verifica se a pilha esta cheia.
 * Retorna 1 se cheia, 0 caso contrario.
 */
int pilha_cheia(int topo);

/*
 * Verifica se a pilha esta vazia.
 * Retorna 1 se vazia, 0 caso contrario.
 */
int pilha_vazia(int topo);

/*
 * Insere uma chamada no topo da pilha (push).
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver cheia.
 */
int push(Chamada pilha[], int *topo, Chamada nova);

/*
 * Remove e retorna a chamada do topo da pilha (pop).
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int pop(Chamada pilha[], int *topo, Chamada *removida);

/*
 * Consulta a chamada do topo sem remover (peek).
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int peek(Chamada pilha[], int topo, Chamada *consultada);

/*
 * Exibe todas as chamadas do topo ate a base.
 */
void listar(Chamada pilha[], int topo);

/*
 * Verifica se ja existe uma chamada com o protocolo informado.
 * Retorna 1 se encontrado, 0 caso contrario.
 */
int protocolo_existe(Chamada pilha[], int topo, int protocolo);

/* --- Prototipos das funcoes de arquivo --- */

/*
 * Salva todas as chamadas da pilha em arquivo CSV.
 * Retorna 1 em caso de sucesso, 0 em caso de erro.
 */
int salvar_csv(Chamada pilha[], int topo);

/*
 * Carrega as chamadas do arquivo CSV para a pilha.
 * Retorna o numero de registros carregados, ou -1 em caso de erro.
 */
int carregar_csv(Chamada pilha[], int *topo);

/* --- Prototipos das funcoes de menu --- */

/*
 * Exibe o menu principal e retorna a opcao escolhida pelo usuario.
 */
int exibir_menu(void);

/*
 * Executa o fluxo de registro de uma nova chamada.
 */
void menu_registrar(Chamada pilha[], int *topo);

/*
 * Executa o fluxo de atendimento (pop) de uma chamada.
 */
void menu_atender(Chamada pilha[], int *topo);

/*
 * Executa a consulta do topo sem remover (peek).
 */
void menu_consultar(Chamada pilha[], int topo);

/*
 * Exibe os dados de uma chamada formatada na tela.
 */
void exibir_chamada(Chamada c);

/*
 * Remove caractere de nova linha ao final de uma string lida com fgets.
 */
void limpar_newline(char *str);

/*
 * Limpa o buffer de entrada do teclado.
 */
void limpar_buffer(void);

#endif /* PILHA_H */
