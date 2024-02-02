#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "Hash.h"
#include "QuickSort.h"


// ΠΑΟΥΛΙΝ ΚΟΜΙΝΙ 202220210090 dit21090@go.uop.gr
// ΒΑΣΙΛΗΣ ΚΟΥΤΑΝΤΟΣ 2022202100097 dit21097@go.uop.gr

int INT_HASH_TABLE(char* filename ,char **table_row, int DICTIONARYSIZE)
{   
    FILE *fp = fopen(filename, "r");            //Open Wordlist

    if(fp == NULL)
    {
        printf("Error: file pointer is null."); //Check if empty
        exit(1);
    }

    char lineBuffer[50];
    unsigned int key;

    while (fgets(lineBuffer, 50, fp) != NULL)  //Loop until end of file
    {
        lineBuffer[strlen(lineBuffer)-1] = '\0';            
        key = HASH(lineBuffer, DICTIONARYSIZE);             //Pass word to hash fun and get the hash

        if (table_row[key] == NULL)                       //Check if table is empty in this posision
        {
            table_row[key] = (char*)malloc(sizeof(char) * strlen(lineBuffer)+1);    //malloc size of word + 1 (\n)
            strcpy(table_row[key], lineBuffer);         //copy the word from the buffer to the table
        }
        else
        {
            int count = 0;
            do {
                count++;
                if (count == DICTIONARYSIZE) return 1;
                key++;
                if (key >= DICTIONARYSIZE)
                {
                    key = 0;
                }
            } while(table_row[key] != NULL);    //loop until you find a empty array

            table_row[key] = malloc(sizeof(char) * strlen(lineBuffer)+1);   // malloc ---//---
            strcpy(table_row[key], lineBuffer);                             // copy ---//---
        }
    }
    
    fclose(fp);     //close file  for no leaks.
}

int Display(char **table_row, int DICTIONARYSIZE)
{
    for (unsigned int i = 0; i < DICTIONARYSIZE; i++)   
    {
        if (table_row[i] != NULL)       //chech if the array in tha cell is empty 
        {   
            printf("%d) %s\n", i, table_row[i]);  //print the word & the id(array cell)
        }
    }
    return 0;
}

int Search(char **table_row, int DICTIONARYSIZE)
{   
    unsigned int key, hash;
    char lineBuffer[50];

    printf("Give me a word to search: ");
    scanf("%s", lineBuffer);
    scanf("%*[^\n]");
    fflush(stdin);

    hash = HASH(lineBuffer, DICTIONARYSIZE);
    key = hash;

    if (table_row[key] == NULL)
    {
        printf("CELL/HASH: %d is NULL\n", hash);
        printf("This word in not in the dictionary!!!\n");
        return 1;
    }

    int count = 0;
    while (strcmp(table_row[key], lineBuffer) != 0)
    {
        key++;
        count++;
        if (key >= DICTIONARYSIZE) key = 0;
        if (count >= DICTIONARYSIZE) {
            printf("This word in not in the dictionary.\n");
            return 1;
        }
    }
    printf("Word: %s\nHash: %d\nCell: %d\n",table_row[key], hash, key);

    return 0;
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

    int DICTIONARYSIZE = strtol(argv[2], NULL, 10);             //get the DICTIONARYSIZE

    char **table_row = (char**)malloc(sizeof(char*) * DICTIONARYSIZE);

    for (int i = 0; i < DICTIONARYSIZE; i++)
    {
        table_row[i] = NULL;                        //Set the new space to NULL
    }
    
    INT_HASH_TABLE(filename, table_row, DICTIONARYSIZE);

    int mode = -1;
    do
    {
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

