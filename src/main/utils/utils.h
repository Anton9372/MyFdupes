#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "../logging/log.h"
#include "../options/options.h"

#define HARD_LINK_CREATE_SUCCESS "Hard link created succesfuly: "
#define HARD_LINK_CREATE_ERROR "Error while creating hard link: "
#define FILE_DOES_NOT_EXIST_ERROR "File does not exist: "
#define FILE_DELETING_SUCCESS "File deleted succesfully: "
#define FILE_DELETING_ERROR "Error deleting file: "
#define FILE_IS_NOT_A_REGULAR_FILE_ERROR "File is not a regular file and cannot be deleted: "

void createHardLink(const char* pathToFile, const char* pathToLink);
void deleteFile(const char* filePath);
void replaceFileWithHardLink(const char* pathToFile, const char* pathToFileDuplicate, int forceReplace);

#endif
