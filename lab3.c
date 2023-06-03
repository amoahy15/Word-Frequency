/**
 * This program reads a text file and [file this in] The file name is provided using command line
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author Humphrey Amoakohene {@literal }
 * @date March. 2, 2023
 * @assignment Lab 3
 * @course CSC 250
 **/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 20

/* a useful struct, if you choose to use it  */
struct WordFreq
{
    char *word;
    int count;
};

/* function declarations */
int process_characters(char filename[], struct WordFreq **list, int *num);
void add_word(struct WordFreq **list, int *num, char *word);
void output_frequency(char *filename, struct WordFreq *list, int num);
void sort_words(struct WordFreq *list, int num);
int unique_word_count(struct WordFreq *list, int num);


int main(int argc, char *argv[])
{
    struct WordFreq *list = NULL;
    int num = 0;
    int fileOK = 1;
    int unique_word;
    int i;

    /* check command line arguments */
    if (argc < 3)
    {
        printf("Usage: %s filename frequency_file\n", argv[0]);
        return 1;
    }

    fileOK = process_characters(argv[1], &list, &num);

    if (!fileOK)
    {
        printf("%s could not open file %s\n", argv[0], argv[1]);
        return 2;
    }
    /* sort words*/
    sort_words(list, num);
    unique_word = unique_word_count(list, num);
    printf("%s has %d unique words\n", argv[1], unique_word);

    /* write frequency to output file */
    output_frequency(argv[2], list, num);

    /* free allocated memory */
    for (i = 0; i < num; i++)
    {
        free(list[i].word);
    }
    free(list);

    return 0;
}

int process_characters(char filename[], struct WordFreq **list, int *num)
{
    char ch;
    FILE *filePtr;
    char buffer[MAX_STRING_SIZE];
    int n = 0;

    buffer[0] = '\0';

    filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        return 0;
    }

    ch = fgetc(filePtr);
    while (ch != EOF)
    {
        if (isalpha(ch))
        {
            ch = tolower(ch);
            buffer[n] = ch;
            n++;
            buffer[n] = '\0';
        }
        else if (n > 0)
        {
            add_word(list, num, buffer); /* add word to list */
            buffer[0] = '\0';
            n = 0;
        }
        ch = fgetc(filePtr);
    }

    fclose(filePtr);
    return 1;
}

void add_word(struct WordFreq **list, int *num, char *word)
{
    int i;

    /* check if word already exists in list if not return */
    for (i = 0; i < *num; i++)
    {
        if (strcmp((*list)[i].word, word) == 0)
        {
            (*list)[i].count++;
            return;
        }
    }

    /* add new word to list*/
    *list = realloc(*list, sizeof(struct WordFreq) * (*num + 1));
    (*list)[*num].word = malloc(strlen(word) + 1);
    strcpy((*list)[*num].word, word);
    (*list)[*num].count = 1;
    (*num)++;
}
void sort_words(struct WordFreq *list, int num)
{
    int i, j;
    struct WordFreq temp;

    for (i = 0; i < num - 1; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (list[i].count < list[j].count)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}
void output_frequency(char *filename, struct WordFreq *list, int num)
{
    int i;
    FILE *filePtr;
    filePtr = fopen(filename, "w");
    for (i = 0; i < 10; i++)
    {
        fprintf(filePtr, "%s %d\n", list[i].word, list[i].count);
    }
    fclose(filePtr);
}
int unique_word_count(struct WordFreq *list, int num)
{
    int count = 0;
    int i;

    for (i = 0; i < num; i++)
    {
        if (list[i].count == 1)
        {
            count++;
        }
    }

    return count;
}