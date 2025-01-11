/*
Desenvolva um programa que:
- Crie uma matriz 3x3
- Preencha com valores do usu�rio
- Crie uma fun��o que gere a matriz transposta
- Imprima ambas as matrizes para compara��o
*/

#include <stdio.h>

int main() {
    int mat[3][3], i, j;

    // Preenchendo a matriz
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("Digite o valor da posicao %d %d: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    // Imprimindo a matriz transposta
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}

