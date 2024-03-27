#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray
{
    int* pContent; //Contenu du tableau

    int iSize; //Taille atuelle du tableau
    int iCapacity; //Nombre de bloc allouée

} IntArray;

void Init( IntArray* pIntArray )
{
    pIntArray->pContent = NULL;
    pIntArray->iSize = 0;
    pIntArray->iCapacity = 0;
}

void Add( IntArray* pIntArray, int iValue)
{
    if (pIntArray->iSize == pIntArray->iCapacity)
    {
        pIntArray->iCapacity += 10;
        pIntArray->pContent = (int*)realloc(pIntArray->pContent, pIntArray->iCapacity * sizeof(int));
    }

    pIntArray->pContent[pIntArray->iSize] = iValue;
    pIntArray->iSize++;
}

void Insert( IntArray* pIntArray, int iValue, int iIndex)
{
    if (iIndex >= 0 && iIndex <= pIntArray->iSize)
    {
        if (pIntArray->iSize == pIntArray->iCapacity)
        {
            pIntArray->iCapacity += 10;
            pIntArray->pContent = (int*)realloc(pIntArray->pContent, pIntArray->iCapacity * sizeof(int));
        }

        for (int i = pIntArray->iSize; i > iIndex; i--)
        {
            pIntArray->pContent[i] = pIntArray->pContent[i - 1];
        }

        pIntArray->pContent[iIndex] = iValue;
        pIntArray->iSize++;
    }
}

void Remove( IntArray* pIntArray, int iIndex)
{
    if (iIndex >= 0 && iIndex < pIntArray->iSize)
    {
        for (int i = iIndex; i < pIntArray->iSize - 1; i++)
        {
            pIntArray->pContent[i] = pIntArray->pContent[i + 1];
        }

        pIntArray->iSize--;

        if (pIntArray->iSize < pIntArray->iCapacity - 10)
        {
            pIntArray->iCapacity -= 10;
            pIntArray->pContent = (int*)realloc(pIntArray->pContent, pIntArray->iCapacity * sizeof(int));
        }
    }
}

int Get(IntArray* pIntArray, int iIndex)
{
    if (iIndex >= 0 && iIndex < pIntArray->iSize)
    {
        return pIntArray->pContent[iIndex];
    }

    return 0;
}

void Print( IntArray* pIntArray )
{
    for (int i = 0; i < pIntArray->iSize; i++)
    {
        printf("%d ", pIntArray->pContent[i]);
    }

    printf("\n");
}

void Destroy( IntArray* pIntArray )
{
    free(pIntArray->pContent);
}

int main()
{
    IntArray oArray;
    Init( &oArray );

    Destroy( &oArray );

    return 0;
}