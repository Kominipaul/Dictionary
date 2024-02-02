#include <stdio.h> 
#include <string.h> 

// ΠΑΟΥΛΙΝ ΚΟΜΙΝΙ 202220210090 dit21090@go.uop.gr
// ΒΑΣΙΛΗΣ ΚΟΥΤΑΝΤΟΣ 2022202100097 dit21097@go.uop.gr

void swap(char* a, char* b) 
{ 
    char temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int partition(char* str, int low, int high) 
{ 
    char pivot = str[high]; // choose the last character as the pivot 
    int i = low - 1; // index of the smaller element 

    for (int j = low; j <= high - 1; j++) { 
        if (str[j] <= pivot) { 
            i++; // increment the index of the smaller 
            swap(&str[i], &str[j]); // swap the current
        } 
    } 
    swap(&str[i + 1], &str[high]); // swap the pivot with str[i + 1] 
    return i + 1; // return the pivot index 
} 

void quickSort(char* str, int low, int high) 
{ 
    if (low < high) { 
        int pivotIndex = partition( 
            str, low, high); // partition the string and get the pivot index 
        quickSort(str, low, pivotIndex - 1); // sort the left sub-array 
        quickSort(str, pivotIndex + 1, high); // sort the right sub-array 
    } 
} 