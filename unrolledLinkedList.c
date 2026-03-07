#include <stdio.h>
#include <stdlib.h>

#define NB_ELEM 8

typedef struct Page Page;

struct Page {
  int element[NB_ELEM];
  __int8_t bitmap;
  Page *next;
};

Page *constructorInit();
void insert(Page *firstPage, int element);
void printAllPage(Page *first);

//////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  Page *first = constructorInit();
  __int8_t a = 0;

  //printf("\n\n%u\n\n", a | (1ULL << 8));

  // insert(first, 5);
  // insert(first, 85);

  // printAllPage(first);
  return 0;
}

//////////////////////////////////////////////////////////////////////

Page *constructorInit() {
  Page *tmpPage = malloc(sizeof(Page));

  tmpPage->bitmap = 0;
  for (int i = 0; i < NB_ELEM; i++) {
    tmpPage->element[i] = -1;
  }
  tmpPage->next = NULL;

  return tmpPage;
}

void insert(Page *firstPage, int element) {
  if (firstPage == NULL)
    return;

  Page *current = firstPage;

  while (current != NULL) {
    for (int i = 0; i < NB_ELEM; i++) {
      if (!(current->bitmap & (1ULL << i))) {
        current->element[i] = element;
        current->bitmap = (current->bitmap | (1ULL << i));

        printf("Bitmap : %u", current->bitmap);
        return;
      }
      current = current->next;
    }
  }
}

void printAllPage(Page *first) {
  Page *current = first;
  int currentPageIndex = 0;
  while (current != NULL) {
    printf("Page %d\n\n", currentPageIndex);
    for (int i = 0; i < NB_ELEM; i++) {
      printf("Elem %d : %d\n", i, current->element[i]);
    }
    printf("\n\n");
    current = current->next;
    currentPageIndex++;
  }
}