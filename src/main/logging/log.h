#ifndef LOG_H_
#define LOG_H_  

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define MAX_BUFFER_LENGTH   (1024)

const char* logFileName = "/home/anton/study/MyFdupes/log.txt";

enum LOG_LEVEL {
    FATAL_ = 0,
    ERROR_ = 1,
    INFO_ = 2
};

void logMessage(int logLevel, const char* format, ...);

#endif