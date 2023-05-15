#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    int numerosecreto = 82;
    int chute;
    int tentativas = 0;
    int ganhou = 0;

    printf("____________________________________\n");
    printf("|                                  |\n");
    printf("|       Jogo de adivinhação        |\n");
    printf("|        Diga um numero            |\n");
    printf("|     Se for certo você ganha      |\n");
    printf("|     -----------------------      |\n");

    while (ganhou == 0) {
        printf("|          Tentativa %d             |\n", tentativas + 1);
        printf("|        Informe o numero          |\n ==>");
        scanf("%d", &chute);

        if(chute < 0) {
            printf("|Não é permitido numeros negativos|\n");

            continue;
        }

        printf("|         Seu chute foi: %d        |\n", chute);
        int acertou = (chute == numerosecreto);

        if (acertou) {
            printf("|     Parabens você acertou!      |\n");

            ganhou = 1;
        } else {
            if (chute > numerosecreto) {
            printf("|Seu chute foi maior que o numero|\n");
            } else {
            printf("|Seu chute foi menor que o numero|\n");
            }

        }
        tentativas = tentativas + 1;
    }
    printf("Fim de jogo!");

}
