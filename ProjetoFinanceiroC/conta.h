#ifndef CONTA_H
#define CONTA_H

typedef struct {
    int numero;
    char titular[100];
    double saldo;
    char tipo[20];
} Conta;

void inicializarConta(Conta* conta, int numero, const char* titular, const char* tipo);
int depositar(Conta* conta, double valor);
int sacar(Conta* conta, double valor);
void exibirConta(const Conta* conta);

#endif
