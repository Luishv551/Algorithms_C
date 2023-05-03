#include <stdio.h>

int main() {
    printf("***************************\n");
    printf("Bem vindo ao jogo de adivinhacao:\n");
    printf("***************************\n");

    int num_secreto = 42;

//    printf("O numero secreto e %d", num_secreto)


    printf("Qual o seu chute?\n");

    int chute;
    scanf("%d", &chute);
    printf("Seu chute foi %d\n", chute);

    if (chute == num_secreto){
        printf("ACERTOU\n");
    }
    else{

        if (chute > num_secreto) {
            printf ("Seu chute foi marior que o numero secreto\n");
        }
        else {
            printf("Seu chute foi menor que o numero secreto\n");
        }
        printf("ERRADO\n");
        }









}
