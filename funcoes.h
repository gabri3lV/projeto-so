#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX 100
#define MAX_PRIORIDADES 5
#define QUANTUM 4 // valor fixo pra testar

// Estrutura para representar um processo
struct Processo {
    int id;
    int tempo_execucao;
    int tempo_restante;
    int prioridade;
    int tempo_espera;
    int tempo_aumento_prioridade;
};

// Estrutura para representar uma fila de processos
struct Fila {
    struct Processo* processos;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;  // Adicionado o campo capacidade
};

// Estrutura para representar o gerenciador de filas
struct GerenciadorFilas {
    struct Fila filas[MAX_PRIORIDADES];
};

// Declaração das funções
void inicializaFila(struct Fila* fila);
void inicializaGerenciador(struct GerenciadorFilas* gerenciador);
void criaProcessosAleatorios(struct GerenciadorFilas* gerenciador, int num_processos);
void criaProcessosUsuario(struct GerenciadorFilas* gerenciador, int num_processos);
void escalonaProcessos(struct GerenciadorFilas* gerenciador, int num_processos);
void exibeResultados(struct Fila* fila);
void liberaGerenciador(struct GerenciadorFilas* gerenciador);
struct Processo desenfileiraProcesso(struct Fila* fila); 
void liberaFila(struct Fila* fila);
int filaVazia(struct Fila* fila);
void aumentaPrioridade(struct GerenciadorFilas* gerenciador);

#endif // FUNCOES_H