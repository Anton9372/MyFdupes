#include "fileSystem.h"

void processDirectory(HashTable* hashTable, const Options* options) {
    if(hashTable == NULL || options == NULL) {
        return;
    }

    DIR* directory = opendir(options->directoryPath);
    if(directory == NULL) {
        logMessage(ERROR_, "Error opening directory: %s\n", options->directoryPath);
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

        snprintf(entryPath, MAX_BUFFER_LEN, "%s/%s", options->directoryPath, dirEntry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode) && (options->recurceIntoDirectory == ENABLE_)) {
            Options* subDirOptions = optionsCopyConstructor(options);
            if(subDirOptions == NULL) {
                free(entryPath);
                continue;
            }

            subDirOptions->directoryPath = entryPath;
            processDirectory(hashTable, subDirOptions);
            optionsDestructor(subDirOptions);
        } else if (S_ISREG(st.st_mode)) {
            processFile(hashTable, entryPath, options->deleteEmptyFiles, options->forceReplace);
        }

        free(entryPath);
    }

    closedir(directory);
}

void processFile(HashTable* hashTable, const char* pathToFile, int deleteEmptyFiles, int forceReplace) {
    FILE* file = fopen(pathToFile, "r");
    if(file == NULL) {
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(fileSize == 0) {
        if(deleteEmptyFiles == DISABLE_) {
            logMessage(INFO_, "File was skipped because empty: %s\n", pathToFile);
        } else {
            deleteFile(pathToFile);
            logMessage(INFO_, "File was deleted because empty: %s\n", pathToFile);
        }
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
    HTInsert(hashTable, fileHash, pathToFile, forceReplace);

    controlSumDestructor(controlSum);
    free(buffer);

    fclose(file);
}