#include <stdio.h>

int fibonacci(int n)
{
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main()
{
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);

    int resultado = fibonacci(n);
    printf("The corresponding value in the Fibonacci sequence is: %d\n", resultado);

    return 0;
}
