#ifndef LIST_H
#define LIST_H

typedef struct Node {
  void* item;
  struct Node* next;
  struct Node* prev;
} Node;

typedef struct LinkedList {
  Node* first;
  Node* last;
} LinkedList;

Node* Node_new();
void Node_destroy(Node* node);

LinkedList* LinkedList_new();
void LinkedList_destroy(LinkedList* list);

void LinkedList_remove(LinkedList* list, Node* node);
void LinkedList_delete(LinkedList* list, Node* node);
void LinkedList_clear(LinkedList* list);
void LinkedList_addLast(LinkedList* list, void* item);

#endif
