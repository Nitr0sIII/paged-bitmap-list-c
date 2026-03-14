#include "./include/listManagementDynamic.h"

INIT_LIST(int)
INIT_LIST(float)
INIT_LIST(char)

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int a;

  // Build one typed list for each supported data type.
  UnrolledList_int listInt = constructorListInit_int();
  UnrolledList_char listChar = constructorListInit_char();
  UnrolledList_float listFloat = constructorListInit_float();

  // Insert random values to populate the three examples.
  for (int i = 0; i < 7; i++) {
    insert_int(&listInt, rand() % 11);
    insert_char(&listChar, (rand() % 10) + 65);
    insert_float(&listFloat, (float)(rand() % 10) / (float)((rand() % 9) + 1));
  }

  //////////////////////////////////////////////////////////////////////

  printUnrolledList_int(&listInt);

  // Remove every matching occurrence, then compact the list.
  SearchResult_int occInt = research_int(&listInt, 9);
  for (int i = 0; i < occInt.number; i++) {
    removeAtLocation_int(&listInt, occInt.founds[i]);
  }

  free(occInt.founds);
  printf("Removed occ in List: \n");

  printUnrolledList_int(&listInt);

  compact_int(&listInt);
  printf("Compacted List: \n");
  printUnrolledList_int(&listInt);

  freeAllPages_int(listInt.head);

  printf("-----------------------------\n\n");

  //////////////////////////////////////////////////////////////////////

  printUnrolledList_char(&listChar);

  // Repeat the same workflow on the char-based list.
  SearchResult_char occChar = research_char(&listChar, 68);
  for (int i = 0; i < occChar.number; i++) {
    removeAtLocation_char(&listChar, occChar.founds[i]);
  }

  free(occChar.founds);
  printf("Removed occ in List: \n");

  printUnrolledList_char(&listChar);

  compact_char(&listChar);
  printf("Compacted List: \n");
  printUnrolledList_char(&listChar);

  freeAllPages_char(listChar.head);

  printf("-----------------------------\n\n");

  //////////////////////////////////////////////////////////////////////

  printUnrolledList_float(&listFloat);

  // Same demonstration again for the float-based list.
  SearchResult_float occFloat = research_float(&listFloat, 9.1);
  for (int i = 0; i < occFloat.number; i++) {
    removeAtLocation_float(&listFloat, occFloat.founds[i]);
  }

  free(occFloat.founds);
  printf("Removed occ in List: \n");
  printUnrolledList_float(&listFloat);

  compact_float(&listFloat);
  printf("Compacted List: \n");
  printUnrolledList_float(&listFloat);

  freeAllPages_float(listFloat.head);

  printf("-----------------------------\n\n");
}