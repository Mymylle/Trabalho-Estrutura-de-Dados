#ifndef PLAYLIST_H
#define PLAYLIST_H


#define MAX_MUSICAS 100
#define TAM_TITULO   50
#define TAM_ARTISTA  50
#define TAM_GENERO   30
#define NOME_ARQUIVO "playlist.csv"


typedef struct {
    int  id;
    char titulo[TAM_TITULO];
    char artista[TAM_ARTISTA];
    int  duracao;       
    char genero[TAM_GENERO];
} Musica;


extern Musica playlist[MAX_MUSICAS];
extern int    quantidade;


void inserirMusica(void);
void listarMusicas(void);
void buscarMusica(void);
void editarMusica(void);
void excluirMusica(void);
int  buscarPorId(int id);


void salvarCSV(void);
void carregarCSV(void);


void exibirMenu(void);
void limparBufferEntrada(void);
int  lerInteiro(const char *mensagem);
void lerTexto(const char *mensagem, char *destino, int tamanho);

#endif
