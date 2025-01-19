#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void limparTela(void) {
    system("cls");
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(const char* mensagem) {
    int valor;
    printf("%s", mensagem);
    scanf("%d", &valor);
    limparBuffer();
    return valor;
}

double lerDouble(const char* mensagem) {
    double valor;
    printf("%s", mensagem);
    scanf("%lf", &valor);
    limparBuffer();
    return valor;
}
