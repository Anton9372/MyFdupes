#ifndef CONTROLSUM_H_
#define CONTROLSUM_H_

#include <stdlib.h>
#include <string.h>
#include "sha256.h"

typedef struct ControlSum {
    uint8_t* sum;
    size_t length;
} ControlSum;

ControlSum* controlSumContructor();
void* addBufferHash(ControlSum* block, const char* buffer);
uint8_t* getControlSum(ControlSum* block);
void controlSumDestructor(ControlSum* block);

#endif
