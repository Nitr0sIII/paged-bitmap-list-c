#include "./include/listManagementNormal.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  // Create the list and ask the user for the page capacity.
  UnrolledList list = constructorListInit();

  // Fill the list with random values to demonstrate insertion.
  for (int i = 0; i < 15; i++) {
    insert(&list, rand() % 15);
  }

  printUnrolledList(&list);

  // Search all occurrences of 9, then remove them from the list.
  SearchResult occ = research(&list, 9);
  for (int i = 0; i < occ.number; i++) {
    removeAtLocation(&list, occ.founds[i]);
  }
  free(occ.founds);

  printUnrolledList(&list);

  // Compact the pages to eliminate holes left by deletions.
  compact(&list);

  printUnrolledList(&list);

  // Release every allocated page before exiting.
  freeAllPages(list.head);
  printf("\n\n");
}