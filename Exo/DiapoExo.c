#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
  char *pContent;
  int iLength;
} String;

int GetStringLength(const char *str) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

String Create(const char *str) {
  String newString;
  int i = GetStringLength(str);
  newString.iLength = i;
  newString.pContent = malloc((newString.iLength + 1) * sizeof(char));
  memcpy(newString.pContent, str, newString.iLength + 1);
  return newString;
}

void Print(const String *pStr) {
  printf("%s\n", pStr->pContent);
}

String Concatenate1(const String *pStr1, const String *pStr2) {
  String newString;
  newString.iLength = pStr1->iLength + pStr2->iLength;
  newString.pContent = malloc((newString.iLength + 1) * sizeof(char));
  memcpy(newString.pContent, pStr1->pContent, pStr1->iLength);
  memcpy(newString.pContent + pStr1->iLength, pStr2->pContent, pStr2->iLength + 1);
  return newString;
}

String Concatenate2(const char *str1, const char *str2) {
  String newString;
  int i = GetStringLength(str1);
  int j = GetStringLength(str2);
  newString.iLength = i + j;
  newString.pContent = malloc((newString.iLength + 1) * sizeof(char));
  memcpy(newString.pContent, str1, i);
  memcpy(newString.pContent + i, str2, j + 1);
  return newString;
}

String Substring(const String *pStr1, int iStartIndex, int iLength) {
  String newString;
  newString.iLength = iLength;
  newString.pContent = malloc((iLength + 1) * sizeof(char));
  memcpy(newString.pContent, pStr1->pContent + iStartIndex, iLength);
  newString.pContent[iLength] = '\0';
  return newString;
}

String Insert(const String *pStr1, const String *pStr2, int iIndex) {
  String newString;
  newString.iLength = pStr1->iLength + pStr2->iLength;
  newString.pContent = malloc((newString.iLength + 1) * sizeof(char));
  memcpy(newString.pContent, pStr1->pContent, iIndex);
  memcpy(newString.pContent + iIndex, pStr2->pContent, pStr2->iLength);
  memcpy(newString.pContent + iIndex + pStr2->iLength, pStr1->pContent + iIndex, pStr1->iLength - iIndex + 1);
  return newString;
}

int AreEquals(const String *pStr1, const String *pStr2) {
  int i = 0;
  while (pStr1->pContent[i] != '\0' && pStr2->pContent[i] != '\0') {
    if (pStr1->pContent[i] != pStr2->pContent[i]) {
      return 0;
    }
    i++;
  }
  if (pStr1->pContent[i] == '\0' && pStr2->pContent[i] == '\0') {
    return 1;
  } else {
    return 0;
  }
}

int TryCastToInt(const String *pStr, int* pValue) {
  if (pStr == NULL || pValue == NULL) {
    return 0;
  }

  int sign = 1;
  int i = 0;
  if (pStr->pContent[0] == '-') {
    sign = -1;
    i = 1;
  }

  int value = 0;
  while (pStr->pContent[i] != '\0') {
    if (pStr->pContent[i] >= '0' && pStr->pContent[i] <= '9') {
      value = value * 10 + (pStr->pContent[i] - '0');
      i++;
    } else {
      return 0;
    }
  }

  *pValue = sign * value;
  return 1;
}

void Destroy(String *pStr) {
  free(pStr->pContent);
  pStr->pContent = NULL;
  pStr->iLength = 0;
}

int main() {
  String str1 = Create("Bonjour");
  printf("%s\n", str1.pContent);

  String str2 = Create("Aurevoir");

  String str3 = Concatenate1(&str1, &str2);

  printf("%s\n", str3.pContent);

  Destroy(&str1);
  Destroy(&str2);
  Destroy(&str3);

  return 0;
}