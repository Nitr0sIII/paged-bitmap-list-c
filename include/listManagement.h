#ifndef LIST_MANAGEMENT_H
#define LIST_MANAGEMENT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_VALUE -1

typedef struct Page Page;

struct Page {
  int *values;
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
  int index;
  Page *pageRef;
} ElementLocation;

typedef struct SearchResult {
  ElementLocation *founds;
  int number;
} SearchResult;

//////////////////////////////////////////////////////////////////////

UnrolledList constructorListInit();
Page *constructorPageInit(int pageCapacity);
int askElementsNumber();

void insert(UnrolledList *list, int value);
void removePosition(UnrolledList *list, ElementLocation position);
void compact(UnrolledList *list);

SearchResult research(UnrolledList *list, int value);

void printLocations(SearchResult occurrences);
void printUnrolledList(UnrolledList *list);

void freeAllPages(Page *head);

#endif