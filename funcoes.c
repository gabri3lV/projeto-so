#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <cstdlib>
#include <ctime>

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

// Função para criar processos com valores aleatórios
void criaProcessos(struct Fila* fila, int num_processos) {

    srand(time(0)); 
    for (int i = 0; i < num_processos && i < MAX; ++i) {
        struct Processo novo_processo;
        novo_processo.id = i + 1;
        novo_processo.tempo_execucao = rand() % 10 + 1; // Tempo de execução entre 1 e 10
        novo_processo.tempo_restante = novo_processo.tempo_execucao;
        novo_processo.prioridade = rand() % 5 + 1; // Prioridade entre 1 e 5
        novo_processo.tempo_espera = 0;
        novo_processo.quantum = rand() % 5 + 1; // Quantum entre 1 e 5
        novo_processo.tempo_aumento_prioridade = rand() % 10 + 1; // Tempo para aumento de prioridade entre 1 e 10

        // Enfileirando
        enfileiraProcesso(fila, novo_processo);
    }
}

// Função para exibir os resultados  dos processos
void exibeResultados(struct Fila* fila) {
    printf("\n\nResultados dos processos:\n");
    printf("ID\tTempo Execucao\tTempo Restante\tPrioridade\tTempo Espera\tQuantum\tTempo Aumento Prioridade\n");
    for (int i = 0; i < fila->tamanho; ++i) {
        struct Processo processo = fila->processos[(fila->inicio + i) % MAX];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\n", processo.id, processo.tempo_execucao, processo.tempo_restante, processo.prioridade, processo.tempo_espera, processo.quantum, processo.tempo_aumento_prioridade);
    }
}