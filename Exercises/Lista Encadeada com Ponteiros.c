#include <stdio.h>
#include <stdlib.h>

// Definicao da struct Node
typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

// Funcao para criar um novo no
Node* criarNode(int valor) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->valor = valor;
    novoNode->proximo = NULL;
    return novoNode;
}

// Funcao para inserir no inicio da lista
void inserirInicio(Node** cabeca, int valor) {
    Node* novoNode = criarNode(valor);
    novoNode->proximo = *cabeca;
    *cabeca = novoNode;
}

// Funcao para inserir no final da lista
void inserirFinal(Node** cabeca, int valor) {
    Node* novoNode = criarNode(valor);
    if (*cabeca == NULL) {
        *cabeca = novoNode;
        return;
    }
    Node* temp = *cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNode;
}

// Funcao para remover um valor especifico
void removerValor(Node** cabeca, int valor) {
    Node* temp = *cabeca;
    Node* anterior = NULL;

    // Caso o valor esteja no inicio
    if (temp != NULL && temp->valor == valor) {
        *cabeca = temp->proximo;
        free(temp);
        return;
    }

    // Procurar o valor na lista
    while (temp != NULL && temp->valor != valor) {
        anterior = temp;
        temp = temp->proximo;
    }

    // Se o valor nao foi encontrado
    if (temp == NULL) {
        printf("Valor %d nao encontrado na lista.\n", valor);
        return;
    }

    // Remover o no
    anterior->proximo = temp->proximo;
    free(temp);
}

// Funcao para imprimir a lista
void imprimirLista(Node* cabeca) {
    Node* temp = cabeca;
    while (temp != NULL) {
        printf("%d -> ", temp->valor);
        temp = temp->proximo;
    }
    printf("NULL\n");
}

// Funcao principal para demonstrar o funcionamento
int main() {
    Node* lista = NULL;

    inserirInicio(&lista, 10);
    inserirInicio(&lista, 20);
    inserirFinal(&lista, 30);
    inserirFinal(&lista, 40);

    printf("Lista inicial: ");
    imprimirLista(lista);

    removerValor(&lista, 20);
    printf("Apos remover 20: ");
    imprimirLista(lista);

    removerValor(&lista, 50); // Tentativa de remover valor inexistente

    return 0;
}
