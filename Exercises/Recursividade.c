/*
Implemente um programa que:
- Crie uma fun��o recursiva para gerar a sequ�ncia:
  f(n) = 2*f(n-1) + f(n-2), onde f(0) = 1 e f(1) = 2
- Pe�a ao usu�rio um n�mero N
- Mostre os N primeiros termos da sequ�ncia
*/

#include <stdio.h>

// Fun��o recursiva para calcular f(n)
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

    // Solicita ao usu�rio o n�mero de termos
    printf("Digite o n�mero de termos N: ");
    scanf("%d", &N);

    // Verifica se o n�mero � v�lido
    if (N <= 0) {
        printf("Por favor, insira um n�mero positivo.\n");
        return 1;
    }

    // Mostra os N primeiros termos da sequ�ncia
    printf("Os %d primeiros termos da sequ�ncia s�o:\n", N);
    for (int i = 0; i < N; i++) {
        printf("f(%d) = %d\n", i, f(i));
    }

    return 0;
}
