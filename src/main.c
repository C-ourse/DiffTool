#include <stdio.h>
#include <stdlib.h>

#include "File.h"
#include "Compare.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: <file1> <file2>\n");
        return EXIT_FAILURE;
    }

    struct FileContents left = {0};
    struct FileContents right = {0};

    if (readFile(argv[1], &left) || readFile(argv[2], &right))
    {
        exit(EXIT_FAILURE);
    }

    struct Differences differences = compare(&left, &right);

    displayDifferences(&differences, &left, &right);

    return 0;
}
