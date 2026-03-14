#include "./include/listManagementNormal.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  UnrolledList list = constructorListInit();

  for (int i = 0; i < 15; i++) {
    insert(&list, rand() % 15);
  }

  printUnrolledList(&list);

  SearchResult occ = research(&list, 9);
  for (int i = 0; i < occ.number; i++) {
    removeAtLocation(&list, occ.founds[i]);
  }
  free(occ.founds);

  printUnrolledList(&list);

  compact(&list);

  printUnrolledList(&list);

  freeAllPages(list.head);
  printf("\n\n");
}