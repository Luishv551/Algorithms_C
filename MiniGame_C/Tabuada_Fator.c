#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main(void) {

    int numero;
    int f;

    printf("Qual numero voce quer saber a tabuada?\n");
    scanf("%d", &numero);

    printf("Ate qual fator voce quer a tabuada?\n");
    scanf("%d", &f);

    for (int i=1; i<=f; i++) {

        printf("%d x %d = %d\n", numero, i, numero * i);

}
    return 0;

}
