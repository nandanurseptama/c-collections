#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"

struct line
{
    int value;
    int *prev;
    int *next;
};

int main()
{
    FILE *file;
    int ch;
    char *content = NULL; // Pointer to store the file content
    size_t size = 0;      // Current size of the content
    size_t capacity = 1;  // Initial capacity

    // Open the file in read mode
    file = fopen("1.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Allocate initial memory
    content = (char *)malloc(capacity);
    if (content == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read file character by character
    while ((ch = fgetc(file)) != EOF)
    {
        if (size + 1 >= capacity)
        {
            // Double the capacity when needed
            capacity *= 2;
            char *new_content = (char *)realloc(content, capacity);
            if (new_content == NULL)
            {
                perror("Memory reallocation failed");
                free(content);
                fclose(file);
                return EXIT_FAILURE;
            }
            content = new_content;
        }

        content[size++] = (char)ch; // Store the character
    }

    // Null-terminate the string
    content[size] = '\0';

    // Close the file
    fclose(file);

    // Use the content (Here, we simply print it for verification)
    printf("File Content:\n%s", content);

    // Free allocated memory
    free(content);

    return EXIT_SUCCESS;
}