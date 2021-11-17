/* 
Thomas Fenaroli
CS50
querier.c
*/

// inclusions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/word.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"

// countersNode struct
struct countersNode {
  int key;
  int count;
};

// function declarations
void unionQuery(counters_t* firstCounters, counters_t* secondCounters);
counters_t* intersectionQuery(counters_t* firstCounters, counters_t* secondCounters);
void updateUnion(void* arg, const int key, const int count);
void updateIntersection(void* arg, const int key, const int count);
void prepUpdateIntersection(void* arg, const int key, const int count);
void updateMaxNode(void* arg, const int key, const int count);
int getCountersSize(counters_t* counters);
void updateCount(void* arg, const int key, const int count);
char* getURL(int docID, char* pageDirectory);
void query(char* pageDirectory, char* indexFilename);
bool parseArgs(char* pageDirectory, char* indexFilename);
void printResults(counters_t* result, char* pageDirectory);
int tokenizeQuery(char* queryLine, char* words[]);
counters_t* parseQuery(char* queryLine, index_t* queryIndex);
bool isOperator(char* word);
int getMin(int int1, int int2);
int main(const int argc, char* argv[]);

// performs union query
void unionQuery(counters_t* firstCounters, counters_t* secondCounters) {
    counters_iterate(secondCounters, firstCounters, &updateUnion);
}

// performs intersection query
counters_t* intersectionQuery(counters_t* firstCounters, counters_t* secondCounters) {
    counters_t* intersectionCounters;
    counters_t* iteratingCounters;
    if (getCountersSize(firstCounters) <= getCountersSize(secondCounters)) {
        intersectionCounters = firstCounters;
        iteratingCounters = secondCounters;
    }
    else {
        intersectionCounters = secondCounters;
        iteratingCounters = firstCounters;
    }
    counters_iterate(intersectionCounters, iteratingCounters, &prepUpdateIntersection);
    counters_iterate(iteratingCounters, intersectionCounters, &updateIntersection);
    return intersectionCounters;
}

// updates union accordingly
void updateUnion(void* arg, const int key, const int count) {
    counters_t* firstCounters = arg;
    int firstCount = counters_get(firstCounters, key);
    if (firstCount == 0) {
        counters_set(firstCounters, key, count);
    }
    else {
        counters_set(firstCounters, key, firstCount + count);
    }
}

// prepares counters for intersection update
void prepUpdateIntersection(void* arg, const int key, const int count) {
    counters_t* iteratingCounters = arg;
    int get = counters_get(iteratingCounters, key);
    if (get == 0) {
        counters_set(iteratingCounters, key, 0);
    }
}

// updates intersection accordingly
void updateIntersection(void* arg, const int key, const int count) {
    counters_t* intersectionCounters = arg;
    int firstCount = counters_get(intersectionCounters, key);
    if (firstCount != 0) {
        int min = getMin(firstCount, count);
        counters_set(intersectionCounters, key, min);
    }
}

// updates the node with the maximum count
void updateMaxNode(void* arg, const int key, const int count) {
    if (arg != NULL) {
        struct countersNode* maxNodePointer = arg;
        if (count > maxNodePointer->count) {
            maxNodePointer->count = count;
            maxNodePointer->key = key;
        }
    }
}

// updates count of counters nodes
void updateCount(void* arg, const int key, const int count) {
    int* itemCount = arg;

    if (key != 0 && count != 0) {
        (*itemCount)++;
    }
}

// gets URL from a docID file
char* getURL(int docID, char* pageDirectory) {
    char fileName[100];
    sprintf(fileName, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(fileName, "r");
    if (fp != NULL) {
        char* URL = file_readLine(fp);
        fclose(fp);
        return URL;
    }
    else {
        fprintf(stderr, "error: failed to retrieve docID URL, exiting non-zero\n");
        exit(1);
    }
}

// performs query
void query(char* pageDirectory, char* indexFilename) {
    if (!parseArgs(pageDirectory, indexFilename)) {
        fprintf(stderr, "error: couldn't parse arguments, exiting non-zero\n");
        exit(1);
    }
    index_t* queryIndex = index_load(indexFilename);

    char* line;
    printf("Query: ");
    while ((line = file_readLine(stdin)) != NULL) {
        counters_t* resultCounters = parseQuery(line, queryIndex);
        free(line);
        if (resultCounters != NULL) {
            printResults(resultCounters, pageDirectory);
        }
        counters_delete(resultCounters);
        printf("\n\n\n");
        printf("Query: ");
        index_delete(queryIndex);
    }
}

// gets countersSize
int getCountersSize(counters_t* counters) {
    int itemCount = 0;
    counters_iterate(counters, &itemCount, &updateCount);
    return itemCount;
}

// parses command-line arguments
bool parseArgs(char* pageDirectory, char* indexFilename) {
    if (!pagedir_validatedir(pageDirectory)) {
        return false;
    }
    FILE* fp = fopen(indexFilename, "r");
    if (fp == NULL) {
        fclose(fp);
        fprintf(stderr, "error: couldn't parse arguments, exiting non-zero\n");
        exit(1);
    }
    fclose(fp);
    return true;
}

// prints results from query
void printResults(counters_t* result, char* pageDirectory) {
    int itemCount = 0;
    counters_iterate(result, &itemCount, &updateCount);
    if (itemCount == 0) {
        printf("no documents match the query\n");
    }
    else {
        struct countersNode maxNode = {0, 0};
        struct countersNode* maxNodePointer = &maxNode;

        counters_iterate(result, maxNodePointer, &updateMaxNode);
        char* URL = getURL(maxNodePointer->key, pageDirectory);
        printf("docID: %d, score: %d, URL: %s", maxNodePointer->key, maxNodePointer->count, URL);
        free(URL);
        printf("\n");
        counters_set(result, maxNodePointer->key, 0);
        while (maxNodePointer->count != 0) {
            maxNodePointer->count = 0;
            counters_iterate(result, maxNodePointer, &updateMaxNode);
            if (maxNodePointer->count != 0) {
                char* URL = getURL(maxNodePointer->key, pageDirectory);
                printf("docID: %d, score: %d, URL: %s", maxNodePointer->key, maxNodePointer->count, URL);
                free(URL);
                printf("\n");
                counters_set(result, maxNodePointer->key, 0);
            }
        }
    }
}

// tokenizes query
int tokenizeQuery(char* queryLine, char* words[]) {
    char* word = queryLine;
    char* rest;
    int wordCount = 0;
    while (*word != '\0') {
        while (isalpha(*word) == 0) {
            word++;
        }
        rest = word;
        while (isalpha(*rest) != 0) {
            rest++;
        }
        if ((*rest) == '\0') {
            char* normalizedWord = normalizeWord(word);
            words[wordCount] = normalizedWord;
            wordCount++;
            return wordCount;
        }
        else {
            *rest = '\0';
            char* normalizedWord = normalizeWord(word);
            words[wordCount] = normalizedWord;
            wordCount++;
            rest++;
            word = rest;
        }
    }
    return wordCount;
}

// parses query
counters_t* parseQuery(char* queryLine, index_t* queryIndex) {
    for (int i = 0; i < strlen(queryLine); i++) {
        if (isalpha(queryLine[i]) == 0 && isspace(queryLine[i]) == 0) {
            fprintf(stderr, "error: invalid character %c, taking next query\n", queryLine[i]);
            return NULL;
        }
    }
    int arrayLength = (int)(strlen(queryLine))/2;
    char* words[arrayLength];
    int wordCount = 0;
    wordCount = tokenizeQuery(queryLine, words);
    printf("here is tokenized query:\n");
    for(int i = 0; i < wordCount; i++) {
        printf("%s ", words[i]);
    }
    printf("\n\n");

    if (isOperator(words[0])) {
        fprintf(stderr, "error: first word is an operator, taking next query\n");
        return NULL;
    }
    else if (isOperator(words[wordCount - 1])) {
        fprintf(stderr, "error: last word is an operator, taking next query\n");
        return NULL;
    }

    for (int i = 0; i < wordCount; i++) {
        if (isOperator(words[i])) {
            if (isOperator(words[i + 1])) {
                fprintf(stderr, "error: adjacent operators, taking next query\n");
                return NULL;
            }
        }
    }

    counters_t* countersUnion = counters_new();
    counters_t* countersIntersection = index_get(queryIndex, words[0]);
    for (int i = 1; i < wordCount; i++) {
        if (strcmp(words[i], "or") == 0) {
            unionQuery(countersUnion, countersIntersection);
            countersIntersection = counters_new();
            countersIntersection = index_get(queryIndex, words[i + 1]);
            i++;
        }
        else if (!isOperator(words[i])) {
            countersIntersection = intersectionQuery(countersIntersection, index_get(queryIndex, words[i]));
        }
    }

    unionQuery(countersUnion, countersIntersection);

    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    return countersUnion;
}

// determines if word is an operator ("and" or "or")
bool isOperator(char* word) {
    if (strcmp(word, "and") == 0 || strcmp(word, "or") == 0) {
        return true;
    }
    return false;
}

// gets the minimum value of two integers
int getMin(int int1, int int2) {
    if (int1 <= int2) {
        return int1;
    }
    else {
        return int2;
    }
}

// main function
int main (int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "error: improper number of arguments, exiting non-zero\n");
        exit(1);
    }

    char* pageDirectory = argv[1];
    char* indexFilename = argv[2];

    query(pageDirectory, indexFilename);
    return 0;
}