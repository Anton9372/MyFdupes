#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../hashing/sha256.h"

#define KEY_LENGTH	(32)

typedef struct HTNode {
	char* value;
	uint8_t* key;
	struct HTNode* next;
} HTNode;

typedef struct HashTable {
	size_t capacity;
	size_t size;
	HTNode** table;
} HashTable;

HTNode* HTNodeConstructor(const uint8_t* key, const char* value);
HashTable* HTConstructor(const size_t capacity);
size_t getIndex(const uint8_t* hash, const size_t HTCapacity);
void* HTInsert(HashTable* hashTable, const uint8_t* key, const char* value);
void* HTRemove(HashTable* hashTable, const uint8_t* key);
void* HTGet(const HashTable* hashTable, const uint8_t* key);
void HTNodeDestructor(HTNode* node);
void HTDestructor(HashTable* hashTable);

#endif