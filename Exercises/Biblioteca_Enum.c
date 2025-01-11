/*
Crie um sistema simples de biblioteca:
- Defina um enum para Status do livro (Disponível, Emprestado, Em Manutenção)
- Crie uma struct Livro com: título, autor, status
- Implemente funções para:
  a) Cadastrar livro
  b) Alterar status
  c) Listar livros por status
*/

#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100

// Definição do enum para o status do livro
enum Status {
    DISPONIVEL,
    EMPRESTADO,
    EM_MANUTENCAO
};

// Estrutura para representar um livro
struct Livro {
    char titulo[100];
    char autor[100];
    enum Status status;
};

// Variável global para armazenar os livros
struct Livro biblioteca[MAX_LIVROS];
int totalLivros = 0;

// Função para cadastrar um livro
void cadastrarLivro(const char *titulo, const char *autor, enum Status status) {
    if (totalLivros < MAX_LIVROS) {
        strcpy(biblioteca[totalLivros].titulo, titulo);
        strcpy(biblioteca[totalLivros].autor, autor);
        biblioteca[totalLivros].status = status;
        totalLivros++;
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Erro: Capacidade máxima da biblioteca atingida.\n");
    }
}

// Função para alterar o status de um livro
void alterarStatus(const char *titulo, enum Status novoStatus) {
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].titulo, titulo) == 0) {
            biblioteca[i].status = novoStatus;
            printf("Status do livro '%s' alterado com sucesso.\n", titulo);
            return;
        }
    }
    printf("Erro: Livro '%s' não encontrado.\n", titulo);
}

// Função para listar livros por status
void listarLivrosPorStatus(enum Status status) {
    printf("Livros com status %d:\n", status);
    for (int i = 0; i < totalLivros; i++) {
        if (biblioteca[i].status == status) {
            printf("Título: %s | Autor: %s\n", biblioteca[i].titulo, biblioteca[i].autor);
        }
    }
}

int main() {
    // Exemplos de uso
    cadastrarLivro("O Senhor dos Anéis", "J.R.R. Tolkien", DISPONIVEL);
    cadastrarLivro("1984", "George Orwell", EMPRESTADO);
    cadastrarLivro("O Pequeno Príncipe", "Antoine de Saint-Exupéry", EM_MANUTENCAO);

    printf("\n--- Livros Disponíveis ---\n");
    listarLivrosPorStatus(DISPONIVEL);

    printf("\n--- Alterando Status ---\n");
    alterarStatus("1984", DISPONIVEL);

    printf("\n--- Livros Disponíveis Atualizados ---\n");
    listarLivrosPorStatus(DISPONIVEL);

    return 0;
}
