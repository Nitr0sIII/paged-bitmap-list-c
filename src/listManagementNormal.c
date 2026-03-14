#include "../include/listManagementNormal.h"
#include "../include/colorConsole.h"

UnrolledList constructorListInit() {
  UnrolledList tmpList;

  tmpList.itemCount = 0;
  tmpList.pageCount = 0;
  tmpList.pageCapacity = askPageCapacity();
  tmpList.head = constructorPageInit(tmpList.pageCapacity);

  return tmpList;
}

Page *constructorPageInit(int numByPage) {
  Page *tmpPage = malloc(sizeof(Page));

  // Allocate storage for the values contained in the page.
  tmpPage->values = malloc(sizeof(int) * numByPage);
  tmpPage->bitmap = 0;

  // Mark every slot as empty at startup.
  for (int i = 0; i < numByPage; i++) {
    tmpPage->values[i] = INIT_VALUE;
  }

  tmpPage->next = NULL;

  return tmpPage;
}

int askPageCapacity() {
  int num = 0;
  do {
    printf("\nChoose the number of elements in a page (1-8): ");
    scanf("%d", &num);
  } while (num <= 0 || num > 8);

  return num;
}

//////////////////////////////////////////////////////////////////////

void insert(UnrolledList *list, int value) {
  // Create the first page if the list is still empty.
  if (list->head == NULL) {
    list->head = constructorPageInit(list->pageCapacity);
    if (list->head == NULL) {
      return;
    }
    list->pageCount++;
  }

  Page *current = list->head;

  // Scan pages until a free slot is found.
  while (current != NULL) {
    for (int i = 0; i < list->pageCapacity; i++) {
      if (!(current->bitmap & (1 << i))) {
        current->values[i] = value;
        current->bitmap |= (1 << i);
        list->itemCount++;
        return;
      }
    }
    if (current->next == NULL) {
      // Add page when all current pages are full.
      current->next = constructorPageInit(list->pageCapacity);
      if (current->next == NULL) {
        return;
      }
      list->pageCount++;
    }
    current = current->next;
  }
}

void removeAtLocation(UnrolledList *list, ElementLocation position) {
  if (list->head == NULL) {
    printf("Error : \"head\" pointer is NULL");
    return;
  }

  // Clear the slot and update the bitmap.
  position.pageRef->values[position.index] = INIT_VALUE;
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

  // Walk through every occupied slot and keep matching positions.
  while (current != NULL) {
    for (int i = 0; i < list->pageCapacity; i++) {
      if (current->bitmap & (1 << i)) {
        if (current->values[i] == value) {
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
    printf("Alert : values (%d) not found\n\n", value);
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

    // Push values leftward into the first hole encountered.
    while (current != NULL) {
      for (int i = 0; i < list->pageCapacity; i++) {
        if (!(current->bitmap & (1 << i))) {
          if (!isRefFound) {
            refHoleFound.pageRef = current;
            refHoleFound.index = i;
            isRefFound = 1;
          }
        } else if (isRefFound) {
          refHoleFound.pageRef->values[refHoleFound.index] = current->values[i];
          refHoleFound.pageRef->bitmap |= (1 << refHoleFound.index);

          current->values[i] = INIT_VALUE;
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

  // Remove pages that became completely empty after compaction.
  while (current != NULL) {
    if (current->bitmap == 0) {
      Page *next = current->next;

      if (previous == NULL) {
        list->head = next;
      } else {
        previous->next = next;
      }

      free(current->values);
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
  printf(CYN "Positions found: %d\n" RESET, occurrences.number);
  for (int i = 0; i < occurrences.number; i++) {
    printf("  " YEL "[%d]" RESET " -> page " GRN "%p\n" RESET, occurrences.founds[i].index, (void *)occurrences.founds[i].pageRef);
  }
}

void printUnrolledList(UnrolledList *list) {
  Page *current = list->head;
  int pageIndex = 0;

  printf(BLU "\nLIST: int\n" RESET);

  while (current != NULL) {
    printf(CYN "\nPage %d : " RESET, pageIndex);
    for (int i = 0; i < list->pageCapacity; i++) {
      if (current->bitmap & (1 << i)) {
        printf(GRN "1" RESET);
      } else {
        printf(RED "0" RESET);
      }
    }
    printf("\n");

    for (int i = 0; i < list->pageCapacity; i++) {
      if (current->bitmap & (1 << i)) {
        printf("  " MAG "[" RESET "%d" MAG "] " RESET, i);
        printf(GRN " %d\n" RESET, current->values[i]);
      } else {
        printf("  " MAG "[" RESET "%d" MAG "] " RED " (empty)\n" RESET, i);
      }
    }

    current = current->next;
    pageIndex++;
  }
}

//////////////////////////////////////////////////////////////////////

void freeAllPages(Page *head) {
  Page *current = head;
  // Free pages one by one from head to the end.
  while (current != NULL) {
    Page *next = current->next;
    free(current->values);
    free(current);
    current = next;
  }
}