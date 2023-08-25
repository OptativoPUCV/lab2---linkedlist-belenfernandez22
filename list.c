#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef struct List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List * createList() {
    List * newList = (List *)malloc(sizeof(List));
    if (newList == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for List.\n");
        exit(EXIT_FAILURE);
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;

    return newList;
}
