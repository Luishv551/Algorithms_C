#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Tamanho do tabuleiro
#define WIDTH 10
#define HEIGHT 10
// Tamanho máximo da cobra (pode ocupar todo o tabuleiro)
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)

// Variáveis globais do jogo
int gameOver;
int score;
int snakeLength;

// Posições (x, y) dos segmentos da cobra
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];

// Posição da fruta
int fruitX, fruitY;

// Caminho Hamiltoniano para (WIDTH x HEIGHT) = 100 posições no caso 10x10
// cyclePath[i][0] = x, cyclePath[i][1] = y
int cyclePath[WIDTH * HEIGHT][2];

// Índice no caminho que indica a posição da CABEÇA da cobra
int headIndex;

// --------------------------------------------------------------------
// Funções auxiliares
// --------------------------------------------------------------------

// Limpa a tela com sequências ANSI
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

// Gera fruta em posição livre (não ocupada pela cobra)
void spawnFruit() {
    do {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    } while (isCollisionWithSnake(fruitX, fruitY));
}

// Constrói o caminho (Hamiltonian path) que visita cada célula 10x10 uma vez:
// - Linha par (0,2,4,...): da esquerda para a direita
// - Linha ímpar (1,3,5,...): da direita para a esquerda
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
                // Cabeça da cobra
                printf("O");
            } else if (x == fruitX && y == fruitY) {
                // Fruta
                printf("F");
            } else {
                // Verifica se é parte do corpo (demais segmentos)
                int printed = 0;
                for (int k = 1; k < snakeLength; k++) {
                    if (snakeX[k] == x && snakeY[k] == y) {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    // Espaço vazio
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

    // Exibe pontuação
    printf("Score: %d\n", score);
}

// Configuração inicial
void setup() {
    gameOver = 0;
    score = 0;
    snakeLength = 1;

    srand(time(0));

    // Constrói o caminho Hamiltoniano
    fillHamiltonianPath();

    // A cobra começa na primeira célula do caminho
    headIndex = 0;
    snakeX[0] = cyclePath[0][0];
    snakeY[0] = cyclePath[0][1];

    // Gera a primeira fruta
    spawnFruit();
}

// Lógica principal do jogo
void logic() {
    // 1) Se a cobra já ocupa TODAS as células, é vitória
    if (snakeLength == WIDTH * HEIGHT) {
        printf("Voce venceu! A cobra preencheu todo o campo.\n");
        gameOver = 1;
        return;
    }

    // 2) Mover o corpo (do fim para o início)
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 3) Avançar o índice do caminho (headIndex)
    //    para a próxima célula do Hamiltonian path
    headIndex++;
    if (headIndex >= WIDTH * HEIGHT) {
        // Só por segurança, mas a rigor não é para estourar
        headIndex = headIndex % (WIDTH * HEIGHT);
    }

    // A cabeça vai para a próxima posição do path
    snakeX[0] = cyclePath[headIndex][0];
    snakeY[0] = cyclePath[headIndex][1];

    // 4) Verifica se houve colisão com o corpo
    //    (em tese, não deveria ocorrer se o path não cruza
    //     mas checamos por segurança)
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            // A cabeça encontrou um segmento do corpo
            gameOver = 1;
            return;
        }
    }

    // 5) Verifica se a cabeça está em cima da fruta
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        // A cobra "come" a fruta
        score += 10;
        snakeLength++;

        // Duplica o último segmento para crescer corretamente
        // (pega a posição antiga do último segmento e copia)
        snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
        snakeY[snakeLength - 1] = snakeY[snakeLength - 2];

        // Gera outra fruta
        spawnFruit();
    }
}

// Função principal
int main() {
    setup();

    while (!gameOver) {
        draw();
        logic();
        // Velocidade do jogo (50 ms)
        usleep(5);
    }

    // Se saiu do loop, verifica se foi vitória ou não
    if (snakeLength == WIDTH * HEIGHT) {
        printf("Parabens, voce venceu o Snake!\n");
    } else {
        printf("Game Over! Final Score: %d\n", score);
    }

    return 0;
}
