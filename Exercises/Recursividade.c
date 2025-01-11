/*
Implemente um programa que:
- Crie uma função recursiva para gerar a sequência:
  f(n) = 2*f(n-1) + f(n-2), onde f(0) = 1 e f(1) = 2
- Peça ao usuário um número N
- Mostre os N primeiros termos da sequência
*/

#include <stdio.h>

// Função recursiva para calcular f(n)
int f(int n) {
    if (n == 0) {
        return 1; // Caso base: f(0) = 1
    } else if (n == 1) {
        return 2; // Caso base: f(1) = 2
    } else {
        return 2 * f(n - 1) + f(n - 2); // Caso recursivo
    }
}

int main() {
    int N;

    // Solicita ao usuário o número de termos
    printf("Digite o número de termos N: ");
    scanf("%d", &N);

    // Verifica se o número é válido
    if (N <= 0) {
        printf("Por favor, insira um número positivo.\n");
        return 1;
    }

    // Mostra os N primeiros termos da sequência
    printf("Os %d primeiros termos da sequência são:\n", N);
    for (int i = 0; i < N; i++) {
        printf("f(%d) = %d\n", i, f(i));
    }

    return 0;
}
