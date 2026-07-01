#ifndef FILA_H
#define FILA_H

#include "tipos.h"

void inicializarFila(FilaCircular *f);
int  filaVazia(const FilaCircular *f);
int  filaCheia(const FilaCircular *f);
int  enfileirar(FilaCircular *f, Processo p);
int  desenfileirar(FilaCircular *f, Processo *saida);
int  consultarProximo(const FilaCircular *f, Processo *saida);
void listarFila(const FilaCircular *f);
int  pidExiste(const FilaCircular *f, int pid);
int  removerPorPid(FilaCircular *f, int pid);

#endif
