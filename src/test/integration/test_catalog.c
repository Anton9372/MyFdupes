#include <stdio.h>

const char* files[] = {
    "/home/anton/study/MyFdupes/test_catalog/file1.txt",
    "/home/anton/study/MyFdupes/test_catalog/file2.txt",
    "/home/anton/study/MyFdupes/test_catalog/file3.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder1/file4.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder1/file5.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/file6.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/file7.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/file8.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder1/folder1/file9.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder1/file10.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder1/file11.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder3/file12.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder2/folder1/file13.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder2/folder1/file14.txt",
    "/home/anton/study/MyFdupes/test_catalog/folder2/folder2/folder1/file15.txt"
};
    
size_t numOfFiles = sizeof(files) / sizeof(files[0]);

char* data[][5] = {
    {"Hello World!"},
    {"Hello world!"},
    {"Hello World!", "My name is Anton", "1 2 3", "This is a test file", "MyFdupes"}
};

size_t deleteAllFiles() {
    size_t successCount = 0;

    for(size_t i = 0; i < numOfFiles; i++) {
        if(remove(files[i]) == 0) {
            successCount++;
        } else {
            printf("Error deleting file %s\n", files[i]);
        }
    }

    printf("Success count: %d\n", successCount);

    return successCount;
}

void writeStringsToFile(const char* filePath, char** strings, size_t numOfStrings) {
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error while opening file %s\n", filePath);
        return;
    }

    for(size_t i = 0; i < numOfStrings; i++) {
        fprintf(file, "%s\n", strings[i]);
    }

    fclose(file);
}

int main() {
    printf("create - 1, delete - 0\n");
    int option;
    scanf(" %d", &option);
    
    if(option == 0) {
        size_t deletedFiles = deleteAllFiles();
        printf("%d\n", deletedFiles && numOfFiles);
        return 0;
    }

    writeStringsToFile(files[0], data[0], 1);
    writeStringsToFile(files[1], data[1], 1);
    writeStringsToFile(files[2], data[2], 5);
    writeStringsToFile(files[3], data[0], 1);
    char* str1 = "nwnfujweifjiwefjiwjf";
    writeStringsToFile(files[4], &str1, 1);
    char* str2 = "nwnfujw47385938593845jf";
    writeStringsToFile(files[5], &str2, 1);
    writeStringsToFile(files[6], data[2], 5);
    writeStringsToFile(files[7], data[1], 1);
    writeStringsToFile(files[8], data[0], 1);
    writeStringsToFile(files[9], data[1], 1);
    char* str3 = "nwnfedededeedeujw47385938593845jf";
    writeStringsToFile(files[10], &str3, 1);
    writeStringsToFile(files[11], data[2], 5);
    writeStringsToFile(files[12], data[0], 1);
    writeStringsToFile(files[13], data[0], 1);
    char* str4 = "nwnfedededeedeujw4738593859384frfrfrfrfr5jf";
    writeStringsToFile(files[14], &str4, 1);

    return 0;
}