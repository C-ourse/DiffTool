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
        outContents->lines = realloc(outContents->lines, 
                                     outContents->nrOfLines * sizeof(char *));

        size_t dummySize = 0;
        getline(&outContents->lines[outContents->nrOfLines - 1], &dummySize, file);
    }

    return EXIT_SUCCESS;
}


int compare(struct FileContents *left, struct FileContents *right)
{
    int differences = 0;
    size_t smaller = left->nrOfLines;

    if (left->nrOfLines > right->nrOfLines)
    {
        smaller = right->nrOfLines;
        differences += left->nrOfLines - right->nrOfLines;
    }
    else
    {
        differences += right->nrOfLines - left->nrOfLines;
    }
    
    for (size_t i = 0; i < smaller; i++)
    {
        if (strcmp(left->lines[i], right->lines[i]) != 0)
        {
            differences++;
        }
    }

    return differences;
}

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
    
    int differences = compare(&left, &right);
    
    // displayDifferences(differences);
    printf("Diff lines: %d\n", differences);

    return 0;
}
