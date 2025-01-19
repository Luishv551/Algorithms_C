# Sistema Bancário em C

## Descrição
Sistema bancário básico implementado em C com funcionalidades de criação de contas, operações financeiras e consultas. O projeto utiliza conceitos de programação estruturada, manipulação de arquivos e estruturas de dados.

## Estrutura de Arquivos

ProjetoFinanceiroC/
├── main.c         # Arquivo principal
├── conta.h        # Header de contas
├── conta.c        # Implementação de contas
├── util.h         # Header de utilidades
└── util.c         # Implementação de utilidades
## Funcionalidades

### 1. Gestão de Contas
* Criar nova conta
* Definir titular
* Escolher tipo de conta (Corrente/Poupança)
* Sistema de numeração automática

### 2. Operações Financeiras
* Depósito
* Saque
* Consulta de saldo

### 3. Utilitários
* Limpeza de tela
* Leitura segura de dados
* Tratamento de buffer
* Sistema de menus

## Estruturas de Dados

### Struct Conta
```c
typedef struct {
    int numero;           // Identificador único
    char titular[100];    // Nome do titular
    double saldo;        // Saldo atual
    char tipo[20];       // Tipo da conta
} Conta;

Funções Principais
Manipulação de Contas

inicializarConta(): Configura nova conta
depositar(): Adiciona valor ao saldo
sacar(): Remove valor do saldo
exibirConta(): Mostra detalhes da conta

Utilitários

limparTela(): Limpa console
pausar(): Pausa execução
limparBuffer(): Limpa buffer de entrada
lerInteiro(): Lê números inteiros com validação
lerDouble(): Lê números decimais com validação

Tratamento de Erros

Validação de entrada de dados
Verificação de saldo para saques
Tratamento de buffer para strings
Verificação de limites de contas

Constantes e Limites

#define MAX_CONTAS 100    // Máximo de contas
#define MAX_NOME 100      // Tamanho máximo do nome
#define MAX_TIPO 20       // Tamanho máximo do tipo

Conceitos Utilizados

Programação Estruturada
Estruturas (Structs)
Ponteiros
Passagem por Referência
Manipulação de Strings
Arrays
Funções
Headers e Modularização
Entrada/Saída
Controle de Fluxo