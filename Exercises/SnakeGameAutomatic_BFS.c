#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 10
#define MAX_SNAKE_LENGTH 100

// Variáveis de jogo
int gameOver;
int score;
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int fruitX, fruitY;
char direction;

// Estruturas para BFS
typedef struct {
    int x;
    int y;
} Node;

#define MAX_QUEUE (WIDTH * HEIGHT)

typedef struct {
    Node data[MAX_QUEUE];
    int front, rear;
} Queue;

// Funções de fila
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE == q->front;
}

void enqueue(Queue *q, int x, int y) {
    if (!isFull(q)) {
        q->data[q->rear].x = x;
        q->data[q->rear].y = y;
        q->rear = (q->rear + 1) % MAX_QUEUE;
    }
}

Node dequeue(Queue *q) {
    Node n = { -1, -1 };
    if (!isEmpty(q)) {
        n = q->data[q->front];
        q->front = (q->front + 1) % MAX_QUEUE;
    }
    return n;
}

// Função para verificar colisão com a cobra
int isCollision(int x, int y) {
    for (int i = 0; i < snakeLength; i++) {
        if (snakeX[i] == x && snakeY[i] == y) {
            return 1;
        }
    }
    return 0;
}

// Verifica se pode mover para (x, y)
int canMove(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return 0;
    if (isCollision(x, y))
        return 0;
    return 1;
}

// Nova função para verificar se existe caminho até a cauda
int hasPathToTail() {
    int lastX = snakeX[snakeLength - 1];
    int lastY = snakeY[snakeLength - 1];

    // Cria um mapa temporário do campo
    int tempMap[WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            tempMap[i][j] = 0;
        }
    }

    // Marca posições ocupadas pela cobra
    for(int i = 0; i < snakeLength - 1; i++) {
        tempMap[snakeX[i]][snakeY[i]] = 1;
    }

    // Usa BFS para encontrar caminho até a cauda
    Queue q;
    initQueue(&q);

    int visited[WIDTH][HEIGHT] = {0};
    enqueue(&q, snakeX[0], snakeY[0]);
    visited[snakeX[0]][snakeY[0]] = 1;

    while(!isEmpty(&q)) {
        Node curr = dequeue(&q);

        // Se chegou na cauda
        if(curr.x == lastX && curr.y == lastY) {
            return 1;
        }

        // Movimentos possíveis
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for(int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if(newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT
               && !tempMap[newX][newY] && !visited[newX][newY]) {
                visited[newX][newY] = 1;
                enqueue(&q, newX, newY);
            }
        }
    }

    return 0;
}

// BFS para encontrar caminho até a fruta
char findPathBFS(int sx, int sy, int fx, int fy) {
    if (sx == fx && sy == fy) return ' ';

    int visited[WIDTH][HEIGHT];
    int parentX[WIDTH][HEIGHT];
    int parentY[WIDTH][HEIGHT];

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            visited[i][j] = 0;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }
    }

    int dx[4] = { 0,  0, -1,  1 };
    int dy[4] = {-1,  1,  0,  0 };

    Queue q;
    initQueue(&q);
    visited[sx][sy] = 1;
    enqueue(&q, sx, sy);

    int found = 0;

    while (!isEmpty(&q)) {
        Node curr = dequeue(&q);
        int cx = curr.x;
        int cy = curr.y;

        if (cx == fx && cy == fy) {
            found = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (canMove(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                parentX[nx][ny] = cx;
                parentY[nx][ny] = cy;
                enqueue(&q, nx, ny);
            }
        }
    }

    if (!found) return ' ';

    int px = fx;
    int py = fy;

    while (!(parentX[px][py] == sx && parentY[px][py] == sy)) {
        if (parentX[px][py] == -1) return ' ';
        int tempX = parentX[px][py];
        int tempY = parentY[px][py];
        px = tempX;
        py = tempY;
    }

    if (px > sx) return 'R';
    if (px < sx) return 'L';
    if (py > sy) return 'D';
    if (py < sy) return 'U';

    return ' ';
}

// Nova versão da função autoInput com movimento mais inteligente
void autoInput() {
    int headX = snakeX[0];
    int headY = snakeY[0];

    // Arrays para os possíveis movimentos
    int dx[4] = {0, 0, -1, 1};  // U, D, L, R
    int dy[4] = {-1, 1, 0, 0};
    char moves[4] = {'U', 'D', 'L', 'R'};

    // 1) Primeiro, tenta encontrar um caminho seguro para a fruta
    char bfsMove = findPathBFS(headX, headY, fruitX, fruitY);

    if(bfsMove != ' ') {
        // Simula o movimento para verificar se é seguro
        int nextX = headX;
        int nextY = headY;

        switch(bfsMove) {
            case 'U': nextY--; break;
            case 'D': nextY++; break;
            case 'L': nextX--; break;
            case 'R': nextX++; break;
        }

        // Verifica se após o movimento ainda terá caminho para a cauda
        if(canMove(nextX, nextY)) {
            // Simula o movimento
            int oldX = snakeX[0];
            int oldY = snakeY[0];
            snakeX[0] = nextX;
            snakeY[0] = nextY;

            if(hasPathToTail()) {
                snakeX[0] = oldX;
                snakeY[0] = oldY;
                direction = bfsMove;
                return;
            }

            // Desfaz a simulação
            snakeX[0] = oldX;
            snakeY[0] = oldY;
        }
    }

    // 2) Se não encontrou caminho seguro para a fruta,
    // procura o movimento mais seguro (que mantém mais opções abertas)
    int bestScore = -1;
    char bestMove = ' ';

    for(int i = 0; i < 4; i++) {
        int newX = headX + dx[i];
        int newY = headY + dy[i];

        if(canMove(newX, newY)) {
            // Simula o movimento
            int oldX = snakeX[0];
            int oldY = snakeY[0];
            snakeX[0] = newX;
            snakeY[0] = newY;

            // Conta quantos movimentos ficarão disponíveis
            int availableMoves = 0;
            for(int j = 0; j < 4; j++) {
                int nextX = newX + dx[j];
                int nextY = newY + dy[j];
                if(canMove(nextX, nextY)) {
                    availableMoves++;
                }
            }

            // Adiciona bônus se mantiver caminho para a cauda
            if(hasPathToTail()) {
                availableMoves += 10;
            }

            // Atualiza melhor movimento se necessário
            if(availableMoves > bestScore) {
                bestScore = availableMoves;
                bestMove = moves[i];
            }

            // Desfaz a simulação
            snakeX[0] = oldX;
            snakeY[0] = oldY;
        }
    }

    if(bestMove != ' ') {
        direction = bestMove;
        return;
    }

    // 3) Se ainda assim não encontrou movimento, tenta qualquer um válido
    for(int i = 0; i < 4; i++) {
        int newX = headX + dx[i];
        int newY = headY + dy[i];
        if(canMove(newX, newY)) {
            direction = moves[i];
            return;
        }
    }
}

// Configuração inicial
void setup() {
    gameOver = 0;
    score = 0;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeLength = 1;
    direction = ' ';

    srand(time(0));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

// Limpa a tela
void clearScreen() {
    printf("\033[H\033[J");
}

// Desenho do campo
void draw() {
    clearScreen();

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");

            if (i == snakeY[0] && j == snakeX[0]) {
                printf("O");
            } else if (i == fruitY && j == fruitX) {
                printf("F");
            } else {
                int printBody = 0;
                for (int k = 1; k < snakeLength; k++) {
                    if (snakeX[k] == j && snakeY[k] == i) {
                        printf("o");
                        printBody = 1;
                        break;
                    }
                }
                if (!printBody) {
                    printf(" ");
                }
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

// Atualiza a lógica do jogo
void logic() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    switch (direction) {
        case 'U': snakeY[0]--; break;
        case 'D': snakeY[0]++; break;
        case 'L': snakeX[0]--; break;
        case 'R': snakeX[0]++; break;
    }

    if (snakeX[0] < 0 || snakeX[0] >= WIDTH ||
        snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        gameOver = 1;
        return;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
            return;
        }
    }

    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 10;
        snakeLength++;
        do {
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        } while (isCollision(fruitX, fruitY));
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        autoInput();
        logic();
        usleep(15000); // 150ms de delay - ajuste conforme necessário
    }

    printf("Game Over! Score final: %d\n", score);
    return 0;
}
