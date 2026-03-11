#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_CAPACITY 8
#define INIT_VALUE -1

typedef struct Page Page;

struct Page {
  int value[PAGE_CAPACITY];
  uint8_t bitmap;
  Page *next;
};

typedef struct UnrolledList {
  int pageCapacity;
  int itemCount;
  int pageCount;
  Page *head;
} UnrolledList;

typedef struct ElementLocation {
  int value;
  uint8_t index;
  Page *pageRef;
} ElementLocation;

typedef struct SearchResult {
  ElementLocation *founds;
  int number;
} SearchResult;

//////////////////////////////////////////////////////////////////////

UnrolledList constructorListInit();
Page *constructorPageInit();

void insert(UnrolledList *list, int value);
void removePosition(UnrolledList *list, ElementLocation position);
void compact(UnrolledList *list);

SearchResult research(UnrolledList *list, int value);

void printLocations(SearchResult occurrences);
void printUnrolledList(UnrolledList *list);

void freeAllPages(Page *head);

//////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  UnrolledList list = constructorListInit();

  for (int i = 0; i < 7; i++) {
    insert(&list, rand() % 15);
  }

  SearchResult occ = research(&list, 5);

  printUnrolledList(&list);

  for (int i = 0; i < occ.number; i++) {
    removePosition(&list, occ.founds[i]);
  }

  free(occ.founds);

  printUnrolledList(&list);

  compact(&list);
  printUnrolledList(&list);

  freeAllPages(list.head);

  printf("\n\n");
  return 0;
}

//////////////////////////////////////////////////////////////////////

UnrolledList constructorListInit() {
  UnrolledList tmpList;
  tmpList.head = constructorPageInit();
  tmpList.itemCount = 0;
  tmpList.pageCount = 1;
  tmpList.pageCapacity = PAGE_CAPACITY;

  return tmpList;
}

Page *constructorPageInit() {
  Page *tmpPage = malloc(sizeof(Page));

  tmpPage->bitmap = 0;
  for (int i = 0; i < PAGE_CAPACITY; i++) {
    tmpPage->value[i] = INIT_VALUE;
  }
  tmpPage->next = NULL;

  return tmpPage;
}

//////////////////////////////////////////////////////////////////////

void insert(UnrolledList *list, int value) {
  if (list->head == NULL) {
    list->head = constructorPageInit();
    list->pageCount++;
  }

  Page *current = list->head;

  while (current != NULL) {
    for (int i = 0; i < PAGE_CAPACITY; i++) {
      if (!(current->bitmap & (1 << i))) {
        current->value[i] = value;
        current->bitmap |= (1 << i);
        list->itemCount++;
        return;
      }
    }
    if (current->next == NULL) {
      current->next = constructorPageInit();
      list->pageCount++;
    }
    current = current->next;
  }
}

void removePosition(UnrolledList *list, ElementLocation position) {
  if (list->head == NULL) {
    printf("Error : \"head\" pointer is NULL");
    return;
  }

  position.pageRef->value[position.index] = 0;
  position.pageRef->bitmap &= ~(1 << position.index);
  list->itemCount--;
}

SearchResult research(UnrolledList *list, int value) {
  SearchResult occurrences;
  occurrences.founds = NULL;
  occurrences.number = 0;

  if (list->head == NULL) {
    printf("Error : \"head\" pointer is NULL");
    return occurrences;
  }

  ElementLocation *founds = NULL;
  Page *current = list->head;
  int count = 0;

  while (current != NULL) {
    for (int i = 0; i < PAGE_CAPACITY; i++) {
      if (current->bitmap & (1 << i)) {
        if (current->value[i] == value) {
          count++;
          if (founds == NULL) {
            founds = malloc(sizeof(ElementLocation));
          } else {
            founds = realloc(founds, count * sizeof(ElementLocation));
          }

          ElementLocation tmp = {.value = value, .index = i, .pageRef = current};
          founds[count - 1] = tmp;
        }
      }
    }
    current = current->next;
  }

  if (count == 0) {
    printf("Alert : Value (%d) not found\n\n", value);
    return occurrences;
  }

  occurrences.founds = founds;
  occurrences.number = count;

  return occurrences;
}

void compact(UnrolledList *list) {
  if (list->head == NULL) {
    printf("Error : \"head\" pointer is NULL");

    return;
  }

  Page *current = list->head;
  int moved;
  do {
    moved = 0;
    int isRefFound = 0;
    current = list->head;
    ElementLocation refHoleFound;

    while (current != NULL) {
      for (int i = 0; i < PAGE_CAPACITY; i++) {
        if (!(current->bitmap & (1 << i))) {
          if (!isRefFound) {
            refHoleFound.pageRef = current;
            refHoleFound.index = i;
            isRefFound = 1;
          }
        } else if (isRefFound) {
          refHoleFound.pageRef->value[refHoleFound.index] = current->value[i];
          refHoleFound.pageRef->bitmap |= (1 << refHoleFound.index);

          current->value[i] = 0;
          current->bitmap &= ~(1 << i);

          refHoleFound.index = i;
          refHoleFound.pageRef = current;
          moved = 1;
        }
      }
      current = current->next;
    }
  } while (moved);

  Page *previous = NULL;
  current = list->head;

  while (current != NULL) {
    if (current->bitmap == 0) {
      Page *next = current->next;

      if (previous == NULL) {
        list->head = next;
      } else {
        previous->next = next;
      }

      free(current);
      list->pageCount--;
      current = next;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

//////////////////////////////////////////////////////////////////////

void printLocations(SearchResult occurrences) {
  int count = 0;
  printf("Position found :\n\n");
  for (int i = 0; i < occurrences.number; i++) {
    printf("Value : %d\n", occurrences.founds[count].value);
    printf("Bitmap Index : %d\n", occurrences.founds[count].index);
    printf("Adress : %p\n\n", occurrences.founds[count].pageRef);
    count++;
  }
}

void printUnrolledList(UnrolledList *list) {
  Page *current = list->head;
  int currentPageIndex = 0;
  while (current != NULL) {
    printf("Page %d\n\n", currentPageIndex);
    for (int i = 0; i < PAGE_CAPACITY; i++) {
      if (current->bitmap & (1 << i)) {
        printf("Value %d : %d\n", i, current->value[i]);
      } else {
        printf("Value %d : (empty)\n", i);
      }
    }
    printf("\n");
    current = current->next;
    currentPageIndex++;
  }
}

//////////////////////////////////////////////////////////////////////

void freeAllPages(Page *head) {
  Page *current = head;
  while (current != NULL) {
    Page *next = current->next;
    free(current);
    current = next;
  }
}
