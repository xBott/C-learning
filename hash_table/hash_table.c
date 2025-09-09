#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"

unsigned int hash(const char* key, int size) {
    unsigned int value = 0;
    while (*key) {
        value = value * 31 + (unsigned char)(*key);
        key++;
    }
    return value % size;
}


HashTable* hashTableCreate(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->bukkets = calloc(size, sizeof(HashNode*));
    return table;
}

void hashTableResize(HashTable* table, int newSize) {
    HashNode** newNodes = calloc(newSize, sizeof(HashNode*));

    for (int i = 0; i < table->size; i++) {
        HashNode* node = table->bukkets[i];
        while (node != NULL) {
            HashNode* next = node->next;

            int h = hash(node->key, newSize);

            node->next = newNodes[h];
            newNodes[h] = node;

            node = next;
        }
    }

    free(table->bukkets);
    table->bukkets = newNodes;
    table->size = newSize;
}

void hashTableInsert(HashTable* table, char* key, char* value) {

    double loadFactor = (double)table->count / table->size;
    if (loadFactor > 0.75) {
        hashTableResize(table, table->size * 2);
    }

    int index = hash(key, table->size);

    HashNode* node = malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = table->bukkets[index];

    table->bukkets[index] = node;
    table->count++;

}

void hashTableDelete(HashTable* table, char* key) {

    if (table == NULL || table->bukkets == NULL) return;

    int index = hash(key, table->size);
    HashNode* node = table->bukkets[index];
    HashNode* previousNode = NULL;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {

            if (previousNode == NULL) {
                table->bukkets[index] = node->next;
            } else {
                previousNode->next = node->next;
            }

            free(node->key);
            free(node->value);
            free(node);

            table->count--;

            double loadFactor = (double)table->count / table->size;
            if (table->size > 1 && loadFactor < 0.25) {
                hashTableResize(table, table->size / 2);
            }

            return;
        }

        previousNode = node;
        node = node->next;
    }

}

char* hashTableGetOrDefault(HashTable* table, char* key, char* def) {

    if (!table || !table->bukkets) {
        return def;
    }

    int index = hash(key, table->size);

    HashNode* node = table->bukkets[index];

    if (node == NULL) {
        return def;
    }

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return def;
}

size_t hashTableMemoryUsage(HashTable* table) {
    if (!table) return 0;

    size_t total = sizeof(*table);
    if (!table->bukkets) return total;

    total += sizeof(HashNode*) * table->size;

    for (int i = 0; i < table->size; i++) {
        HashNode* node = table->bukkets[i];
        while (node) {
            total += sizeof(*node);
            total += strlen(node->key) + 1;
            total += strlen(node->value) + 1;
            node = node->next;
        }
    }

    return total;
}
