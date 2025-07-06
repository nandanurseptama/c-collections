#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loader(const char *filename, char ***linesOut)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("failed to open file");
        return -1;
    }

    size_t count = 0;
    // initial capacity
    size_t capacity = 10;
    char **lines = malloc(capacity * sizeof(char *));

    if (!lines)
    {
        fclose(file);
        perror("Failed to allocate memory for lines");
        return -1;
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

int absolute(int a){
    if(a < 0){
        return a * -1;
    }
    return a;
}