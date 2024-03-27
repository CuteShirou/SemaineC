#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray
{
    int* pContent; //Contenu du tableau

    int iSize; //Taille atuelle du tableau
    int iCapacity; //Nombre de bloc allouée

} IntArray;


int main()
{
    /*
    6) 
        a) Demander à l'utilisateur de rentrer un nombre positif pour remplir un tableau Format d'affichage:
        "[0] => "
        "[1] => "
        "[n]=>"

        Vous devrez remplir le tableau au fur et à mesure des entrées

        b) Lorsque l'utilisateur entre '-1' le programme affiche le tableau et se termine
    */
    IntArray arr;
    arr.iSize = 0;
    arr.iCapacity = 10;

    arr.pContent = (int*)malloc(arr.iCapacity * sizeof(int));

    if (arr.pContent == NULL) {
        printf("Erreur d'allocation de mémoire.");
        return 1;
    }

    int count = 0;
    int num;

    while (1) {
        printf("[%d] => ", count);
        scanf("%d", &num);

        if (num == -1) {
            break;
        }

        if (arr.iSize >= arr.iCapacity) {
            arr.iCapacity *= 2;
            arr.pContent = (int*)realloc(arr.pContent, arr.iCapacity * sizeof(int));

            if (arr.pContent == NULL) {
                printf("Erreur de réallocation de mémoire.");
                return 1;
            }
        }

        arr.pContent[count] = num;
        arr.iSize++;
        count++;
    }
    printf("\nLe tableau est: \n");
    for (int i = 0; i < count; i++) {
        printf("[%d] => %d\n", i, arr.pContent[i]);
    }

    free(arr.pContent);

    return 0;
}