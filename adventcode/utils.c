#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loader(const char *filename, char ***linesOut)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("failed to open file");
        return EXIT_FAILURE;
    }

    printf("file opened\n");

    size_t count = 0;
    // initial capacity
    size_t capacity = 10;
    char **lines = malloc(capacity * sizeof(char *));

    if (!lines)
    {
        fclose(file);
        perror("Failed to allocate memory for lines");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t size = 0;
    ssize_t read;

    while ((read = getline(&line, &size, file)) != -1)
    {
        if (line[read - 1] == '\n')
        {
            line[--read] = '\0';
        }

        if (count >= capacity)
        {
            capacity = capacity * 2;
            char **temp = realloc(lines, capacity * sizeof(char *));
            if (!temp)
            {
                perror("Failed to reallocate memory");
                free(line);
                for (size_t i = 0; i < count; i++)
                {
                    free(lines[i]);
                }
                free(lines);
                fclose(file);
                return -1;
            }
            lines = temp;
        }

        lines[count] = strdup(line); // allocate and copy the line
        count++;
    }

    free(line);
    fclose(file);
    *linesOut = lines;

    return (int)count;
}
// Free all memory used by lines
void freeTextData(char **lines, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

int main()
{
    char **lines = NULL;
    int count = loader("1.txt", &lines);

    if (count < 0)
    {
        perror("failed to load file");
        return EXIT_FAILURE;
    }

    printf("Loaded %d lines:\n", count);

    for (int i = 0; i < count; i++)
    {
        printf("Line %d: %s\n", i + 1, lines[i]);
    }

    freeTextData(lines, count);

    return 0;
}
