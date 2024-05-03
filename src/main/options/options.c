#include "options.h"

Options* optionsConstructor() {
    Options* options = (Options*)malloc(sizeof(Options));
    if(options == NULL) {
        return NULL;
    }

    options->directoryPath = ".";

    options->recurceIntoDirectory = DISABLE_;
    options->forceReplace = DISABLE_;
    options->deleteEmptyFiles = DISABLE_;
    options->help = DISABLE_;

    return options;
}

Options* optionsCopyConstructor(const Options* srcOptions) {
    Options* options = (Options*)malloc(sizeof(Options));
    if(options == NULL) {
        return NULL;
    }

    options->directoryPath = srcOptions->directoryPath;

    options->recurceIntoDirectory = srcOptions->recurceIntoDirectory;
    options->forceReplace = srcOptions->forceReplace;
    options->deleteEmptyFiles = srcOptions->deleteEmptyFiles;
    options->help = srcOptions->help;

    return options;
}

void optionsDestructor(Options* options) {
    if(options != NULL) {
        free(options);
    }
}

Options* processCmdArguments(int argc, char** argv) {
    Options* options = optionsConstructor();
    if(options == NULL) {
        return NULL;
    }

    int opt;
    while((opt = getopt(argc, argv, "rfeh")) != -1) {
        switch(opt) {
            case 'r': {
                options->recurceIntoDirectory = ENABLE_;
                break;
            }
            case 'f': {
                options->forceReplace = ENABLE_;
                break;
            }
            case 'e': {
                options->deleteEmptyFiles = ENABLE_;
                break;
            }
            case 'h': {
                options->help = ENABLE_;
                break;
            }
            default: {
                fprintf(stderr, "Usage: %s [options] [directoryPath]\n", argv[0]);
                fprintf(stderr, "   options: -r, -f, -e, -h\n");
                exit(-2);
            }
        }
    }

    if(optind < argc) {
        options->directoryPath = argv[optind];
    }

    return options;
}

void displayHelp() {
    printf("%s\n", " |");
    printf("%s\n", " | MyFdupes: searches for duplicate files in a directory and changes them to hard links");
    printf("%s\n", " |");
    printf("%s\n", " | Usage:");
    printf("%s\n", " |   ./study/MyFdupes/MyFdupes [options] /path/to/directory");
    printf("%s\n", " | [options]:");
    printf("%s\n", " |   -r, recurce into directories");
    printf("%s\n", " |   -f, force replacing (normally programm asks for authorization to replace)");
    printf("%s\n", " |   -e, delete empty files");
    printf("%s\n", " |   -h, shows this info");
    printf("%s\n", " |");
}
