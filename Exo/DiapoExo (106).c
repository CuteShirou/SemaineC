#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* pNext;
    struct Node* pPrevious;

    int iValue;
} Node;

typedef struct List
{
    Node* pFirst;

    int iCount;
} List;

void Init(List* pList)
{
    pList->pFirst = NULL;
    pList->iCount = 0;
}

void AddFirst(List* pList, int iValue)
{
    Node* pNode = (Node*)malloc(sizeof(Node));
    pNode->iValue = iValue;
    pNode->pNext = pList->pFirst;
    pNode->pPrevious = NULL;

    if (pList->pFirst != NULL)
    {
        pList->pFirst->pPrevious = pNode;
    }

    pList->pFirst = pNode;
    pList->iCount++;
}

void AddLast(List* pList, int iValue)
{
    Node* pNode = (Node*)malloc(sizeof(Node));
    pNode->iValue = iValue;
    pNode->pNext = NULL;

    if (pList->pFirst == NULL)
    {
        pNode->pPrevious = NULL;
        pList->pFirst = pNode;
    }
    else
    {
        Node* pCurrent = pList->pFirst;
        while (pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        pNode->pPrevious = pCurrent;
        pCurrent->pNext = pNode;
    }

    pList->iCount++;
}

void AddAfterNode(List* pList, Node* pNode, int iValue)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->iValue = iValue;
    pNewNode->pNext = pNode->pNext;
    pNewNode->pPrevious = pNode;

    if (pNode->pNext != NULL)
    {
        pNode->pNext->pPrevious = pNewNode;
    }

    pNode->pNext = pNewNode;
    pList->iCount++;
}

void Insert(List* pList, int iValue, int iIndex)
{
    if (iIndex < 0 || iIndex > pList->iCount)
    {
        printf("Invalid index\n");
        return;
    }

    if (iIndex == 0)
    {
        AddFirst(pList, iValue);
    }
    else if (iIndex == pList->iCount)
    {
        AddLast(pList, iValue);
    }
    else
    {
        Node* pNode = GetNode(pList, iIndex - 1);
        AddAfterNode(pList, pNode, iValue);
    }
}

void Remove(List* pList, int iIndex)
{
    if (iIndex < 0 || iIndex >= pList->iCount)
    {
        printf("Invalid index\n");
        return;
    }

    if (iIndex == 0)
    {
        Node* pNode = pList->pFirst;
        pList->pFirst = pNode->pNext;
        if (pNode->pNext != NULL)
        {
            pNode->pNext->pPrevious = NULL;
        }
        free(pNode);
    }
    else
    {
        Node* pNode = GetNode(pList, iIndex);
        pNode->pPrevious->pNext = pNode->pNext;
        if (pNode->pNext != NULL)
        {
            pNode->pNext->pPrevious = pNode->pPrevious;
        }
        free(pNode);
    }

    pList->iCount--;
}

void RemoveNode(List* pList, Node* pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    if (pNode->pPrevious == NULL)
    {
        pList->pFirst = pNode->pNext;
    }
    else
    {
        pNode->pPrevious->pNext = pNode->pNext;
    }

    if (pNode->pNext != NULL)
    {
        pNode->pNext->pPrevious = pNode->pPrevious;
    }

    free(pNode);
    pList->iCount--;
}

Node* GetNode(List* pList, int iIndex)
{
    if (iIndex < 0 || iIndex >= pList->iCount)
    {
        return NULL;
    }

    Node* pNode = pList->pFirst;
    for (int i = 0; i < iIndex; i++)
    {
        pNode = pNode->pNext;
    }

    return pNode;
}

void Print(List* pList)
{
    Node* pNode = pList->pFirst;
    while (pNode != NULL)
    {
        printf("%d ", pNode->iValue);
        pNode = pNode->pNext;
    }
    printf("\n");
}

void Destroy(List* pList)
{
    Node* pNode = pList->pFirst;
    while (pNode != NULL)
    {
        Node* pNext = pNode->pNext;
        free(pNode);
        pNode = pNext;
    }
    pList->pFirst = NULL;
    pList->iCount = 0;
}

int main()
{
    List oList;
    Init(&oList);

    AddLast(&oList, 1);
    AddLast(&oList, 2);
    AddLast(&oList, 3);

    AddFirst(&oList, 0);

    Print(&oList);

    Destroy(&oList);

    return 0;
}