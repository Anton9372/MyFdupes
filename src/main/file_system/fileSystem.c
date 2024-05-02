#include "fileSystem.h"

void processDirectory(HashTable* hashTable, const char* pathToDirectory) {
    if(hashTable == NULL) {
        return;
    }

    DIR* directory = opendir(pathToDirectory);
    if(directory == NULL) {
        return;
    }

    struct dirent* dirEntry;
    while((dirEntry = readdir(directory)) != NULL) {
        if(strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0) {
            continue;   
        }

        char* entryPath = (char*)malloc(MAX_BUFFER_LEN * sizeof(char));
        if(entryPath == NULL) {
            return;
        }

        snprintf(entryPath, strlen(entryPath), "%s/%s", pathToDirectory, dirEntry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            processDirectory(hashTable, entryPath);
        } else if (S_ISREG(st.st_mode)) {
            
        }
    }

    closedir(directory);
}

void processFile(HashTable* hashTable, const char* pathToFile) {
    FILE* file = fopen(pathToFile, "r");
    if(file == NULL) {
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(fileSize == 0) {
        logMessage(INFO_, "File was skipped because empty: %s\n", pathToFile);
        return;
    }

    char* buffer = (char*)malloc(MAX_BUFFER_LEN * sizeof(char));
    if(buffer == NULL) {
        return;
    }

    ControlSum* controlSum = controlSumContructor();

    while(fread(buffer, sizeof(char), sizeof(buffer), file)) {
        addBufferHash(controlSum, buffer);

    }

    uint8_t* fileHash = getControlSum(controlSum);
    HTInsert(hashTable, fileHash, pathToFile);

    controlSumDestructor(controlSum);
    free(buffer);

    fclose(file);
}