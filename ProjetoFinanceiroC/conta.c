
#include "conta.h"
#include <stdio.h>
#include <string.h>

void inicializarConta(Conta* conta, int numero, const char* titular, const char* tipo) {
    conta->numero = numero;
    strcpy(conta->titular, titular);
    strcpy(conta->tipo, tipo);
    conta->saldo = 0.0;
}

int depositar(Conta* conta, double valor) {
    if (valor > 0) {
        conta->saldo += valor;
        return 1;
    }
    return 0;
}

int sacar(Conta* conta, double valor) {
    if (valor > 0 && valor <= conta->saldo) {
        conta->saldo -= valor;
        return 1;
    }
    return 0;
}

void exibirConta(const Conta* conta) {
    printf("\nNúmero: %d\n", conta->numero);
    printf("Titular: %s\n", conta->titular);
    printf("Tipo: %s\n", conta->tipo);
    printf("Saldo: R$ %.2f\n", conta->saldo);
}
