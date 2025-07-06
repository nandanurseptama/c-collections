#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"

void buble_sort(int count, int *input)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < i; j++)
        {

            if (input[j] > input[i])
            {
                int temp = input[j];
                input[j] = input[i];
                input[i] = temp;
            }
        }
    }
}

int solve(int totalLine, char **lines)
{
    int *left = (int *)malloc(totalLine);
    int *right = (int *)malloc(totalLine);

    // read input
    for (int i = 0; i < totalLine; i++)
    {
        if (sscanf(lines[i], "%d\t%d", &left[i], &right[i]) != 2)
        {
            return EXIT_FAILURE;
        }
    }

    buble_sort(totalLine, left);
    buble_sort(totalLine, right);

    int sum = 0;

    for (int i = 0; i < totalLine; i++)
    {
        int distance = absolute(left[i] - right[i]);
        printf("%d - %d = %d\n", left[i], right[i], distance);
        sum += distance;
    }

    printf("%d\n", sum);

    return EXIT_SUCCESS;
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

    int result = solve(count, lines);

    if (result > 0)
    {
        perror("failed to solve problem");
        return 0;
    }

    // printf("success solve the problem\n");

    freeTextData(lines, count);

    return 0;
}