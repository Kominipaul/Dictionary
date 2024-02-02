#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "Hash.h"
#include "QuickSort.h"


// ΠΑΟΥΛΙΝ ΚΟΜΙΝΙ 202220210090 dit21090@go.uop.gr
// ΒΑΣΙΛΗΣ ΚΟΥΤΑΝΤΟΣ 2022202100097 dit21097@go.uop.gr


typedef struct Word
{
    char *word;
    struct Word *next;
} Word;

int INT_HASH_TABLE(char* filename ,Word** table_row, int DICTIONARYSIZE)
{   
    FILE *fp = fopen(filename, "r");            //Open Wordlist
    if(fp == NULL)                              //Check if file exists
    {
        printf("Error: file does not exist.");
        exit(1);
    }

    char lineBuffer[50], lineBufferCopy[50];                        //make a buffer to store the words
    unsigned int key;

    while (fgets(lineBuffer, 50, fp) != NULL)  //Loop until end of file
    {
        lineBuffer[strlen(lineBuffer)-1] = '\0';                    //remove the \n from the end of the word
        
        strcpy(lineBufferCopy, lineBuffer);                         //copy the lineBuffer to the copy

        quickSort(lineBuffer, 0 , strlen(lineBuffer)-1);            //sort the word

        key = HASH(lineBuffer, DICTIONARYSIZE);                     //Pass word to hash fun and get the hash

        //printf("\nword: %s\ncopy : %s\nhash: %d\n",lineBufferCopy, lineBuffer, key);

        if (table_row[key] == NULL) {                       // check if the table_row[key] is empty
            Word *newWord = malloc(sizeof(Word));           // Allocate memory for new word struct
            newWord->word = malloc(sizeof(char) * strlen(lineBuffer)+1);   // malloc ---//---
            //newWord->word = strdup(lineBuffer);             // Copy lineBuffer into newWord->word
            strcpy(newWord->word, lineBuffer);              // Copy lineBuffer into newWord->word   

            Word *newWordCopy = malloc(sizeof(Word));       // Allocate memory for new word struct
            newWordCopy->word = malloc(sizeof(char) * strlen(lineBufferCopy)+1);
            //newWordCopy->word = strdup(lineBufferCopy);     // Copy lineBuffer into newWord->Word
            strcpy(newWordCopy->word, lineBufferCopy);
            newWordCopy->next = NULL;                       // Set next pointer to NULL

            table_row[key] = newWord;                       // save struct newWord to it
            newWord->next = newWordCopy;                    // set the next pointer to newWordCopy

        } else {
            if (strcmp(table_row[key]->word, lineBuffer) == 0) {      //check if the word is the same
                Word *newWordCopy = (Word*)malloc(sizeof(Word));      // Allocate memory for new word struct
                newWordCopy->word = malloc(sizeof(char) * strlen(lineBufferCopy)+1);
                //newWordCopy->word = strdup(lineBufferCopy);           // Copy lineBuffer into newWord->Word
                strcpy(newWordCopy->word, lineBufferCopy);
                newWordCopy->next = NULL; 

                Word *current = table_row[key];                       //make a pointer to the current word
                while (current->next != NULL) {
                    current = current->next;                          //loop until you find the last word
                }
                current->next = newWordCopy;                          // Set next pointer to NULL
            }       
        }
    }
    fclose(fp);                                                       //close file  for no leaks.
}

//make a function to display the table with the words and if the have a collision print them next to each other with an arrow.  --->
void Display(Word** table_row, int DICTIONARYSIZE)
{
    for (int i = 0; i < DICTIONARYSIZE; i++)
    {
        if (table_row[i] != NULL)
        {
            Word *current = table_row[i];
            printf("%d) %s", i, current->word);
            while (current->next != NULL)
            {
                current = current->next;
                printf(" --> %s", current->word);
            }
        }
        printf("\n");
    }
}

int Search(Word** table_row, int DICTIONARYSIZE)
{
    char word[50], wordCopy[50];

    printf("Give me a word to search: ");
    scanf("%s", word);
    scanf("%*[^\n]");
    fflush(stdin);

    strcpy(wordCopy, word);

    quickSort(word, 0, strlen(word)-1);
    printf("Sorted word: %s\n", word);

    unsigned int key = HASH(word, DICTIONARYSIZE);
    printf("Hash: %d\n", key);

    int count = 0;
    Word *current = table_row[key];
    while (current->next != NULL)
    {
        count++;
        current = current->next;
        if (strcmp(current->word, wordCopy) == 0)
        {
            printf("Cell: %d Word: %s\nLinkList: %d.\n", key, current->word, count);
            return 0;
        }
        
    }
}


int main(int argc, char *argv[])
{   
    if (argc < 2) {                 
        printf("./Dictionary file.txt\n");          //Check if user gave a wordlist.
        exit(0);
    }

    char* filename;
    filename = (char*)malloc(sizeof(argv[1]) + 5);  //allocate space for filename
    strcpy(filename, argv[1]);
    strcat(filename, ".txt");

    int DICTIONARYSIZE = atoi(argv[2]);             //get the DICTIONARYSIZE

    Word* table_row[DICTIONARYSIZE];
    for (int i = 0; i < DICTIONARYSIZE; i++) {
        table_row[i] = NULL;
    }

    INT_HASH_TABLE(filename, table_row, DICTIONARYSIZE);

    int mode = -1;
    do {
        mode = -1;

        printf("\n0.Exit\n1.Display\n2.Search\n");
        scanf("%d",&mode);
        scanf("%*[^\n]");
        fflush(stdin);

        if (mode == 1){
            Display(table_row, DICTIONARYSIZE);
        } else if (mode == 2)
        {
            Search(table_row, DICTIONARYSIZE);
        }
        fflush(stdin);
    } while (mode != 0);

    return 0;
}



