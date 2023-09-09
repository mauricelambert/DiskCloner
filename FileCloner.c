// This file implements an optimized file cloner
// (initially used to clone a complet hard disk).

/*
    Copyright (C) 2023  Maurice Lambert
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// Linux:
// gcc -O5 FileCloner.c -o LinuxFileCloner
// gcc -O5 FileCloner.c -shared -o libFileCloner.so

// Windows:
// gcc -O5 FileCloner.c -o WindowsFileCloner.exe
// gcc -O5 FileCloner.c -shared -o libFileCloner.dll

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// This function clones a file from FILE object
extern unsigned int clone_from_file(
    FILE *source,
    FILE *destination,
    unsigned char *buffer,
    unsigned int bufferSize
) {
    size_t readSize, writeSize;

    do {
        readSize = fread(buffer, sizeof(char), bufferSize, source);
        writeSize = fwrite(buffer, 1, readSize, destination);
    } while (readSize && readSize == writeSize);

    if (readSize) {
        fputs("Error copying file content.", stderr);
        return 4;
    }

    return 0;
}

// This function clones a file from string filename
extern unsigned int clone_from_filename(
    const unsigned char *sourcepath,
    const unsigned char *destinationpath,
    unsigned char *buffer,
    unsigned int bufferSize
) {
    FILE *source, *destination;

    source = fopen(sourcepath, "rb");
    destination = fopen(destinationpath, "wb");

    if (source == NULL) {
        fputs("Error opening the source file.", stderr);
        if (destination != NULL) {
            fclose(destination);
        }
        return 5;
    }

    if (destination == NULL) {
        fputs("Error opening the destination file.", stderr);
        if (source != NULL) {
            fclose(destination);
        }
        return 6;
    }

    unsigned int code = clone_from_file(
        source, destination, buffer, bufferSize
    );

    fclose(source);
    fclose(destination);

    return code;
}

// This function starts the program execution (parses ARGV)
int main(int argc, const char** argv) {
    if (argc < 3 || argc > 4) {
        fputs(
            "USAGES: ./CloneFile [bufferSize, default: 131072] "
            "sourcePath destinationPath",
            stderr
        );
        return 1;
    }

    if (argc == 4) {
        for (unsigned int index = 0; argv[1][index] != 0; index += 1) {
            if (!isdigit(argv[1][index])) {
                fputs("bufferSize is invalid, must be digits.", stderr);
                return 2;
            }
        }
    }

    const unsigned char *sourcepath, *destinationpath;
    unsigned char defaultBuffer[131072];
    unsigned int bufferSize;
    unsigned char *buffer;

    if (argc == 4) {
        bufferSize = atoi(argv[1]);
        buffer = malloc(sizeof(char) * bufferSize);

        sourcepath = argv[2];
        destinationpath = argv[3];
    } else {
        bufferSize = 131072;
        buffer = defaultBuffer;

        sourcepath = argv[1];
        destinationpath = argv[2];
    }

    unsigned int code = clone_from_filename(
        sourcepath, destinationpath, buffer, bufferSize
    );

    if (argc == 4) {
        free(buffer);
    }

    return code;
}
