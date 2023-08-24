#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

List *createList() {
  List *newList = (List *)malloc(sizeof(List));
  if (newList) {
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
  }
  return newList;
}

void *firstList(List *list) {
  if (list && list->head) {
    list->current = list->head;
    return list->current->data;
  }
  return NULL;
}

void *nextList(List *list) {
  if (list && list->current && list->current->next) {
    list->current = list->current->next;
    return list->current->data;
  }
  return NULL;
}

void *lastList(List *list) {
  if (list && list->tail) {
    list->current = list->tail;
    return list->current->data;
  }
  return NULL;
}

void *prevList(List *list) {
  if (list && list->current && list->current->prev) {
    list->current = list->current->prev;
    return list->current->data;
  }
  return NULL;
}

void pushFront(List *list, void *data) {
  if (list) {
    Node *newNode = createNode(data);
    if (newNode) {
      if (list->head) {
        newNode->next = list->head;
        list->head->prev = newNode;
      } else {
        list->tail = newNode;
      }
      list->head = newNode;
    }
  }
}

void pushCurrent(List *list, void *data) {
  if (list && list->current) {
    Node *newNode = createNode(data);
    if (newNode) {
      newNode->next = list->current->next;
      newNode->prev = list->current;
      if (list->current->next) {
        list->current->next->prev = newNode;
      }
      list->current->next = newNode;
    }
  }
}

void *popCurrent(List *list) {
  if (list && list->current) {
    Node *toRemove = list->current;
    void *data = toRemove->data;

    if (toRemove->prev) {
      toRemove->prev->next = toRemove->next;
    } else {
      list->head = toRemove->next;
    }

    if (toRemove->next) {
      toRemove->next->prev = toRemove->prev;
    } else {
      list->tail = toRemove->prev;
    }

    if (toRemove->next) {
      list->current = toRemove->next;
    } else if (toRemove->prev) {
      list->current = toRemove->prev;
    } else {
      list->current = NULL;
    }

    free(toRemove);
    return data;
  }
  return NULL;
}

int main() {
  List *myList = createList();

  int a = 10, b = 20, c = 30;

  pushFront(myList, &a);
  pushFront(myList, &b);
  pushFront(myList, &c);

  printf("Data at current: %d\n", *(int *)firstList(myList));
  printf("Data at next: %d\n", *(int *)nextList(myList));

  pushCurrent(myList, &a);
  printf("Data at next after push: %d\n", *(int *)nextList(myList));

  int *poppedData = (int *)popCurrent(myList);
  if (poppedData) {
    printf("Popped data: %d\n", *poppedData);
    free(poppedData);
  }

  return 0;
}


void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}