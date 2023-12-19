#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WALL '#'
#define PATH ' '

void initializeMaze(char **maze, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maze[i][j] = WALL;
        }
    }
    maze[1][0] = PATH; // Entrance
}

void carveMaze(char **maze, int x, int y, int n, int m) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    maze[x][y] = PATH;

    // Shuffle directions
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = dx[i];
        dx[i] = dx[r];
        dx[r] = temp;
        temp = dy[i];
        dy[i] = dy[r];
        dy[r] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i]*2;
        int ny = y + dy[i]*2;

        if (nx > 0 && nx < n - 1 && ny > 0 && ny < m - 1 && maze[nx][ny] == WALL) {
            maze[nx - dx[i]][ny - dy[i]] = PATH;
            carveMaze(maze, nx, ny, n, m);
        }
    }
}

void makeExit(char **maze, int n, int m) {
    int x = n - 2;
    int y = m - 2;

    while (x > 0 && maze[x][y] == WALL) {
        maze[x][y] = PATH;
        x--;
    }
    maze[n - 2][m - 1] = PATH; // Exit
}

void printMaze(char **maze, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == PATH) {
                putchar(PATH);
            } else {
                // Determine the character to print based on the position
                if ((i % 2 == 0) && (j % 2 == 0)) {
                    putchar('+'); // Corners
                } else if (i % 2 == 0) {
                    putchar('-'); // Horizontal walls
                } else {
                    putchar('|'); // Vertical walls
                }
            }
        }
        putchar('\n');
    }
}


int main() {
    int n, m;
    printf("Enter the dimensions of the maze (n m): ");
    scanf("%d %d", &n, &m);

    char **maze = (char **)malloc(n * sizeof(char *));
    if (maze == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        maze[i] = (char *)malloc(m * sizeof(char));
        if (maze[i] == NULL) {
            perror("Memory allocation failed");
            // Free already allocated rows
            for (int j = 0; j < i; j++) {
                free(maze[j]);
            }
            free(maze);
            return 1;
        }
    }

    srand(time(NULL));
    initializeMaze(maze, n, m);
    carveMaze(maze, 1, 1, n, m);
    makeExit(maze, n, m);
    printMaze(maze, n, m);

    for (int i = 0; i < n; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
