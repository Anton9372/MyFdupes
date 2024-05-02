#include <stdio.h>
#include "../../main/hashing/controlSum.h"

#define MAX_NUM_STRINGS	(100)

const char* buffer[][MAX_NUM_STRINGS] = {
	{ "" },
	{ " "},
	{ "Hello" },
	{ "Hello" },
	{ "Hello", " World" },
	{ "Hello", " World" },
	{ "The quick ", "brown fox jumps ", "over the lazy dog" },
	{ "The quick ", "brown fox jumps ", "over the lazy dog" },
	{ "The ", "quick ", "brown ", "fox ", "jumps ", "over ", "the ", "lazy ", "dog" },
	{ "The quick brown fox jumps over the lazy cog" },
	{ "The quick brown fox jumps over the lazy cog" }
};

const size_t numOfStrings[] = {
	1, 1, 1, 1, 2, 2, 3, 3, 9, 1, 1
};

uint8_t* test(const char** buffer, const size_t numOfStrings) {
	ControlSum* block = controlSumContructor();

	for (size_t i = 0; i < numOfStrings; i++) {
		addBufferHash(block, buffer[i]);
	}

	uint8_t* result = getControlSum(block);
	controlSumDestructor(block);

	return result;
}

int main() {
	size_t numOfTests = sizeof(numOfStrings) / sizeof(numOfStrings[0]);

	for (size_t i = 0; i < numOfTests; i++) {
		printf("Test %d: ", i);

		for (size_t j = 0; j < numOfStrings[i]; j++) {
			printf("%s", buffer[i][j]);
		}
		printf("\n");
		
		uint8_t* result = test(buffer[i], numOfStrings[i]);

		for (size_t i = 0; i < SHA256_SIZE_BYTES; i++) {
			printf("%02x", result[i]);
		}
		printf("\n");
	}
	
	return 0;
}