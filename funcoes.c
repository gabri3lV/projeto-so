#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <time.h>

// Função que inicializa a fila de processos
void inicializaFila(struct Fila* fila) {
    fila->processos = (struct Processo*)malloc(MAX * sizeof(struct Processo));  // Aloca memória para os processos
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = MAX;
}

// Função que inicializa o gerenciador de filas
void inicializaGerenciador(struct GerenciadorFilas* gerenciador) {
    for (int i = 0; i < MAX_PRIORIDADES; ++i) {
        inicializaFila(&gerenciador->filas[i]);
    }
}

// Função que insere um processo na fila
int enfileiraProcesso(struct Fila* fila, struct Processo processo) {
    if (fila->tamanho == fila->capacidade) {
        printf("Fila cheia!\n");
        return -1;  // Fila cheia
    }
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->processos[fila->fim] = processo;
    fila->tamanho++;
    printf("Processo %d enfileirado com sucesso!\n", processo.id);
    return 0; 
}

// Função para desenfileirar um processo
struct Processo desenfileiraProcesso(struct Fila* fila) {
    if (fila->tamanho == 0) {
        struct Processo vazio = {-1, 0, 0, 0, 0, 0};  // Processo "vazio" para garantir que os campos sejam zerados e consistentes
        return vazio;  // Fila está vazia
    }
    struct Processo processo = fila->processos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return processo;
}

// Função para verificar se a fila está vazia
int filaVazia(struct Fila* fila) {
    return (fila->tamanho == 0); // Retorna 1 se a fila estiver vazia, 0 caso contrário
}

// Função para criar processos com valores aleatórios
void criaProcessosAleatorios(struct GerenciadorFilas* gerenciador, int num_processos) {

    srand(time(0)); 
    for (int i = 0; i < num_processos && i < MAX; ++i) {
        struct Processo novo_processo;
        novo_processo.id = i + 1;
        novo_processo.tempo_execucao = rand() % 10 + 1; // Tempo de execução entre 1 e 10
        novo_processo.tempo_restante = novo_processo.tempo_execucao;
        novo_processo.prioridade = rand() % 5 + 1; // Prioridade entre 1 e 5
        novo_processo.tempo_espera = 0;
        novo_processo.tempo_aumento_prioridade = rand() % 10 + 1; // Tempo para aumento de prioridade entre 1 e 10

        // Enfileirando
         enfileiraProcesso(&gerenciador->filas[novo_processo.prioridade], novo_processo);
    }
}

// Função para criar processos de acordo com a resposta do usuário
void criaProcessosUsuario(struct GerenciadorFilas* gerenciador, int num_processos){
    for (int i = 0; i < num_processos && i < MAX; i++){
        struct Processo novo_processo;
        novo_processo.id = i + 1;

        printf("Digite o tempo de execucao do processo %d: ", i + 1);
        scanf("%d", &novo_processo.tempo_execucao);
        novo_processo.tempo_restante = novo_processo.tempo_execucao;

        printf("Digite a prioridade do processo %d: ", i + 1);
        scanf("%d", &novo_processo.prioridade);

        novo_processo.tempo_espera = 0;

        printf("Digite o tempo de aumento de prioridade do processo %d: ", i + 1);
        scanf("%d", &novo_processo.tempo_aumento_prioridade);
        
        enfileiraProcesso(&gerenciador->filas[novo_processo.prioridade], novo_processo);
    }
}
// Função para exibir os resultados  dos processos
void exibeResultados(struct Fila* fila) {
    for (int i = 0; i < fila->tamanho; ++i) {
        struct Processo processo = fila->processos[(fila->inicio + i) % fila->capacidade];
        int tempo_executado = processo.tempo_execucao - processo.tempo_restante;
        printf("P%d (%d | %d) [Prioridade: %d]", processo.id, tempo_executado, processo.tempo_restante, processo.prioridade);
        if (i < fila->tamanho - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Libera a memória alocada para a fila
void liberaFila(struct Fila* fila) {
    free(fila->processos);
    fila->processos = NULL;
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = 0;
}

// Função para liberar a memória alocada para as filas
void liberaGerenciador(struct GerenciadorFilas* gerenciador) {
    for (int i = 0; i < MAX_PRIORIDADES; ++i) {
        liberaFila(&gerenciador->filas[i]);  // Corrigido para usar liberaFila
    }
}

// Função para aumentar a prioridade dos processos
void aumentaPrioridade(struct GerenciadorFilas* gerenciador) {
    for (int p = 1; p < MAX_PRIORIDADES; ++p) {  // Começa a partir da segunda prioridade
        struct Fila* fila = &gerenciador->filas[p];
        int tamanho_original = fila->tamanho;
        for (int i = 0; i < tamanho_original; ++i) {
            struct Processo* processo = &fila->processos[(fila->inicio + i) % fila->capacidade];
            if (processo->tempo_espera >= processo->tempo_aumento_prioridade) {
                processo->prioridade--;
                processo->tempo_espera = 0;
                printf("Processo %d teve sua prioridade aumentada para %d\n", processo->id, processo->prioridade);
                desenfileiraProcesso(fila); // Remove o processo da fila atual
                enfileiraProcesso(&gerenciador->filas[processo->prioridade], *processo); // Adiciona o processo na fila de maior prioridade
            }
        }
    }
}

// Função para escalonar os processos
void escalonaProcessos(struct GerenciadorFilas* gerenciador) {
    // Exibe o estado inicial dos processos
    printf("====================================\n");
    printf("Estado inicial dos processos:\n");
    for (int k = 0; k < MAX_PRIORIDADES; k++) {
        printf("Fila de prioridade %d:\n", k);
        exibeResultados(&gerenciador->filas[k]);
    }
    while (1) {
        int processos_restantes = 0;

        for (int i = 0; i < MAX_PRIORIDADES; ++i) {
            struct Fila* fila = &gerenciador->filas[i];
            if (!filaVazia(fila)) {
                processos_restantes = 1;
                struct Processo processo = desenfileiraProcesso(fila);

                // Simula a execução do processo
                printf("Executando processo %d da prioridade %d\n", processo.id, processo.prioridade);
                int tempo_execucao = (processo.tempo_restante < QUANTUM) ? processo.tempo_restante : QUANTUM;
                processo.tempo_restante -= tempo_execucao;
                if (processo.tempo_restante > 0) {
                    processo.tempo_espera += tempo_execucao;
                    enfileiraProcesso(fila, processo);
                } else {
                    printf("Processo %d concluído\n", processo.id);
                }

                // Aumenta a prioridade dos processos se necessário
                aumentaPrioridade(gerenciador);

                // Acompanhando o estado atual dos processos
                printf("====================================\n");
                printf("Estado atual dos processos:\n");
                for (int k = 0; k < MAX_PRIORIDADES; k++){
                    printf("Fila de prioridade %d:\n", k);
                    exibeResultados(&gerenciador->filas[k]);
                }
            }
        }
        if (!processos_restantes) {
            break;  // Todos os processos foram concluídos
        }
        // Atualiza o tempo de espera para todos os processos nas filas
        for (int i = 0; i < MAX_PRIORIDADES; ++i) {
            struct Fila* fila = &gerenciador->filas[i];
            for (int j = 0; j < fila->tamanho; ++j) {
                struct Processo* processo = &fila->processos[(fila->inicio + j) % fila->capacidade];
                processo->tempo_espera += 1;  // aumenta o tempo de espera
            }
        }
    }
}