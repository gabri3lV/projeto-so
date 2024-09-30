#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

// Função que inicializa a fila de processos
void inicializaFila(struct Fila* fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
}

// Função que insere um processo na fila
int enfileiraProcesso(struct Fila* fila, struct Processo processo) {
    if (fila->tamanho == MAX) {
        return -1;  // Fila cheia
    }
    fila->fim = (fila->fim + 1) % MAX;  // Incrementa o índice fim de forma circular ->  evita que a fila "saia dos limites"
    fila->processos[fila->fim] = processo;
    fila->tamanho++;
    return 0;  // Sucesso
}

// Função para desenfileirar um processo
struct Processo desenfileiraProcesso(struct Fila* fila) {
    if (fila->tamanho == 0) {
        struct Processo vazio = {-1, 0, 0, 0, 0, 0, 0};  // Processo "vazio" para garantir que os campos sejam zerados e consistentes
        return vazio;  // Fila vazia
    }
    struct Processo processo = fila->processos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;  // Incrementa o índice início de forma circular
    fila->tamanho--;
    return processo;
}

// Função para verificar se a fila está vazia
int filaVazia(struct Fila* fila) {
    return (fila->tamanho == 0); // Retorna 1 se a fila estiver vazia, 0 caso contrário
}