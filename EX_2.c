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
    printf("Seu chuta foi %d", chute);

    if chute == (num_secreto){
        printf("ACERTOU\n")
    }
    else{
        printf("ERRADO\n")
        }









}
