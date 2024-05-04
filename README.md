# MyFdupes

MyFdupes is a command-line tool designed to help you efficiently manage duplicate files within a directory by converting them into hard links.

## Features

- **Default Directory Check**: By default, the program checks only the selected directory without traversing internal directories. For recursive traversal, use the `-r` option.
- **Duplicate Detection Algorithm**: The program employs a checksum-based algorithm using SHA256 hashing to find file duplicates.
- **Efficient Storage**: A hash table is utilized to store checksums of files, ensuring only one instance of a file is stored. If a duplicate is found, it won't be inserted into the table.
- **Logging**: MyFdupes logs instances of replacing a file with a hard link in the `log.txt` file.
- **Empty File Handling**: Empty files are skipped by default.

## Usage

The program accepts the following command line arguments: `MyFdupes [options] [directoryPath]`. If no directory path is specified, the current directory is used.

### Options:

- **Recursive Mode (-r)**: Recursively search through subdirectories for duplicates.
- **Force Mode (-f)**: Automatically replace duplicate files without prompting for confirmation.
- **Empty File Deletion (-e)**: Delete empty files.
- **Help Information (-h)**: Display a detailed summary of MyFdupes' usage and available options.

## Contributions

Contributions to MyFdupes are welcome! If you encounter any issues, have suggestions for improvements, or would like to contribute code, please open an issue or submit a pull request on GitHub.


