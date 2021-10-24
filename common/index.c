/* 
Thomas Fenaroli
CS50
index.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/file.h"

// index struct
typedef struct index {
    hashtable_t* indexHashtable;
} index_t;

// handles docID-count pair
void handleCtrsPair(void* arg, const int key, const int count) {
    FILE* fp = (FILE*) arg;
    if (key >= 0 && count > 0) {
        fprintf(fp, "%d %d ", key, count);
    }
}

// handles word-counters_t* pair
void handleHtPair(void* arg, const char* key, void* item) {
    FILE* fp = (FILE*) arg;
    fprintf(fp, "%s ", key);
    if (key != NULL && item != NULL) {
        counters_iterate(item, arg, &handleCtrsPair);
    }
    fprintf(fp, "\n");
}

// index_new (see index.h for description)
index_t* index_new(int* numWords) {
    index_t* newIndex = malloc(sizeof(index_t*));
    if (newIndex == NULL) {
        fprintf(stderr, "error: out of memory, exiting non-zero\n");
        exit(1);
    }
    if (numWords != NULL) {
        newIndex->indexHashtable = hashtable_new(*numWords);
    }
    else {
        newIndex->indexHashtable = hashtable_new(500);
    }
    return newIndex;
}

// index_add (see index.h for description)
bool index_add(index_t* index, char* word) {
    counters_t* counters = counters_new();
    bool result = hashtable_insert(index->indexHashtable, word, counters);
    return result;
}

// index_get (see index.h for description)
counters_t* index_get(index_t* index, char* word) {
    counters_t* item = hashtable_find(index->indexHashtable, word);
    return item;
}

// index_load (see index.h for description)
index_t* index_load(char* fileName) {
    char* word;
    int docID = 0;
    int count = 0;

    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: couldn't open oldIndexFilename for reading, exiting non-zero\n");
        exit(1);
    }

    int numLines = file_numLines(fp);
    int* numLinesPointer = &numLines;
    index_t* index = index_new(numLinesPointer);

    while ((word = file_readWord(fp)) != NULL) {
        index_add(index, word);
        counters_t* counters = index_get(index, word);
        while ((fscanf(fp, "%d %d", &docID, &count)) == 2) {
            counters_add(counters, docID);
            counters_set(counters, docID, count);
        }
        free(word);
    }

    fclose(fp);

    return index;
}

// index_save (see index.h for description)
void index_save(index_t* index, const char* indexFilename) {
    FILE* fp = fopen(indexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "error: couldn't open index file, exiting non-zero\n");
        exit(1);
    }

    hashtable_iterate(index->indexHashtable, fp, &handleHtPair);

    fclose(fp);
}

// index_delete (see index.h for description)
void index_delete(index_t* index) {
    hashtable_delete(index->indexHashtable, &counters_delete);
    free(index);
}