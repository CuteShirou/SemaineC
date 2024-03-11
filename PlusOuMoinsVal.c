#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secretNumber, guess, attempts = 0;
    srand(time(0)); // Seed the random number generator

    // Generate a random number between 1 and 100
    secretNumber = rand() % 100 + 1;

    printf("Bienvenue dans le jeu Plus ou Moins !\n");

    do {
        printf("Devinez le nombre secret (entre 1 et 100) : ");
        scanf("%d", &guess);
        attempts++;

        if (guess > secretNumber) {
            printf("C'est moins !\n");
        } else if (guess < secretNumber) {
            printf("C'est plus !\n");
        } else {
            printf("Félicitations ! Vous avez trouvé le nombre secret en %d tentatives.\n", attempts);
        }
    } while (guess != secretNumber);

    return 0;
}