/*
Implemente um programa que:
- Declare duas variáveis inteiras
- Crie uma função que receba dois ponteiros
- Faça a troca dos valores usando apenas ponteiros
- Imprima os valores antes e depois da troca
*/

#include <stdio.h>

// Função para trocar os valores usando ponteiros
void trocaValores(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    // Entrada dos valores
    printf("Digite o primeiro valor: ");
    scanf("%d", &x);
    printf("Digite o segundo valor: ");
    scanf("%d", &y);

    // Imprime os valores antes da troca
    printf("\nAntes da troca:\n");
    printf("x = %d, y = %d\n", x, y);

    // Chama a função para trocar os valores
    trocaValores(&x, &y);

    // Imprime os valores após a troca
    printf("\nDepois da troca:\n");
    printf("x = %d, y = %d\n", x, y);

    return 0;
}
