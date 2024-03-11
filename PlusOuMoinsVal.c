#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ATTEMPTS 10

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
            break;
        }

        if (attempts >= MAX_ATTEMPTS) {
            printf("Vous avez dépassé le nombre maximum d'essais. Vous avez perdu ! Le nombre secret était : %d\n", secretNumber);
            break;
        } else {
            printf("Il vous reste %d tentative(s).\n", MAX_ATTEMPTS - attempts);
        }
    } while (guess != secretNumber);

    return 0;
}