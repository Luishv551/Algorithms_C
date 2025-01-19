#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "conta.h"

#define MAX_CONTAS 100

void exibirMenu() {
    printf("\n=== SISTEMA BANCARIO ===\n");
    printf("1. Criar conta\n");
    printf("2. Depositar\n");
    printf("3. Sacar\n");
    printf("4. Consultar saldo\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int buscarConta(Conta contas[], int numContas, int numero) {
    for (int i = 0; i < numContas; i++) {
        if (contas[i].numero == numero) {
            return i;
        }
    }
    return -1;
}

void criarConta(Conta contas[], int *numContas) {
    char titular[100];
    char tipo[20];

    printf("\nNome do titular: ");
    scanf("%99[^\n]", titular);
    limparBuffer();

    printf("Tipo de conta (Corrente/Poupanca): ");
    scanf("%19[^\n]", tipo);
    limparBuffer();

    inicializarConta(&contas[*numContas], *numContas + 1, titular, tipo);
    (*numContas)++;

    printf("\nConta criada com sucesso!\n");
    printf("Numero da conta: %d\n", *numContas);
}

void realizarDeposito(Conta contas[], int numContas) {
    int numero;
    double valor;

    printf("\nNumero da conta: ");
    scanf("%d", &numero);
    limparBuffer();

    int indice = buscarConta(contas, numContas, numero);

    if (indice != -1) {
        printf("Valor do deposito: R$ ");
        scanf("%lf", &valor);
        limparBuffer();

        if (depositar(&contas[indice], valor)) {
            printf("\nDeposito realizado com sucesso!\n");
            printf("Novo saldo: R$ %.2f\n", contas[indice].saldo);
        } else {
            printf("\nValor invalido para deposito!\n");
        }
    } else {
        printf("\nConta nao encontrada!\n");
    }
}

void realizarSaque(Conta contas[], int numContas) {
    int numero;
    double valor;

    printf("\nNumero da conta: ");
    scanf("%d", &numero);
    limparBuffer();

    int indice = buscarConta(contas, numContas, numero);

    if (indice != -1) {
        printf("Valor do saque: R$ ");
        scanf("%lf", &valor);
        limparBuffer();

        if (sacar(&contas[indice], valor)) {
            printf("\nSaque realizado com sucesso!\n");
            printf("Novo saldo: R$ %.2f\n", contas[indice].saldo);
        } else {
            printf("\nSaldo insuficiente ou valor invalido!\n");
        }
    } else {
        printf("\nConta nao encontrada!\n");
    }
}

void consultarSaldo(Conta contas[], int numContas) {
    int numero;

    printf("\nNumero da conta: ");
    scanf("%d", &numero);
    limparBuffer();

    int indice = buscarConta(contas, numContas, numero);

    if (indice != -1) {
        exibirConta(&contas[indice]);
    } else {
        printf("\nConta nao encontrada!\n");
    }
}

int main() {
    Conta contas[MAX_CONTAS];
    int numContas = 0;
    int opcao;

    do {
        limparTela();
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                if (numContas < MAX_CONTAS) {
                    criarConta(contas, &numContas);
                } else {
                    printf("\nLimite de contas atingido!\n");
                }
                break;

            case 2:
                realizarDeposito(contas, numContas);
                break;

            case 3:
                realizarSaque(contas, numContas);
                break;

            case 4:
                consultarSaldo(contas, numContas);
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while(opcao != 0);

    return 0;
}
