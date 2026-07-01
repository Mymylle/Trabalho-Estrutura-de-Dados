/*
 * playlist.h
 * Definicoes de constantes, struct e prototipos de todas as funcoes
 * do sistema de playlist de musicas.
 *
 * Disciplina : Estrutura de Dados
 * Curso      : Analise e Desenvolvimento de Sistemas
 * Instituicao: UniJorge
 * Semestre   : 3 semestre
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

/* --- Constantes --- */
#define MAX_MUSICAS 100
#define TAM_TITULO   50
#define TAM_ARTISTA  50
#define TAM_GENERO   30
#define NOME_ARQUIVO "playlist.csv"

/*
 * Estrutura que representa uma musica na playlist.
 */
typedef struct {
    int  id;
    char titulo[TAM_TITULO];
    char artista[TAM_ARTISTA];
    int  duracao;       /* duracao em segundos */
    char genero[TAM_GENERO];
} Musica;

/* Vetor de musicas e variavel de controle (definidos em main.c) */
extern Musica playlist[MAX_MUSICAS];
extern int    quantidade;

/* --- Prototipos: operacoes da lista --- */
void inserirMusica(void);
void listarMusicas(void);
void buscarMusica(void);
void editarMusica(void);
void excluirMusica(void);
int  buscarPorId(int id);

/* --- Prototipos: persistencia em arquivo --- */
void salvarCSV(void);
void carregarCSV(void);

/* --- Prototipos: interface e entrada --- */
void exibirMenu(void);
void limparBufferEntrada(void);
int  lerInteiro(const char *mensagem);
void lerTexto(const char *mensagem, char *destino, int tamanho);

#endif /* PLAYLIST_H */
