#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Node* createNode(int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int value) {
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node* get(Node* head, int index) {
    Node* temp = head;
    int step = 0;
    while (step < index) {
        step++;
        temp = temp->next;
    }
    return temp;
}

int size(Node* node) {
    int count = 0;
    Node* temp = node;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

int sum(Node* head) {

    int result = 0;
    int length = size(head);

    for (int i = 0; i < length; i++) {
        Node* node = get(head, i);
        int value = node->value;
        result+=value;
    }

    return result;

}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}
