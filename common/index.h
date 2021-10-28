/* 
Thomas Fenaroli
CS50
index.h
*/

#include <stdio.h>
#include <stdbool.h>

#include "../libcs50/counters.h"

// index struct
typedef struct index index_t;

// handles docID-count pair
void handleCtrsPair(void* arg, const int key, const int count);

// handles word-counters_t* pair
void handleHtPair(void* arg, const char* key, void* item);

// creates new index
index_t* index_new();

// adds to the index
bool index_add(index_t* index, char* word);

// gets the counters of a word
counters_t* index_get(index_t* index, char* word);

// loads an index from a file
index_t* index_load(char* fileName);

// prints an index to a file
void index_save(index_t* index, const char* indexFilename);

// deletes an index
void index_delete(index_t* index);