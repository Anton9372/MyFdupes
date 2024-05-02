#include "utils.h"

void createHardLink(const char* pathToFile, const char* pathToLink) {
    struct stat st;
    if(stat(pathToFile, &st) != 0) {
        logMessage(FATAL_, "%s%s%s\n", HARD_LINK_CREATE_ERROR, FILE_DOES_NOT_EXIST_ERROR, pathToFile);
        return;
    }

    if (link(pathToFile, pathToLink) == 0) {
        logMessage(INFO_, "%s%s --> %s\n", HARD_LINK_CREATE_SUCCESS, pathToLink, pathToFile);
    } else {
        logMessage(ERROR_, "%s%s", HARD_LINK_CREATE_ERROR, strerror(errno));
    }
}

void deleteFile(const char* filePath) {
    struct stat st;
    if(stat(filePath, &st) != 0) {
        logMessage(FATAL_, "%s%s\n",FILE_DOES_NOT_EXIST_ERROR, filePath);
        return;
    }

    if (!S_ISREG(st.st_mode)) {
        logMessage(ERROR_, "%s%s\n", FILE_IS_NOT_A_REGULAR_FILE_ERROR ,filePath);
        return;
    }

    if (remove(filePath) == 0) {
        logMessage(INFO_, "%s%s\n", FILE_DELETING_SUCCESS, filePath);
    } else {
        logMessage(ERROR_, "%s%s: %s\n", FILE_DELETING_ERROR, filePath, strerror(errno));
    }
}

