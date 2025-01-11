#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Tamanho do tabuleiro
#define WIDTH 10
#define HEIGHT 10
// Tamanho m�ximo da cobra (pode ocupar todo o tabuleiro)
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)

// Vari�veis globais do jogo
int gameOver;
int score;
int snakeLength;

// Posi��es (x, y) dos segmentos da cobra
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];

// Posi��o da fruta
int fruitX, fruitY;

// Caminho Hamiltoniano para (WIDTH x HEIGHT) = 100 posi��es no caso 10x10
// cyclePath[i][0] = x, cyclePath[i][1] = y
int cyclePath[WIDTH * HEIGHT][2];

// �ndice no caminho que indica a posi��o da CABE�A da cobra
int headIndex;

// --------------------------------------------------------------------
// Fun��es auxiliares
// --------------------------------------------------------------------

// Limpa a tela com sequ�ncias ANSI
void clearScreen() {
    printf("\033[H\033[J");
}

// Verifica se (x, y) coincide com alguma parte do corpo da cobra
int isCollisionWithSnake(int x, int y) {
    for (int i = 0; i < snakeLength; i++) {
        if (snakeX[i] == x && snakeY[i] == y) {
            return 1;
        }
    }
    return 0;
}

// Gera fruta em posi��o livre (n�o ocupada pela cobra)
void spawnFruit() {
    do {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    } while (isCollisionWithSnake(fruitX, fruitY));
}

// Constr�i o caminho (Hamiltonian path) que visita cada c�lula 10x10 uma vez:
// - Linha par (0,2,4,...): da esquerda para a direita
// - Linha �mpar (1,3,5,...): da direita para a esquerda
void fillHamiltonianPath() {
    int index = 0;
    for (int row = 0; row < HEIGHT; row++) {
        if (row % 2 == 0) {
            // Esquerda -> Direita
            for (int col = 0; col < WIDTH; col++) {
                cyclePath[index][0] = col;   // x
                cyclePath[index][1] = row;   // y
                index++;
            }
        } else {
            // Direita -> Esquerda
            for (int col = WIDTH - 1; col >= 0; col--) {
                cyclePath[index][0] = col;
                cyclePath[index][1] = row;
                index++;
            }
        }
    }
    // index deve chegar a WIDTH*HEIGHT = 100
}

// Desenha o tabuleiro e o estado do jogo
void draw() {
    clearScreen();

    // Borda superior
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // Linhas do campo
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0) printf("#"); // borda esquerda

            if (x == snakeX[0] && y == snakeY[0]) {
                // Cabe�a da cobra
                printf("O");
            } else if (x == fruitX && y == fruitY) {
                // Fruta
                printf("F");
            } else {
                // Verifica se � parte do corpo (demais segmentos)
                int printed = 0;
                for (int k = 1; k < snakeLength; k++) {
                    if (snakeX[k] == x && snakeY[k] == y) {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    // Espa�o vazio
                    printf(" ");
                }
            }

            if (x == WIDTH - 1) {
                printf("#"); // borda direita
            }
        }
        printf("\n");
    }

    // Borda inferior
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // Exibe pontua��o
    printf("Score: %d\n", score);
}

// Configura��o inicial
void setup() {
    gameOver = 0;
    score = 0;
    snakeLength = 1;

    srand(time(0));

    // Constr�i o caminho Hamiltoniano
    fillHamiltonianPath();

    // A cobra come�a na primeira c�lula do caminho
    headIndex = 0;
    snakeX[0] = cyclePath[0][0];
    snakeY[0] = cyclePath[0][1];

    // Gera a primeira fruta
    spawnFruit();
}

// L�gica principal do jogo
void logic() {
    // 1) Se a cobra j� ocupa TODAS as c�lulas, � vit�ria
    if (snakeLength == WIDTH * HEIGHT) {
        printf("Voce venceu! A cobra preencheu todo o campo.\n");
        gameOver = 1;
        return;
    }

    // 2) Mover o corpo (do fim para o in�cio)
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 3) Avan�ar o �ndice do caminho (headIndex)
    //    para a pr�xima c�lula do Hamiltonian path
    headIndex++;
    if (headIndex >= WIDTH * HEIGHT) {
        // S� por seguran�a, mas a rigor n�o � para estourar
        headIndex = headIndex % (WIDTH * HEIGHT);
    }

    // A cabe�a vai para a pr�xima posi��o do path
    snakeX[0] = cyclePath[headIndex][0];
    snakeY[0] = cyclePath[headIndex][1];

    // 4) Verifica se houve colis�o com o corpo
    //    (em tese, n�o deveria ocorrer se o path n�o cruza
    //     mas checamos por seguran�a)
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            // A cabe�a encontrou um segmento do corpo
            gameOver = 1;
            return;
        }
    }

    // 5) Verifica se a cabe�a est� em cima da fruta
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        // A cobra "come" a fruta
        score += 10;
        snakeLength++;

        // Duplica o �ltimo segmento para crescer corretamente
        // (pega a posi��o antiga do �ltimo segmento e copia)
        snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
        snakeY[snakeLength - 1] = snakeY[snakeLength - 2];

        // Gera outra fruta
        spawnFruit();
    }
}

// Fun��o principal
int main() {
    setup();

    while (!gameOver) {
        draw();
        logic();
        // Velocidade do jogo (50 ms)
        usleep(5);
    }

    // Se saiu do loop, verifica se foi vit�ria ou n�o
    if (snakeLength == WIDTH * HEIGHT) {
        printf("Parabens, voce venceu o Snake!\n");
    } else {
        printf("Game Over! Final Score: %d\n", score);
    }

    return 0;
}
