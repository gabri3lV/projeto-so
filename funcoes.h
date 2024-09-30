// Definindo o tamanho máximo de processos que usarei
#DEFINE MAX 10 

// Estrutura com as informações de um processo
struct Processo {
    int id;
    int tempo_execucao;
    int tempo_restante;
    int prioridade;
    int tempo_espera;
    int quantum;
    int tempo_aumento_prioridade;
};

// Estrutura da fila de processos
struct Fila {
    struct Processo processos[MAX];  // Array para armazenar os processos
    int inicio;  // Índice do início da fila
    int fim;     // Índice do final da fila
    int tamanho; // Tamanho atual da fila
};

// FUNÇÕES:
void criaProcessos(struct Fila* fila, int num_processos);
int escalonamento();
int aumentaPrioridade();
int finalizaProcessos();
int executaProcessos();
int exibeResultados();
void inicializaFila(struct Fila* fila);
void insereProcesso(struct Fila* fila, struct Processo processo);