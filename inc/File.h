#ifndef DIFFTOOL_INC_FILE_H
#define DIFFTOOL_INC_FILE_H

#include <stddef.h>

struct FileContents
{
    size_t nrOfLines;
    char **lines;
};

int readFile(const char *fileName, struct FileContents *outContents);

#endif //DIFFTOOL_INC_FILE_H
