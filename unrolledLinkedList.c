#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_ELEM 8

typedef struct Page Page;

struct Page {
  int element[NB_ELEM];
  uint8_t bitmap;
  Page *next;
};

typedef struct Position {
  int element;
  uint8_t index;
  Page *pageRef;
} Position;

typedef struct Occurences {
  Position *founds;
  int number;
} Occurences;

Page *constructorInit();
void insert(Page **firstPage, int element);
void removePosition(Page **firstPage, Position position);
Occurences research(Page **firstPage, int element);
void compact(Page **firstPage);
void printPositions(Occurences occurences);
void printAllPage(Page *first);
void freeAllPages(Page *first);

//////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  printf("\n\n\n");

  srand(time(NULL));
  Page *first = NULL;

  for (int i = 0; i < 7; i++) {
    insert(&first, rand() % 15);
  }

  Occurences occ = research(&first, 5);

  printAllPage(first);

  for (int i = 0; i < occ.number; i++) {
    removePosition(&first, occ.founds[i]);
  }
  free(occ.founds);

  printAllPage(first);

  compact(&first);
  printAllPage(first);

  freeAllPages(first);
  printf("\n\n\n");

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

//////////////////////////////////////////////////////////////////////

void insert(Page **firstPage, int element) {
  if (*firstPage == NULL) {
    *firstPage = constructorInit();
  }

  Page *current = *firstPage;

  while (current != NULL) {
    for (int i = 0; i < NB_ELEM; i++) {
      if (!(current->bitmap & (1 << i))) {
        current->element[i] = element;
        current->bitmap |= (1 << i);
        return;
      }
    }
    if (current->next == NULL) {
      current->next = constructorInit();
    }
    current = current->next;
  }
}

void removePosition(Page **firstPage, Position position) {
  if (*firstPage == NULL) {
    printf("Error : NULL firstPage");
    return;
  }

  position.pageRef->element[position.index] = 0;
  position.pageRef->bitmap &= ~(1 << position.index);
}

Occurences research(Page **firstPage, int element) {
  Occurences occurences;
  occurences.founds = NULL;
  occurences.number = 0;

  if (*firstPage == NULL) {
    printf("Error : NULL firstPage");
    return occurences;
  }

  Position *founds = NULL;
  Page *current = *firstPage;
  int count = 0;

  while (current != NULL) {
    for (int i = 0; i < NB_ELEM; i++) {
      if (current->bitmap & (1 << i)) {
        if (current->element[i] == element) {
          count++;
          if (founds == NULL) {
            founds = malloc(sizeof(Position));
          } else {
            founds = realloc(founds, count * sizeof(Position));
          }

          Position tmp = {tmp.element = element, tmp.index = i, tmp.pageRef = current};
          founds[count - 1] = tmp;
        }
      }
    }
    current = current->next;
  }

  if (count == 0) {
    printf("Alert : Element (%d) not found.\n\n", element);
    return occurences;
  }

  occurences.founds = founds;
  occurences.number = count;

  return occurences;
}

void compact(Page **firstPage) {
  if (*firstPage == NULL) {
    return;
  }

  int moved;
  do {
    moved = 0;

    Page *current = *firstPage;
    Position refHoleFound;
    int isRefFound = 0;

    while (current != NULL) {
      for (int i = 0; i < NB_ELEM; i++) {
        if ((current->bitmap & (1 << i)) == 0) {
          if (!isRefFound) {
            refHoleFound.index = i;
            refHoleFound.pageRef = current;
            isRefFound = 1;
          }
        } else if (isRefFound) {
          refHoleFound.pageRef->element[refHoleFound.index] = current->element[i];
          refHoleFound.pageRef->bitmap |= (1 << refHoleFound.index);

          current->element[i] = 0;
          current->bitmap &= ~(1 << i);

          refHoleFound.index = i;
          refHoleFound.pageRef = current;
          moved = 1;
        }
      }
      current = current->next;
    }
  } while (moved);
}

//////////////////////////////////////////////////////////////////////

void printPositions(Occurences occurences) {
  int count = 0;
  for (int i = 0; i < occurences.number; i++) {
    printf("Position found :\n\n");
    printf("Element : %d\n", occurences.founds[count].element);
    printf("Bitmap Index : %d\n", occurences.founds[count].index);
    printf("Adress : %p\n\n", occurences.founds[count].pageRef);
    count++;
  }
}

void printAllPage(Page *first) {
  Page *current = first;
  int currentPageIndex = 0;
  while (current != NULL) {
    printf("Page %d\n\n", currentPageIndex);
    for (int i = 0; i < NB_ELEM; i++) {
      if (current->bitmap & (1 << i)) {
        printf("Elem %d : %d\n", i, current->element[i]);
      } else {
        printf("Elem %d : (vide)\n", i);
      }
    }
    printf("\n");
    current = current->next;
    currentPageIndex++;
  }
}

//////////////////////////////////////////////////////////////////////

void freeAllPages(Page *first) {
  Page *current = first;
  while (current != NULL) {
    Page *next = current->next;
    free(current);
    current = next;
  }
}
