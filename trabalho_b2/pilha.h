#ifndef PILHA_H
#define PILHA_H
#define MAX 100
#define ARQUIVO_CSV "chamadas.csv"
#define CABECALHO_CSV "protocolo;local;tipo;horario"


typedef struct {
    int  protocolo;   
    char local[50];   
    char tipo[30];    
    char horario[20]; 
} Chamada;



int pilha_cheia(int topo);


int pilha_vazia(int topo);


int push(Chamada pilha[], int *topo, Chamada nova);


int pop(Chamada pilha[], int *topo, Chamada *removida);


int peek(Chamada pilha[], int topo, Chamada *consultada);


void listar(Chamada pilha[], int topo);


int protocolo_existe(Chamada pilha[], int topo, int protocolo);


int salvar_csv(Chamada pilha[], int topo);


int carregar_csv(Chamada pilha[], int *topo);


int exibir_menu(void);


void menu_registrar(Chamada pilha[], int *topo);


void menu_atender(Chamada pilha[], int *topo);


void menu_consultar(Chamada pilha[], int topo);


void exibir_chamada(Chamada c);


void limpar_newline(char *str);


void limpar_buffer(void);

#endif 
