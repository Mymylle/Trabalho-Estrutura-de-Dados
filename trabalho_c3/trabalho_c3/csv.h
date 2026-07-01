#ifndef CSV_H
#define CSV_H

#include "tipos.h"

/* * Guarda o estado atual da Fila Circular num ficheiro CSV.
 * O modificador 'const' garante que a função apenas lê a fila, 
 * sem alterar os dados originais na memória.
 * Retorna 1 em caso de sucesso, ou 0 em caso de erro
 */
int salvarCSV(const FilaCircular *f);

/* * Carrega os dados de um ficheiro CSV de volta para a Fila Circular
 * Esta função reconstrói o estado anterior do programa
 * Retorna 1 se os dados foram carregados com sucesso, ou 0 se o ficheiro não existir
 */
int carregarCSV(FilaCircular *f);

#endif