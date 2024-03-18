#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINE -1

typedef struct {
    int value;
    int revealed;
} Tile;

typedef struct {
    int size;
    Tile** tiles;
} Grid;

void initializeGrid(Grid* grid, int size) {
    grid->size = size;
    grid->tiles = (Tile**)malloc(size * sizeof(Tile*));
    for (int i = 0; i < size; i++) {
        grid->tiles[i] = (Tile*)malloc(size * sizeof(Tile));
        for (int j = 0; j < size; j++) {
            grid->tiles[i][j].value = 0;
            grid->tiles[i][j].revealed = 0;
        }
    }
}

void placeMines(Grid* grid, int numberOfMines) {
    srand(time(NULL));
    for (int i = 0; i < numberOfMines; i++) {
        int x = rand() % grid->size;
        int y = rand() % grid->size;
        if (grid->tiles[x][y].value != MINE) {
            grid->tiles[x][y].value = MINE;
            // Increment mine counters for adjacent tiles
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < grid->size && ny >= 0 && ny < grid->size && grid->tiles[nx][ny].value != MINE) {
                        grid->tiles[nx][ny].value++;
                    }
                }
            }
        } else {
            i--;
        }
    }
}

void printGrid(Grid* grid) {
    for (int i = 0; i < grid->size; i++) {
        for (int j = 0; j < grid->size; j++) {
            if (grid->tiles[i][j].revealed) {
                if (grid->tiles[i][j].value == MINE) {
                    printf("M ");
                } else {
                    printf("%d ", grid->tiles[i][j].value);
                }
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}

void revealTile(Grid* grid, int x, int y) {
    if (x >= 0 && x < grid->size && y >= 0 && y < grid->size && !grid->tiles[x][y].revealed) {
        grid->tiles[x][y].revealed = 1;
        if (grid->tiles[x][y].value == 0) {
            // Automatically reveal adjacent empty tiles
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < grid->size && ny >= 0 && ny < grid->size) {
                        revealTile(grid, nx, ny);
                    }
                }
            }
        } else if (grid->tiles[x][y].value == MINE) {
            printf("Game Over!\n");
            for (int i = 0; i < grid->size; i++) {
                for (int j = 0; j < grid->size; j++) {
                    if (grid->tiles[i][j].value == MINE) {
                        grid->tiles[i][j].revealed = 1;
                    }
                }
            }
            exit(0);
        }
    }
}

int isGameWon(Grid* grid) {
    for (int i = 0; i < grid->size; i++) {
        for (int j = 0; j < grid->size; j++) {
            if (grid->tiles[i][j].value != MINE && !grid->tiles[i][j].revealed) {
                return 0;
            }
        }
    }
    return 1;
}

void gameLoop(Grid* grid) {
    while (1) {
        printGrid(grid);
        int x, y;
        getUserInput(&x, &y);
        revealTile(grid, x, y);
        if (isGameWon(grid)) {
            printf("You won!\n");
            break;
        }
    }
}

int main() {
    Grid grid;
    initializeGrid(&grid, 10);
    placeMines(&grid, 10);
    gameLoop(&grid);
    return 0;
}   // End of code