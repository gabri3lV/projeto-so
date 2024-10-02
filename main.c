#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    struct GerenciadorFilas gerenciador;
    int num_processos;

    // Inicializa o gerenciador de filas
    inicializaGerenciador(&gerenciador);

    // Cria processos aleatórios ou com entrada do usuário
    printf("Digite o número de processos (no máximo 10): ");
    scanf("%d", &num_processos);

    // Escolha entre processos aleatórios ou entrada do usuário
    int escolha;
    printf("Deseja criar processos aleatórios (1) ou com entrada do usuário (2)? ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        criaProcessosAleatorios(&gerenciador, num_processos);  // Inicialmente, todos os processos na fila de menor prioridade
    } else if (escolha == 2) {
        criaProcessosUsuario(&gerenciador, num_processos);  // Inicialmente, todos os processos na fila de menor prioridade
    } else {
        printf("Escolha inválida!\n");
        return 1;
    }

    // Executa o escalonador
    escalonaProcessos(&gerenciador, num_processos);

    // Exibe os resultados dos processos
    for (int i = 0; i < MAX_PRIORIDADES; ++i) {
        printf("\nResultados da fila de prioridade %d:\n", i + 1);
        exibeResultados(&gerenciador.filas[i]);
    }

    // Libera a memória alocada para as filas
    liberaGerenciador(&gerenciador);

    return 0;
}
