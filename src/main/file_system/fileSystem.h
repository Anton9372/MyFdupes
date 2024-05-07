#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../options/options.h"
#include "../hash_table/hashTable.h"
#include "../hashing/controlSum.h"
#include "../logging/log.h"

#define MAX_BUFFER_LEN  (1024)

extern size_t scannedFilesCounter;

void processDirectory(HashTable* hashTable, const Options* options);
void processFile(HashTable* hashTable, const char* pathToFile, int deleteEmptyFiles, int forceReplace);

#endif