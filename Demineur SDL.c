#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINE -1

typedef struct {
  int value;
  int revealed;
  int flag;
} Tile;

typedef struct {
  int size;
  Tile **tiles;
} Grid;

void ClearBuffer() {
  while (getchar() != '\n')
    ;
}

void clearScreen() {
  system("clear"); 
}

int countDigits(int n) {
  int i = 0;
  if (n != -1) {
    do {
      i++;
      n /= 10;
    } while (n != 0);
  } else if (n == -1) {
    i = 0;
  }
  return i;
}

void space(int size, int nbr) {
  int nbrSpace = countDigits(size) - countDigits(nbr);
  for (int i = 0; i < nbrSpace; i++) {
    printf(" ");
  }
}

void printGrid(Grid *grid) {
  clearScreen();
  const char *colortab[] = {
      "\033[32m-\033[0m ",       "\033[38;5;226m1\033[0m ",
      "\033[38;5;214m2\033[0m ", "\033[38;5;208m3\033[0m ",
      "\033[38;5;183m4\033[0m ", "\033[38;5;141m5\033[0m ",
      "\033[30m6\033[0m ",       "\033[30m7\033[0m ",
      "\033[30m7\033[0m "};
  printf(" ");
  space(grid->size, -1);
  for (int i = 0; i < grid->size; i++) {
    printf("%d ", i+1);
    space(grid->size, i+1);
  }
  printf("\n");
  for (int i = 0; i < grid->size; i++) {
    printf("%d ", i+1);
    space(grid->size, i+1);
    for (int j = 0; j < grid->size; j++) {
      if (grid->tiles[i][j].revealed) {
        if (grid->tiles[i][j].value == MINE) {
          printf("\033[31m●\033[0m");
        } else if (grid->tiles[i][j].value >= 0) {
          printf("%s", colortab[grid->tiles[i][j].value]);
        }
        space(grid->size, grid->tiles[i][j].value);
      } else if (grid->tiles[i][j].flag) {
        printf("\033[34m⚑\033[0m ");
        space(grid->size, 1);
      } else {
        printf("\033[1;30m■\033[0m ");
        space(grid->size, 1);
      }
    }
    printf("\n");
  }
}

void endgame(int *x, int *y, Grid *grid) {
  clearScreen();
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
       grid->tiles[i][j].revealed = 1;
      }
  }printGrid(grid);
  free(x);
  free(y);
}

void initializeGrid(Grid *grid, int size) {
  grid->size = size;
  grid->tiles = (Tile **)malloc(size * sizeof(Tile *));
  for (int i = 0; i < size; i++) {
    grid->tiles[i] = (Tile *)malloc(size * sizeof(Tile));
    for (int j = 0; j < size; j++) {
      grid->tiles[i][j].value = 0;
      grid->tiles[i][j].revealed = 0;
    }
  }
}

void placeMines(Grid *grid, int numberOfMines) {
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
          if (nx >= 0 && nx < grid->size && ny >= 0 && ny < grid->size &&
              grid->tiles[nx][ny].value != MINE) {
            grid->tiles[nx][ny].value++;
          }
        }
      }
    } else {
      i--;
    }
  }
}

void revealTile(Grid *grid, int x, int y, int *X, int *Y, char drapeau) {
  if (x >= 0 && x < grid->size && y >= 0 && y < grid->size && drapeau == 'o') {
    if (grid->tiles[x][y].flag == 0) {
      grid->tiles[x][y].flag = 1;
    } else {
      grid->tiles[x][y].flag = 0;
    }
  }
  if (x >= 0 && x < grid->size && y >= 0 && y < grid->size &&
      !grid->tiles[x][y].revealed && drapeau == 'n') {
    grid->tiles[x][y].revealed = 1;

    if (grid->tiles[x][y].value == 0) {
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int nx = x + dx;
          int ny = y + dy;
          if (nx >= 0 && nx < grid->size && ny >= 0 && ny < grid->size) {
            revealTile(grid, nx, ny, X, Y, drapeau);
          }
        }
      }
    } 
  }
}

int isGameWin(Grid *grid) {
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      if (grid->tiles[i][j].value != MINE && !grid->tiles[i][j].revealed) {
        return 0;
      }
    }
  }
  return 1;
}

int isGameLost(Grid *grid) {
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      if (grid->tiles[i][j].value == MINE && grid->tiles[i][j].revealed) {
        return 1;
      }
    }
  }
  return 0;
}

void gameLoop(Grid *grid) {
  int *x = malloc(sizeof(int));
  int *y = malloc(sizeof(int));
  char drapeau = 'n';
  while (1) {
    printGrid(grid);
    char drapeau;
    printf("\nligne colonne\n");
    scanf("%d %d", &*x, &*y);
    ClearBuffer();
    printf("voulez vous mettre un drapeau ? o/n \n");
    scanf("%c", &drapeau);
    ClearBuffer();
    revealTile(grid, *x-1, *y-1, x, y, drapeau);
    if (isGameWin(grid)) {
      endgame(x, y, grid);
      printf("gg you win\n");
      break;
    }
    if (isGameLost(grid)){
      endgame(x, y, grid);
      printf("F you lose\n");
      break;
    }
  }
}

int main() {
  Grid grid;
  int nbrmines;
  int taille;
  char *rejouer[2];
  while (1) {
    clearScreen();
    printf("de quel taille voulez vous que la grille soit ?\n");
    scanf("%d", &taille);
    ClearBuffer();
    printf("combien de mine voulez vous ?\n");
    scanf("%d", &nbrmines);
    ClearBuffer();
    initializeGrid(&grid, taille);
    placeMines(&grid, nbrmines);
    gameLoop(&grid);
    printf("voulez vous rejouer o/n\n");
    scanf("%c", &rejouer);
    ClearBuffer();
    if (strcmp(rejouer, "n") == 0) {
      break;
    }
  }
  clearScreen();
  return 0;
}

void drawGrid(SDL_Renderer *renderer, Grid *grid, int tileSize) {
  const SDL_Color colors[] = {
      {0, 0, 0, 255},       // Black
      {0, 255, 0, 255},     // Green
      {226, 38, 0, 255},    // Red
      {214, 38, 0, 255},    // Orange
      {208, 38, 0, 255},    // Dark Orange
      {183, 38, 0, 255},    // Dark Red
      {141, 38, 0, 255},    // Dark Red
      {0, 0, 0, 255},       // Black
      {0, 0, 0, 255}        // Black
  };

  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      SDL_Rect rect = {j * tileSize, i * tileSize, tileSize, tileSize};
      if (grid->tiles[i][j].revealed) {
        if (grid->tiles[i][j].value == MINE) {
          SDL_SetRenderDrawColor(renderer, colors[2].r, colors[2].g, colors[2].b, colors[2].a);
        } else if (grid->tiles[i][j].value >= 0) {
          SDL_SetRenderDrawColor(renderer, colors[grid->tiles[i][j].value].r, colors[grid->tiles[i][j].value].g, colors[grid->tiles[i][j].value].b, colors[grid->tiles[i][j].value].a);
        }
      } else if (grid->tiles[i][j].flag) {
        SDL_SetRenderDrawColor(renderer, colors[7].r, colors[7].g, colors[7].b, colors[7].a);
      } else {
        SDL_SetRenderDrawColor(renderer, colors[8].r, colors[8].g, colors[8].b, colors[8].a);
      }
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

void gameLoop(Grid *grid, SDL_Renderer *renderer, int tileSize) {
  int *x = malloc(sizeof(int));
  int *y = malloc(sizeof(int));
  char drapeau = 'n';
  while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        endgame(x, y, grid);
        return;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        *x = mouseY / tileSize;
        *y = mouseX / tileSize;
        if (event.button.button == SDL_BUTTON_LEFT) {
          drapeau = 'n';
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          drapeau = 'o';
        }
        revealTile(grid, *x, *y, x, y, drapeau);
        if (isGameWin(grid)) {
          endgame(x, y, grid);
          printf("gg you win\n");
          return;
        }
        if (isGameLost(grid)) {
          endgame(x, y, grid);
          printf("F you lose\n");
          return;
        }
      }
    }
    SDL_RenderClear(renderer);
    drawGrid(renderer, grid, tileSize);
    SDL_RenderPresent(renderer);
  }
}

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window *window = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0);
  if (window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Set the grid size and number of mines
  Grid grid;
  int nbrmines;
  int taille;
  char *rejouer[2];
  while (1) {
    clearScreen();
    printf("de quel taille voulez vous que la grille soit ?\n");
    scanf("%d", &taille);
    ClearBuffer();
    printf("combien de mine voulez vous ?\n");
    scanf("%d", &nbrmines);
    ClearBuffer();
    initializeGrid(&grid, taille);
    placeMines(&grid, nbrmines);
    gameLoop(&grid, renderer, 800 / taille);
    printf("voulez vous rejouer o/n\n");
    scanf("%c", &rejouer);
    ClearBuffer();
    if (strcmp(rejouer, "n") == 0) {
      break;
    }
  }

  // Cleanup and quit SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}