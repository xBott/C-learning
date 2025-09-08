#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* createNode(int value);

void append(Node** head, int value);

Node* get(Node* head, int index);

int size(Node* head);

int sum(Node* head);

void printList(Node* head);

#endif
