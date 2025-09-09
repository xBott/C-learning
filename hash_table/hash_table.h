#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** bukkets;
    int size;
    int count;
} HashTable;

HashTable* hashTableCreate(int size);

void hashTableInsert(HashTable* table, char* key, char* value);

void hashTableDelete(HashTable* table, char* key);

char* hashTableGetOrDefault(HashTable* table, char* key, char* def);

size_t hashTableMemoryUsage(HashTable* table);

#endif
