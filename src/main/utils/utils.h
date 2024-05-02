#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "../logging/log.h"

const char* HARD_LINK_CREATE_SUCCESS = "Hard link created succesfuly: ";
const char* HARD_LINK_CREATE_ERROR = "Error while creating hard link: ";
const char* FILE_DOES_NOT_EXIST_ERROR = "File does not exist: ";
const char* FILE_DELETING_SUCCESS = "File deleted succesfully: ";
const char* FILE_DELETING_ERROR = "Error deleting file: ";
const char* FILE_IS_NOT_A_REGULAR_FILE_ERROR = "File is not a regular file and cannot be deleted: ";

void createHardLink(const char* pathToFile, const char* pathToLink);
void deleteFile(const char* filePath);



#endif
