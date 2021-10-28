/* 
Thomas Fenaroli
CS50
querier.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/word.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"

struct countersNode {
  int key;
  int count;
};

typedef struct countersPair {
  counters_t* countersIntersection;
  counters_t* firstCounters;
} countersPair_t;

void unionQuery(counters_t* firstCounters, counters_t* secondCounters);
void intersectionQuery(countersPair_t* pairPointer, counters_t* secondCounters);
void updateUnion(void* arg, const int key, const int count);
void updateIntersection(void* arg, const int key, const int count);
void updateMaxNode(void* arg, const int key, const int count);
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

void unionQuery(counters_t* firstCounters, counters_t* secondCounters) {
    counters_iterate(secondCounters, firstCounters, &updateUnion);
}

void intersectionQuery(countersPair_t* pairPointer, counters_t* secondCounters) {
    counters_iterate(secondCounters, pairPointer, &updateIntersection);
}

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

void updateIntersection(void* arg, const int key, const int count) {
    countersPair_t* pairPointer = arg;
    int firstCount = counters_get(pairPointer->firstCounters, key);
    if (firstCount != 0) {
        int min = getMin(firstCount, count);
        counters_set(pairPointer->countersIntersection, key, min);
    }
}

void updateMaxNode(void* arg, const int key, const int count) {
    if (arg != NULL) {
        struct countersNode* maxNodePointer = arg;
        if (count > maxNodePointer->count) {
            maxNodePointer->count = count;
            maxNodePointer->key = key;
        }
    }
}

void updateCount(void* arg, const int key, const int count) {
    int* itemCount = arg;

    if (key != 0 && count != 0) {
        (*itemCount)++;
    }
}

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

void query(char* pageDirectory, char* indexFilename) {
    if (!parseArgs(pageDirectory, indexFilename)) {
        fprintf(stderr, "error parsing arguments, exiting non-zero\n");
        exit(1);
    }

    char* line;
    printf("Query: ");
    while ((line = file_readLine(stdin)) != NULL) {
        index_t* queryIndex = index_load(indexFilename);
        counters_t* resultCounters = parseQuery(line, queryIndex);
        //free(line);
        if (resultCounters != NULL) {
            printResults(resultCounters, pageDirectory);
        }
        counters_delete(resultCounters);
        printf("\n\n\n");
        printf("Query: ");
        index_delete(queryIndex);
    }
}

bool parseArgs(char* pageDirectory, char* indexFilename) {
    if (!pagedir_validatedir(pageDirectory)) {
        return false;
    }
    FILE* fp = fopen(indexFilename, "r");
    if (fp == NULL) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

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

// have to free normalizedWord somewhere
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
    int i = 0;
    while (i < wordCount) {
        printf("test\n");
        counters_t* countersIntersection = counters_new();
        counters_t* firstCounters = index_get(queryIndex, words[i]);
        countersPair_t pair = {countersIntersection, firstCounters};
        countersPair_t* pairPointer = &pair;
        int j = 0;
        while ((j < (wordCount - 1)) && (strcmp(words[i + 1], "and") == 0 || !isOperator(words[i + 1]))) {
            printf("entered inner loop!\n");
            //firstCounters = index_get(queryIndex, words[i]);
            if (j > 0) {
                printf("countersIntersection is: \n\n");
                counters_print(countersIntersection, stdout);
                pairPointer->firstCounters = pairPointer->countersIntersection;
                counters_delete(pairPointer->countersIntersection);
                pairPointer->countersIntersection = counters_new();
                printf("firstCounters is: \n\n");
                counters_print(pairPointer->firstCounters, stdout);
            }
            printf("reached if\n");
            counters_t* secondCounters;
            if (strcmp(words[j + 1], "and") == 0) {
                secondCounters = index_get(queryIndex, words[j + 2]);
                printf("inside if\n");
                printf("first word is %s, second word is %s\n", words[j], words[j + 2]);
                intersectionQuery(pairPointer, secondCounters);
                printf("made it past intersectionQuery\n");
                counters_print(pairPointer->countersIntersection, stdout);
                j += 2;
            }
            else if (strcmp(words[j + 1], "or") != 0) {
                secondCounters = index_get(queryIndex, words[j + 1]);
                printf("inside else\n");
                printf("first word is %s, second word is %s\n", words[j], words[j + 1]);
                intersectionQuery(pairPointer, secondCounters);
                j += 1;
            }

            printf("made it past if\n");
            counters_print(countersIntersection, stdout);
            printf("j is %d\n", j);
            printf("wordCount is %d\n\n\n\n\n", wordCount);
            //if (j >= (wordCount - 1)) break;
            //counters_delete(secondCounters);
        }

        if (i == 0 && j == 0) {
            intersectionQuery(pairPointer, firstCounters);
        }

        counters_print(countersIntersection, stdout);

        printf("made it out of loop\n");
        unionQuery(countersUnion, pairPointer->countersIntersection);
        //counters_delete(pairPointer->countersIntersection);
        i += (j + 1);
    }

    i = 0;
    while (i < wordCount) {
        free(words[i]);
        i++;
    }
    return countersUnion;
}

bool isOperator(char* word) {
    if (strcmp(word, "and") == 0 || strcmp(word, "or") == 0) {
        return true;
    }
    return false;
}

int getMin(int int1, int int2) {
    if (int1 <= int2) {
        return int1;
    }
    else {
        return int2;
    }
}

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