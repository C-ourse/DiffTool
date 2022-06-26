#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FileContents
{
    size_t nrOfLines;
    char **lines;
};

struct Differences
{
    size_t len;
    size_t *indices;
};

char *readLine(FILE *file)
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

void addDifference(struct Differences * this, size_t index)
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