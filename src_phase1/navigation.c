#include <stdbool.h>
#include "navigate.h"

// Direções possíveis (cima, baixo, esquerda, direita)
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

// Estrutura da fila (queue)
typedef struct {
    int row, col, steps;
} QueueNode;

// Tamanho inicial da fila circular
#define QUEUE_SIZE 2048

// Função BFS Modular baseada na Tarefa pedida, utilizando uma fila circular com malloc
int bfs_modular(int **grid, int rows, int cols, int startRow, int startCol, int kstep, int taskType) {
    int correctStartRow = startRow - 1, correctStartCol = startCol - 1;
    int abs_kstep = abs(kstep);  // Número de passos que podemos dar 
    int result = 0;              // Armazena o resultado da Tarefa 1 ou 2
    bool firstPass = true;

    // Array que marca as posições visitadas (inicialmente todas a zero)
    bool **visited = (bool **)calloc(rows, sizeof(bool *));
    for (int i = 0; i < rows; i++) {
        visited[i] = (bool *)calloc(cols, sizeof(bool));
    }

    // Dinamicamente aloca a fila circular
    QueueNode *queue = (QueueNode *)malloc(QUEUE_SIZE * sizeof(QueueNode));
    if (!queue) {
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);
        exit(0);
    }

    int front = 0, rear = 0;

    // Adiciona a posição inicial à fila
    queue[rear].row = correctStartRow;
    queue[rear].col = correctStartCol;
    queue[rear].steps = 0;
    rear = (rear + 1) % QUEUE_SIZE;  // Incrementa rear de forma circular
    visited[correctStartRow][correctStartCol] = true;  // Marca como visitado

    // BFS loop
    while (front != rear) {  // Enquanto houver elementos na fila
        QueueNode current = queue[front];
        front = (front + 1) % QUEUE_SIZE;  // Incrementa front de forma circular

        int currentRow = current.row;
        int currentCol = current.col;
        int currentSteps = current.steps;

        // Tarefa 1: Encontrar o maior elemento positivo
        if (taskType == FIND_MAX) {
            if (!firstPass && grid[currentRow][currentCol] > 0 && grid[currentRow][currentCol] > result) {
                result = grid[currentRow][currentCol];  // Atualiza o resultado se o valor atual for maior
            }
        }
        // Tarefa 2: Somar os elementos positivos
        else if (!firstPass && taskType == SUM_POSITIVES) {
            if (grid[currentRow][currentCol] > 0) {
                result += grid[currentRow][currentCol];  // Adiciona o valor atual ao resultado
            }
        }

        firstPass = false;

        // Se o número de passos dados for maior que o número de passos pedidos, sair do loop
        if (currentSteps >= abs_kstep) {
            continue;
        }

        // Explora as 4 direções possíveis
        for (int i = 0; i < 4; i++) {
            int newRow = currentRow + dRow[i];
            int newCol = currentCol + dCol[i];

            // Verifica se a nova posição é válida e se ainda não foi visitada
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                // Verifica se a fila circular está cheia (evita overflow)
                if ((rear + 1) % QUEUE_SIZE == front) {
                    for (int i = 0; i < rows; i++) {
                        free(visited[i]);
                    }
                    free(visited);
                    free(queue);
                    exit(0);
                }

                // Adiciona a nova posição à fila
                queue[rear].row = newRow;
                queue[rear].col = newCol;
                queue[rear].steps = currentSteps + 1;
                rear = (rear + 1) % QUEUE_SIZE;  // Incrementa rear de forma circular

                // Marca a nova posição como visitada
                visited[newRow][newCol] = true;
            }
        }
    }

    // Liberta a memória alocada para as posições visitadas
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);

    // Liberta a memória alocada para a fila
    free(queue);

    return result;  // Retorna o resultado da Tarefa 1 ou 2
}

// Função para a Tarefa 3: Move-se primeiro verticalmente e depois horizontalmente para o destino
void move_to_destination(FILE *output, int **grid, int rows, int cols, int startRow, int startCol, int destRow, int destCol) {

    fprintf(output, "%d %d %d %d 0 %d %d\n", rows, cols, startRow, startCol, destRow, destCol);

    // Movimento vertical primeiro
    while (startRow != destRow) {
        if (startRow < destRow) {
            startRow++;  // Move para baixo
        } else {
            startRow--;  // Move para cima
        }
        fprintf(output, "%d %d %d\n", startRow, startCol,grid[startRow - 1][startCol - 1]);
    }

    // Agora move horizontalmente
    while (startCol != destCol) {
        if (startCol < destCol) {
            startCol++;  // Move para a direita
        } else {
            startCol--;  // Move para a esquerda
        }
        fprintf(output, "%d %d %d\n", startRow, startCol, grid[startRow - 1][startCol - 1]);
    }
    fprintf(output,"\n");
}