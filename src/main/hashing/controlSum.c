#include "controlSum.h"

ControlSum* controlSumContructor() {
	ControlSum* temp = (ControlSum*)malloc(sizeof(ControlSum));
	if (temp == NULL) {
		return NULL;
	}

	temp->sum = NULL;
	temp->length = 0;

	return temp;
}	

void* addBufferHash(ControlSum* block, const char* buffer) {
	if (block == NULL || buffer == NULL) {
		return NULL;
	}

	uint8_t hash[SHA256_SIZE_BYTES];
	sha256(buffer, strlen(buffer), hash);

	block->length += SHA256_SIZE_BYTES;

	block->sum = (uint8_t*)realloc(block->sum, block->length * sizeof(uint8_t));
	if (block->sum == NULL) {
		return NULL;
	}

	memcpy(block->sum + (block->length - SHA256_SIZE_BYTES), hash, SHA256_SIZE_BYTES);

	return block->sum;
}

uint8_t* getControlSum(ControlSum* block) {
	if (block == NULL) {
		return NULL;
	}

	uint8_t* hash = (uint8_t*)malloc(SHA256_SIZE_BYTES * sizeof(uint8_t));
	if (hash == NULL) {
		return NULL;
	}

	sha256(block->sum, block->length, hash);

	return hash;
}

void controlSumDestructor(ControlSum* block) {
	if (block->sum != NULL) {
		free(block->sum);
	}
	if (block != NULL) {
		free(block);
	}
}
