#include "Compare.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "File.h"

static void addDifference(struct Differences * this, size_t index)
{
    this->len++;
    this->indices = realloc(this->indices, sizeof(size_t) * this->len);
    this->indices[this->len - 1] = index;
}

struct Differences compare(struct FileContents *left, struct FileContents *right)
{
    struct Differences differences = {0};
    size_t shorter = left->nrOfLines;

    if (left->nrOfLines > right->nrOfLines)
    {
        shorter = right->nrOfLines;
    }

    for (size_t i = 0; i < shorter; i++)
    {
        if (strcmp(left->lines[i], right->lines[i]) != 0)
        {
            addDifference(&differences, i);
        }
    }

    return differences;
}

void displayDifferences(const struct Differences *differences,
                        const struct FileContents *left,
                        const struct FileContents *right)
{
    for (size_t i = 0; i < differences->len; i++)
    {
        const size_t line = differences->indices[i];
        printf("%zu Left:  %s\n"
               "%zu Right: %s\n",
               line + 1, left->lines[line], line + 1, right->lines[line]);
    }

    const struct FileContents* shorter = left;
    const struct FileContents* longer = right;
    const char *longerSignature = "Right: ";

    if (left->nrOfLines > right->nrOfLines)
    {
        shorter = right;
        longer = left;
        longerSignature = "Left:  ";
    }

    for (size_t i = shorter->nrOfLines; i < longer->nrOfLines; i++)
    {
        printf("%zu %s%s\n", i + 1, longerSignature, longer->lines[i]);
    }
}
