#include "hashTable.h"

HTNode* HTNodeConstructor(const uint8_t* key, const char* value) {
	if (key == NULL || value == NULL) {
		return NULL;
	}

	HTNode* node = (HTNode*)malloc(sizeof(HTNode));
	if (node == NULL) {
		return NULL;
	}

	size_t valueLength = strlen(value);

	node->key = (uint8_t*)malloc((KEY_LENGTH) * sizeof(uint8_t));
	if (node->key == NULL) {
		free(node);
		return NULL;
	}
	
	node->value = (char*)malloc((valueLength + 1) * sizeof(char));
	if (node->value == NULL) {
		free(node->key);
		free(node);
		return NULL;
	}

	memcpy(node->key, key, KEY_LENGTH);
	strncpy(node->value, value, valueLength);
	node->value[valueLength] = '\0';

	node->next = NULL;

	return node;
}

HashTable* HTConstructor(const size_t capacity) {
	if (capacity == 0) {
		return NULL;
	}

	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (hashTable == NULL) {
		return NULL;
	}

	hashTable->table = (HTNode**)malloc(capacity * sizeof(HTNode*));
	if (hashTable->table == NULL) {
		free(hashTable);
		return NULL;
	}

	hashTable->capacity = capacity;
	hashTable->size = 0;
	for (size_t i = 0; i < capacity; i++) {
		hashTable->table[i] = NULL;
	}

	return hashTable;
}

size_t getIndex(const uint8_t* key, const size_t HTCapacity) {
	size_t index = 0;
	for (size_t i = 0; i < KEY_LENGTH; i++) {
		index = (index << 5) - index + key[i];
	}

	return index % HTCapacity;
}

void* HTInsert(HashTable* hashTable, const uint8_t* key, const char* value, int forceReplace) {
	if (hashTable == NULL || key == NULL || value == NULL) {
		return NULL;
	}

	size_t index = getIndex(key, hashTable->capacity);
	HTNode* node = hashTable->table[index];

	for (node; node != NULL; node = node->next) {
		if (memcmp(node->key, key, KEY_LENGTH) == 0) {
			replaceFileWithHardLink(node->value, value, forceReplace);
			return node->value;
		}
	}

	node = HTNodeConstructor(key, value);
	if (node == NULL) {
		return NULL;
	}

	node->next = hashTable->table[index];
	hashTable->table[index] = node;

	hashTable->size++;
}

void* HTRemove(HashTable* hashTable, const uint8_t* key) {
	if (hashTable == NULL || key == NULL) {
		return NULL;
	}

	size_t index = getIndex(key, hashTable->capacity);
	HTNode* node = hashTable->table[index];
	HTNode* prev = NULL;

	for (node; node != NULL; node = node->next) {
		if (memcmp(node->key, key, KEY_LENGTH) == 0) {
			char* temp = node->value;

			if (prev != NULL) {
				prev->next = node->next;
			}
			else {
				hashTable->table[index] = node->next;
			}

			free(node);
			hashTable->size--;
			return temp;
		}
		prev = node;
	}
	return NULL;
}

void* HTGet(const HashTable* hashTable, const uint8_t* key) {
	if (hashTable == NULL || key == NULL) {
		return NULL;
	}

	size_t index = getIndex(key, hashTable->capacity);
	HTNode* node = hashTable->table[index];

	for (node; node != NULL; node = node->next) {
		if (memcmp(node->key, key, KEY_LENGTH) == 0) {
			return node->value;
		}
	}

	return NULL;
}

void HTNodeDestructor(HTNode* node) {
	if (node != NULL) {
		free(node->key);
		free(node->value);
		free(node);
	}
}

void HTDestructor(HashTable* hashTable) {
	if (hashTable == NULL) {
		return;
	}

	for (size_t i = 0; i < hashTable->capacity; i++) {
		HTNode* current = hashTable->table[i];
		while (current != NULL) {
			HTNode* nextNode = current->next;
			HTNodeDestructor(current);
			current = nextNode;
		}
	}

	free(hashTable->table);
	free(hashTable);
}
