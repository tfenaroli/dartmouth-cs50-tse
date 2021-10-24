/* 
Thomas Fenaroli
CS50
pagedir.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"


// initializes pageDirectory
bool pagedir_init(const char* pageDirectory) {
    char initialFileName[100];
    strcpy(initialFileName, pageDirectory);
    strcat(initialFileName, "/.crawler");
    FILE* fp = fopen(initialFileName, "w");
    if (fp == NULL) {
        fprintf(stderr, "error: couldn't open initial file, returning false\n");
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
        fprintf(stderr, "failed to open file %d\n", docID);
    }
}

// validates pageDirectory
bool pagedir_validatedir(const char* pageDirectory) {
    char crawlerFileName[100];
    sprintf(crawlerFileName, "%s/.crawler", pageDirectory);
    if(access(crawlerFileName, F_OK ) == 0 ) {
        return true;
    }
    return false;
}

// creates webpage_t* from file
webpage_t* pagedir_load(FILE* fp) {
    char* url = file_readLine(fp);
    char* depthString = file_readLine(fp);
    int depth = atoi(depthString);
    char* html = file_readFile(fp);

    webpage_t* newPage = webpage_new(url, depth, html);

    if (newPage == NULL) {
        fprintf(stderr, "error: couldn't load new webpage from crawler-produced file, exiting non-zero\n");
        exit(1);
    }

    free(depthString);
    return newPage;
}