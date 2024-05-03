#include "log.h"

void logMessage(int logLevel, const char* format, ...) {
    FILE* logFile = fopen(LOG_FILE_NAME, "a");
    if(logFile == NULL) {
        return;
    }

    va_list args;
    va_start(args, format);

    const time_t loggingDateTime = time(NULL);
    char loggingDateTimeString[MAX_BUFFER_LENGTH];
    strftime(loggingDateTimeString, MAX_BUFFER_LENGTH, "%d.%m.%Y %H:%M:%S ", localtime(&loggingDateTime));

    fprintf(logFile, "[%s] ", loggingDateTimeString);

    switch (logLevel) {
        case FATAL_: {
            fprintf(logFile, "FATAL: ");
            break;
        }
        case ERROR_: {
            fprintf(logFile, "ERROR: ");
            break;
        }
        case INFO_: {
            fprintf(logFile, "INFO: ");
            break;
        }
        default: {
            fprintf(logFile, "UNKNOWN LOG LEVEL: ");
            break;
        }
    }

    vfprintf(logFile, format, args);
    fprintf(logFile, "\n");
    
    va_end(args);  
    fclose(logFile); 
}
