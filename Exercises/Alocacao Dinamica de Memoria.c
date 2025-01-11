#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Permite o uso de caracteres acentuados

    int m, n, i, j;
    int **matriz;
    int *somas;

    // Solicita as dimensões da matriz
    printf("Digite o número de linhas (M): ");
    scanf("%d", &m);
    printf("Digite o número de colunas (N): ");
    scanf("%d", &n);

    // Aloca dinamicamente a matriz
    matriz = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }

    // Aloca o vetor para as somas das linhas
    somas = (int *)malloc(m * sizeof(int));

    // Preenche a matriz com valores aleatórios
    srand(time(NULL));
    printf("\nMatriz gerada:\n");
    for (i = 0; i < m; i++) {
        somas[i] = 0; // Inicializa a soma da linha
        for (j = 0; j < n; j++) {
            matriz[i][j] = rand() % 100; // Valores entre 0 e 99
            printf("%d ", matriz[i][j]);
            somas[i] += matriz[i][j];
        }
        printf("\n");
    }

    // Exibe as somas das linhas
    printf("\nSoma de cada linha:\n");
    for (i = 0; i < m; i++) {
        printf("Linha %d: %d\n", i + 1, somas[i]);
    }

    // Libera a memória alocada
    for (i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(somas);

    return 0;
}
