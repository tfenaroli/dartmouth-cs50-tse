/* 
Thomas Fenaroli
CS50
indexer.c
*/

#include <stdio.h>
#include "../common/index.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../common/word.h"
#include "../common/pagedir.h"

// scans a webpage to add words to index
void indexPage(webpage_t* page, int docID, index_t* index) {
    int pos = 0;
    char* result;
    while ((result = webpage_getNextWord(page, &pos)) != NULL) {
        if (strlen(result) >= 3) {
            char* normalizedWord = normalizeWord(result);
            counters_t* wordCounters = index_get(index, normalizedWord);
            if (wordCounters == NULL) {
                index_add(index, normalizedWord);
                counters_add(index_get(index, normalizedWord), docID);
            }
            else {
                counters_add(wordCounters, docID);
            }
            free(normalizedWord);
        }
        free(result);
    }
}

// builds index
void indexBuild(const char* pageDirectory, const char* indexFilename) {
    if (!pagedir_validatedir(pageDirectory)) {
        fprintf(stderr, "error: crawled pageDirectory not found, exiting non-zero\n");
        exit(1);
    }
    index_t* index = index_new(NULL);
    FILE* fp;
    int docID = 1;
    char fileName[100];
    sprintf(fileName, "%s/%d", pageDirectory, docID);
    while ((fp = fopen(fileName, "r")) != NULL) {
        webpage_t* webpage = pagedir_load(fp);
        indexPage(webpage, docID, index);
        webpage_delete(webpage);

        docID += 1;
        sprintf(fileName, "%s/%d", pageDirectory, docID);
        fclose(fp);
    }

    index_save(index, indexFilename);

    index_delete(index);
}

// main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "error: improper number of arguments, exiting non-zero\n");
        exit(1);
    }

    char* pageDirectory = argv[1];
    char* indexFilename = argv[2];
    
    indexBuild(pageDirectory, indexFilename);
    
    return 0;
}
