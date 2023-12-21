#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WALL '#'
#define PATH ' '
#define PLUS '+'
#define EMPTY ' '
#define HORZ '-'
#define VERT '|'

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

    char x, x_12, x_3, x_6, x_9;
         
    for (int i = 0; i < n; i++) 
      {
        for (int j = 0; j < m; j++) 
           { 
                                   x=maze[i+0][j+0];    
                     if (i>0)      x_12=maze[i-1][j+0]; else x_12=EMPTY;
                     if (j>0)      x_9=maze[i+0][j-1]; else x_9=EMPTY;
                     if ((i+1)<n)  x_6=maze[i+1][j+0]; else x_6=EMPTY;
                     if ((j+1)<m)  x_3=maze[i+0][j+1]; else x_3=EMPTY;

                 
             if (maze[i][j] == PATH) { putchar(PATH); }
              else {
                     if      ((x==PLUS)&&(x_9==EMPTY)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==VERT)) printf("│");       
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==EMPTY)&&(x_3==HORZ)&&(x_6==EMPTY)) printf("─");    
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==EMPTY)&&(x_3==HORZ)&&(x_6==EMPTY)) printf("─");  
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==VERT)) printf("┤");   
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==VERT)&&(x_3==HORZ)&&(x_6==VERT)) printf("├");    
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==EMPTY)) printf("┘");   
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==EMPTY)&&(x_3==EMPTY)&&(x_6==VERT)) printf("┐");    
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==EMPTY)&&(x_3==HORZ)&&(x_6==VERT)) printf("┬");  
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==VERT)&&(x_3==HORZ)&&(x_6==EMPTY)) printf("┴");  
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==VERT)&&(x_3==HORZ)&&(x_6==EMPTY)) printf("└"); 
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==EMPTY)) printf("┘"); 
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==EMPTY)&&(x_3==EMPTY)&&(x_6==VERT)) printf("│"); 
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==EMPTY)) printf("│");   
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==VERT)&&(x_3==EMPTY)&&(x_6==VERT)) printf("│");   
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==EMPTY)&&(x_3==HORZ)&&(x_6==VERT)) printf("┌");  
                     else if ((x==PLUS)&&(x_9==HORZ)&&(x_12==EMPTY)&&(x_3==EMPTY)&&(x_6==EMPTY)) printf("─");  
                     else if ((x==PLUS)&&(x_9==EMPTY)&&(x_12==EMPTY)&&(x_3==EMPTY)&&(x_6==VERT)) printf("│"); 
                     else if ((x==HORZ)) printf("─");
                     else if ((x==VERT)) printf("│");
                     else printf("─");   
                  }
          }
        putchar('\n');
    }
}

int main(int argc, char *argv[]) { if (argc != 3) { fprintf(stderr, "Usage: %s n m\n", argv[0]); return 1; }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

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

    for (int i = 0; i < n; i++) 
       for (int j = 0; j < m; j++) 
           if (maze[i][j] != PATH) 
                   {
                     if ((i % 2 == 0) && (j % 2 == 0)) {  maze[i][j]=PLUS; }
                       else if (i % 2 == 0) {  maze[i][j]=HORZ; }  // Horizontal walls
                       else {  maze[i][j]=VERT; } // Vertical walls 
                   };

    printMaze(maze, n, m);

    for (int i = 0; i < n; i++) free(maze[i]);
    free(maze);

    return 0;
}
