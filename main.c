
#include <stdio.h>
#include "list/list.h"

int main() {
    Node* list = createNode(1000);
    append(&list, 2000);
    append(&list, 3000);
    printList(list);

    int value = get(list, 1)->value;
    printf("With index 1: %d\n", value);

    int listSum = sum(list);
    printf("Sum: %d\n", listSum);

    return 0;
} 