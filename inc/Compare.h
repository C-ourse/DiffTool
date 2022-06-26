#ifndef DIFFTOOL_INC_COMPARE_H
#define DIFFTOOL_INC_COMPARE_H

#include <stddef.h>

#include "File.h"

struct Differences
{
    size_t len;
    size_t *indices;
};

struct Differences compare(struct FileContents *left,
                           struct FileContents *right);

void displayDifferences(const struct Differences *differences,
                        const struct FileContents *left,
                        const struct FileContents *right);

#endif //DIFFTOOL_INC_COMPARE_H
