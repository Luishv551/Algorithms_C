#include <stdio.h>
#include <string.h>

#define NUM_ALUNOS 5

typedef struct {
    char nome[50];
    int matricula;
    float notas[3];
    float media;
} Aluno;

int main() {
    Aluno alunos[NUM_ALUNOS];
    int i, j, indexMaiorMedia = 0;
    float somaNotas;

    // Cadastro de alunos
    for (i = 0; i < NUM_ALUNOS; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", alunos[i].nome);
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);
        somaNotas = 0;
        for (j = 0; j < 3; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%f", &alunos[i].notas[j]);
            somaNotas += alunos[i].notas[j];
        }
        alunos[i].media = somaNotas / 3.0;
    }

    // Processamento e saída
    for (i = 0; i < NUM_ALUNOS; i++) {
        printf("\nAluno: %s\n", alunos[i].nome);
        printf("Media: %.2f\n", alunos[i].media);
        printf("Situacao: %s\n", (alunos[i].media >= 7.0) ? "Aprovado" : "Reprovado");
        if (alunos[i].media > alunos[indexMaiorMedia].media) {
            indexMaiorMedia = i;
        }
    }

    printf("\nAluno com maior media: %s (%.2f)\n", alunos[indexMaiorMedia].nome, alunos[indexMaiorMedia].media);

    return 0;
}
