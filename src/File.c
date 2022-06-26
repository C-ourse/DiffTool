#include "File.h"

#include <stdio.h>
#include <stdlib.h>

static char *readLine(FILE *file)
{
    size_t len = 1;
    char *line = malloc(len);

    for (char c = fgetc(file); (c != EOF) && (c != '\n'); c = fgetc(file))
    {
        len++;
        line = realloc(line, len);
        line[len - 2] = c; // TODO: Think about how to describe the magical '-2'
    }

    line[len - 1] = '\0';
    return line;
}

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

        outContents->lines[outContents->nrOfLines - 1] = readLine(file);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
