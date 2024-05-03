#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Options {
    const char* directoryPath;

    int recurceIntoDirectory;
    int forceReplace;
    int deleteEmptyFiles;
    int help;
} Options;

enum OptionStatus {
    DISABLE_ = 0,
    ENABLE_ = 1,
};

Options* optionsConstructor();
Options* optionsCopyConstructor(const Options* srcOptions);
void optionsDestructor(Options* options);
Options* processCmdArguments(int argc, char** argv);
void displayHelp();

#endif