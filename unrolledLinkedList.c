#include "./include/listManagement.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  UnrolledList list = constructorListInit();

  insert(&list, 4 /*rand() % 15*/);

  for (int i = 0; i < 5; i++) {
    insert(&list, 9 /*rand() % 15*/);
  }

  SearchResult occ = research(&list, 9);

  printUnrolledList(&list);
  /*
    for (int i = 0; i < occ.number; i++) {
      removePosition(&list, occ.founds[i]);
    }

    free(occ.founds);

    printUnrolledList(&list);

    compact(&list);
    printUnrolledList(&list);*/

  freeAllPages(list.head);

  printf("\n\n");
  return 0;
}