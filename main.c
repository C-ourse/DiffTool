#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FileContents
{
    size_t nrOfLines;
    char **lines;
};

int readFile(const char *fileName, struct FileContents *outContents)
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Error opening file %s.\n", fileName);
        return EXIT_FAILURE;
    }

    while (!feof(file))
    {
        outContents->nrOfLines++;
        outContents->lines = realloc(outContents->lines, outContents->nrOfLines);

        size_t dummySize = 0;
        getline(&outContents->lines[outContents->nrOfLines - 1], &dummySize, file);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    // TODO: Validate args

    struct FileContents left = {0};
    struct FileContents right = {0};

    // TODO: Error-check
    readFile(argv[1], &left);
    readFile(argv[2], &right);

    printf("%s%s", left.lines[0], left.lines[1]);

    // differences = compare(contents);

    // displayDifferences(differences);

    return 0;
}
