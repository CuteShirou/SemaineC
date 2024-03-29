#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_ATTEMPTS 10
#define MAX_GUESSES 100

void Clearbuffer() {
    while (getchar() != '\n');
}

int main() {
    int secretNumber, guess, attempts = 0;
    int minLimit, maxLimit;
    char playAgain;
    int guesses[MAX_GUESSES]; // Array to store player guesses
    int numGuesses = 0; // Counter for number of guesses
    srand(time(0)); // Seed the random number generator

    printf("Bienvenue dans le jeu Plus ou Moins !\n");
    printf("Entrez la limite minimale : ");
    while (scanf("%d", &minLimit) != 1) {
        printf("Veuillez entrer un entier valide pour la limite minimale : ");
        Clearbuffer();
    }
    printf("Entrez la limite maximale : ");
    while (scanf("%d", &maxLimit) != 1) {
        printf("Veuillez entrer un entier valide pour la limite maximale : ");
        Clearbuffer();
    }

    do {
        // Generate a random number between minLimit and maxLimit
        secretNumber = rand() % (maxLimit - minLimit + 1) + minLimit;

        printf("Devinez le nombre secret (entre %d et %d) : ", minLimit, maxLimit);
        do {
            while (scanf("%d", &guess) != 1 || guess < minLimit || guess > maxLimit) {
                printf("Veuillez entrer un entier valide entre %d et %d : ", minLimit, maxLimit);
                Clearbuffer();
            }
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

            // Store the guess in the array
            guesses[numGuesses] = guess;
            numGuesses++;

        } while (guess != secretNumber);

        printf("Vos tentatives : ");
        for (int i = 0; i < numGuesses; i++) {
            printf("%d ", guesses[i]);
        }
        printf("\n");

        printf("Voulez-vous recommencer ? (O/N) : ");
        scanf(" %c", &playAgain);
        attempts = 0; // Reset the number of attempts

        if (tolower(playAgain) == 'o') {
            printf("Entrez la nouvelle limite minimale : ");
            while (scanf("%d", &minLimit) != 1) {
                printf("Veuillez entrer un entier valide pour la limite minimale : ");
                Clearbuffer();
            }
            printf("Entrez la nouvelle limite maximale : ");
            while (scanf("%d", &maxLimit) != 1) {
                printf("Veuillez entrer un entier valide pour la limite maximale : ");
                Clearbuffer();
            }
        }

    } while (tolower(playAgain) == 'o');

    printf("Les nombres que vous avez devinés sont : ");
    for (int i = 0; i < numGuesses; i++) {
        printf("%d ", guesses[i]);
    }
    printf("\n");

    return 0;
}