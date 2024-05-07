#include "hash_table/hashTable.h"
#include "options/options.h"
#include "file_system/fileSystem.h"

#define HASH_TABLE_CAPACITY     (389)
/*  Recommended capacity to minimize collision
    5, 11, 23, 47, 97, 193, 389, 769,
    1543, 3072, 3079,
    12289, 24593, 49157, 98317,
    196613, 393241, 786433,
    1572869, 3145739, 6291469, 
    12582917, 25165843, 50331653,
    100663319, 201326611, 402653189, 805306457,
    1610612736, 2147483629
*/

size_t scannedFilesCounter = 0;
size_t createdHardLinksCounter = 0;

int main(int argc, char** argv) {
    
    Options* options = processCmdArguments(argc, argv);
    if(options == NULL) {
        return -1;
    }

    if(options->help == ENABLE_) {
        displayHelp();
        optionsDestructor(options);
        return 0;
    }

    HashTable* hashTable = HTConstructor(HASH_TABLE_CAPACITY);
    if(hashTable == NULL) {
        optionsDestructor(options);
        return -1;
    }

    processDirectory(hashTable, options);

    optionsDestructor(options);
    HTDestructor(hashTable);

    printf("Files scanned: %d\n", scannedFilesCounter);
    printf("Duplicates deleted: %d\n", createdHardLinksCounter);

    return 0;
}