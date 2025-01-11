#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

int gameOver;
int score;
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int fruitX, fruitY;
char direction;

void setup() {
    gameOver = 0;
    score = 0;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeLength = 1;
    direction = ' '; // Inicialmente parada

    // Posicionar a fruta
    srand(time(0));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void draw() {
    system("cls"); // Limpa a tela

    // Desenhar borda superior
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Desenhar o campo de jogo
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#"); // Borda lateral

            if (i == snakeY[0] && j == snakeX[0])
                printf("O"); // Cabeça da cobra
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruta
            else {
                int print = 0;
                for (int k = 1; k < snakeLength; k++) {
                    if (i == snakeY[k] && j == snakeX[k]) {
                        printf("o"); // Corpo da cobra
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#"); // Borda lateral
        }
        printf("\n");
    }

    // Desenhar borda inferior
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Mostrar pontuação
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': direction = 'U'; break;
            case 's': direction = 'D'; break;
            case 'a': direction = 'L'; break;
            case 'd': direction = 'R'; break;
            case 'x': gameOver = 1; break; // Sair do jogo
        }
    }
}

void logic() {
    // Movendo o corpo da cobra
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Movendo a cabeça
    switch (direction) {
        case 'U': snakeY[0]--; break;
        case 'D': snakeY[0]++; break;
        case 'L': snakeX[0]--; break;
        case 'R': snakeX[0]++; break;
    }

    // Verificando colisão com bordas
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT)
        gameOver = 1;

    // Verificando colisão com o próprio corpo
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameOver = 1;
    }

    // Verificando se a fruta foi comida
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 10;
        snakeLength++;

        // Reposicionar a fruta
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        _sleep(100); // Controlar a velocidade do jogo
    }

    printf("Game Over! Final Score: %d\n", score);

    return 0;
}
