#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 10
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)
#define INF 999999

// Variáveis de jogo
int gameOver;
int score;
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int fruitX, fruitY;
char direction;

// Estrutura para BFS
typedef struct {
    int x, y;
} Point;

typedef struct {
    Point points[WIDTH * HEIGHT];
    int front, rear;
} Queue;

// Funções da Queue
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

void enqueue(Queue *q, int x, int y) {
    q->points[q->rear].x = x;
    q->points[q->rear].y = y;
    q->rear++;
}

Point dequeue(Queue *q) {
    Point p = q->points[q->front];
    q->front++;
    return p;
}

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}

// Funções auxiliares
int isInBounds(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

int isCollision(int x, int y) {
    for (int i = 0; i < snakeLength; i++) {
        if (x == snakeX[i] && y == snakeY[i]) {
            return 1;
        }
    }
    return 0;
}

// Encontra caminho usando BFS
int findPath(int startX, int startY, int targetX, int targetY, char* firstMove) {
    Queue q;
    initQueue(&q);

    int visited[WIDTH][HEIGHT] = {0};
    char moves[WIDTH][HEIGHT] = {0};

    visited[startY][startX] = 1;
    enqueue(&q, startX, startY);

    int dx[] = {-1, 1, 0, 0};  // L, R, U, D
    int dy[] = {0, 0, -1, 1};
    char moveDir[] = {'L', 'R', 'U', 'D'};

    while (!isQueueEmpty(&q)) {
        Point curr = dequeue(&q);

        if (curr.x == targetX && curr.y == targetY) {
            *firstMove = moves[targetY][targetX];
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isInBounds(newX, newY) && !visited[newY][newX] && !isCollision(newX, newY)) {
                visited[newY][newX] = 1;
                moves[newY][newX] = (curr.x == startX && curr.y == startY) ? moveDir[i] : moves[curr.y][curr.x];
                enqueue(&q, newX, newY);
            }
        }
    }

    return 0;
}

// Decide próximo movimento
void decideNextMove() {
    int headX = snakeX[0];
    int headY = snakeY[0];
    char nextMove;

    // Primeira tentativa: ir direto para a fruta
    if (findPath(headX, headY, fruitX, fruitY, &nextMove)) {
        direction = nextMove;
        return;
    }

    // Segunda tentativa: encontrar qualquer movimento válido
    int dx[] = {-1, 1, 0, 0};  // L, R, U, D
    int dy[] = {0, 0, -1, 1};
    char moves[] = {'L', 'R', 'U', 'D'};

    for (int i = 0; i < 4; i++) {
        int newX = headX + dx[i];
        int newY = headY + dy[i];

        if (isInBounds(newX, newY) && !isCollision(newX, newY)) {
            direction = moves[i];
            return;
        }
    }
}

// Configuração inicial
void setup() {
    gameOver = 0;
    score = 0;

    // Posiciona cobra no centro
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeLength = 1;
    direction = 'R';  // Começa movendo para direita

    // Posiciona primeira fruta
    do {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    } while (isCollision(fruitX, fruitY));
}

// Desenha o jogo
void draw() {
    printf("\033[H\033[J");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            if (x == snakeX[0] && y == snakeY[0])
                printf("O");
            else if (x == fruitX && y == fruitY)
                printf("F");
            else {
                int isBody = 0;
                for (int i = 1; i < snakeLength; i++) {
                    if (x == snakeX[i] && y == snakeY[i]) {
                        printf("o");
                        isBody = 1;
                        break;
                    }
                }
                if (!isBody) printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("Score: %d | Length: %d\n", score, snakeLength);
}

// Atualiza estado do jogo
void update() {
    // Move o corpo
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }

    // Move a cabeça
    switch (direction) {
        case 'L': snakeX[0]--; break;
        case 'R': snakeX[0]++; break;
        case 'U': snakeY[0]--; break;
        case 'D': snakeY[0]++; break;
    }

    // Verifica colisões
    if (!isInBounds(snakeX[0], snakeY[0])) {
        gameOver = 1;
        return;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
            return;
        }
    }

    // Verifica fruta
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 10;
        snakeLength++;

        if (snakeLength == WIDTH * HEIGHT) {
            gameOver = 1;  // Vitória!
            return;
        }

        do {
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        } while (isCollision(fruitX, fruitY));
    }
}

int main() {
    srand(time(0));
    setup();

    while (!gameOver) {
        draw();
        decideNextMove();
        update();
        usleep(1000);  // 100ms delay
    }

    draw();
    if (snakeLength == WIDTH * HEIGHT)
        printf("\nVocê venceu! Pontuação final: %d\n", score);
    else
        printf("\nGame Over! Pontuação final: %d\n", score);

    return 0;
}
