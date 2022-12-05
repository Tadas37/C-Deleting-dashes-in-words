#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char **input(int *n)
{
    FILE *file;
    char filename[128];
    int c;
    char **text;

    text = calloc(256, sizeof(char *));

    for (int i = 0; i < 256; i++)
    {
        text[i] = calloc(256, sizeof(char));
    }

    printf("Enter the data file name:\n");

    while (1)
    {
        scanf("%s", filename);
        file = fopen(filename, "r");

        if (file != NULL)
        {
            printf("File reading executed successfully\n");
            int line_size = 0;
            char ignore[1024];

            while ((c = getc(file)) != EOF)
            {
                if (line_size == 255)
                {
                    fgets(ignore, sizeof(ignore), file);
                    line_size = 0;
                    (*n)++;
                }
                else if (c == '\n')
                {
                    line_size = 0;
                    (*n)++;
                }
                else
                {
                    text[(*n)][line_size] = c;
                    line_size++;
                }
            }
            fclose(file);
            break;
        }
        else
        {
            printf("File couldn't be opened\n");
            printf("Input the data file name again:\n");
            fflush(stdin);
        }
    }
    (*n)++;
    
    text = realloc(text, sizeof(char *) * (*n));

    return text;
}

void delete_dash(int array_size, char **text)
{
    for (int i = 0; i < array_size; i++)
    {
        for (int j = 0; j < strlen(text[i]); j++)
        {
            if (tolower(text[i][j]) == '-' && (tolower(text[i][j - 1]) != '-' && tolower(text[i][j + 1]) != '-') && (tolower(isalpha(text[i][j - 1])) || !tolower(isalnum(text[i][j - 1]))) && (tolower(isalpha(text[i][j + 1])) || !tolower(isalnum(text[i][j + 1]))))
            {
                for (int k = j; k < strlen(text[i]); k++)
                {
                    text[i][k] = text[i][k + 1];
                }
            }
        }
    }
}

void output(int array_size, char **text)
{
    FILE *file;
    char filename[128];

    printf("Enter the result file name:\n");

    while (1)
    {
        scanf("%s", filename);

        if (strstr(filename, ".txt") != NULL && file != NULL)
        {
            printf("File writing executed successfully\n");
            file = fopen(filename, "w");
            for (int i = 0; i < array_size; i++)
                fprintf(file, "%s\n", text[i]);
            fclose(file);
            break;
        }
        else
        {
            printf("The file couldn't be written\n");
            printf("Input the result file name again:\n");
            fflush(stdin);
        }
    }
}

int main()
{
    char **text;
    int array_size = 0;

    text = input(&array_size);

    delete_dash(array_size, text);
    output(array_size, text);

    return 0;
}