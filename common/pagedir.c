/* 
Thomas Fenaroli
CS50
pagedir.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"

// initializes pageDirectory
bool pagedir_init(const char* pageDirectory) {
    char initialFileName[100];
    strcpy(initialFileName, pageDirectory);
    strcat(initialFileName, "/.crawler");
    FILE* fp = fopen(initialFileName, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error with pathDirectory, exiting non-zero\n");
        return false;
    }
    printf("added .crawler file to pageDirectory\n");
    fclose(fp);
    return true;
}

// saves file to pageDirectory
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {
    char fileName[100];
    sprintf(fileName, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(fileName, "w");
    if (fp != NULL) {
        printf("saved file %s based on URL: %s\n", fileName, webpage_getURL(page));
        char* URL = webpage_getURL(page);
        int depth = webpage_getDepth(page);
        char* html = webpage_getHTML(page);
        fprintf(fp, "%s\n", URL);
        fprintf(fp, "%d\n", depth);
        fprintf(fp, "%s\n", html);
        fclose(fp);
    }
    else {
        printf("failed to open file %d\n", docID);
    }
}