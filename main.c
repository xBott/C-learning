
#include <stdio.h>
#include <stdlib.h>

#include "list/list.h"
#include "hash_table/hash_table.h"


void testLists() {
    Node* list = createNode(1000);
    append(&list, 2000);
    append(&list, 3000);
    printList(list);

    int value = get(list, 1)->value;
    printf("With index 1: %d\n", value);

    int listSum = sum(list);
    printf("Sum: %d\n", listSum);

    free(list);
}

void testHashTablesWithLoop() {
    HashTable* table = hashTableCreate(1);

    printf("Initial Memory usage: %zu\n", hashTableMemoryUsage(table));

    for (int i = 0; i < 100; i++) {
        char key[10];
        snprintf(key, sizeof(key), "%d", i);

        char value[2];
        value[0] = (char)i;
        value[1] = '\0';

        hashTableInsert(table, key, value);

        printf("Memory usage after insertion: %zu\n", hashTableMemoryUsage(table));
    }

    for (int i = 0; i < 100; i++) {
        char key[10];
        snprintf(key, sizeof(key), "%d", i);
        printf("Key: %s | Value: %s\n", key, hashTableGetOrDefault(table, key, "?"));
    }

    for (int i = 0; i < 100; i++) {
        char key[10];
        snprintf(key, sizeof(key), "%d", i);

        hashTableDelete(table, key);
        printf("Memory usage after deletion: %zu\n", hashTableMemoryUsage(table));
    }

    printf("Final Memory usage: %zu\n", hashTableMemoryUsage(table));

}


void testHashTables() {
    HashTable* table = hashTableCreate(1);

    printf("Inserting elements to the table...\n");
    printf("Initial Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    hashTableInsert(table, "age", "10");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    hashTableInsert(table, "name", "Roman");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    hashTableInsert(table, "test", "Test");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    printf("Retrieving elements from the table...\n");
    printf("Element age: %s\n", hashTableGetOrDefault(table, "age", "0"));
    printf("Element name: %s\n", hashTableGetOrDefault(table, "name", "No Name"));
    printf("Element test: %s\n", hashTableGetOrDefault(table, "test", "null"));

    printf("Deleting elements from the table...\n");

    hashTableDelete(table, "age");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    hashTableDelete(table, "name");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    hashTableDelete(table, "test");
    printf("Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    printf("Final Table memory usage is %zu bytes\n", hashTableMemoryUsage(table));

    printf("Retrieving elements from the table when table is empty...\n");
    printf("Element age: %s\n", hashTableGetOrDefault(table, "age", "0"));
    printf("Element name: %s\n", hashTableGetOrDefault(table, "name", "No Name"));
    printf("Element test: %s\n", hashTableGetOrDefault(table, "test", "null"));

    free(table);
}

int main() {
    
    testLists();
    testHashTables();
    testHashTablesWithLoop();

    return 0;
} 