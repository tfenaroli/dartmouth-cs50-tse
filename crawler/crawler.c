/* 
Thomas Fenaroli
CS50
crawler.c
*/

#include <stdio.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/counters.h"
#include "../libcs50/set.h"
#include "../libcs50/hashtable.h"
#include "../common/pagedir.h"

/* parses arguments
takes arguments: argc, argv, seedURL, pageDirectory, maxDepth
returns void
*/
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

/* scans webpage for URLs
takes arguments: page, pagesToCrawl, pagesSeen
returns void
*/
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

/* performs web crawl
takes arguments: seedURL, pageDirectory, maxDepth
returns void
*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

// main function
int main(int argc, char *argv[] );

// parses arguments
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    char* normalizedURL = normalizeURL(*seedURL);

    if (!isInternalURL(normalizedURL)) {
        fprintf(stderr, "error: URL is not an internal URL, exiting non-zero\n\n");
        exit(1);
    }

    free(normalizedURL);
    if (!pagedir_init(*pageDirectory)) {
        exit(1);
    }

    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "error: depth %d is out of range, exiting non-zero\n\n", *maxDepth);
        exit(1);
    }
    return;
}

// scans webpage for URLs
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {
    int pos = 0;
    char* result;

    while ((result = webpage_getNextURL(page, &pos)) != NULL) {
        //printf("found: %s\n", result);
        int depth = webpage_getDepth(page);
        char* normalizedURL = normalizeURL(result);
        char* allocatedNormalizedURL = malloc(strlen(normalizedURL) + 1);
        if (allocatedNormalizedURL == NULL) {
            fprintf(stderr, "error: couldn't allocate memory for URL, exiting non-zero");
            exit(1);
        }

        strcpy(allocatedNormalizedURL, normalizedURL);
        if (isInternalURL(normalizedURL)) {
            bool inserted = hashtable_insert(pagesSeen, normalizedURL, "");
            if (inserted) {
                webpage_t* newPage = webpage_new(allocatedNormalizedURL, depth + 1, NULL);
                bag_insert(pagesToCrawl, newPage);
            }
            else {
                free(allocatedNormalizedURL);
            }
        }
        else {
            free(allocatedNormalizedURL);
        }
        free(normalizedURL);
        free(result);
    }
    printf("\n");
}

// performs web crawl
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {

    printf("starting to crawl\n\n");
    
    hashtable_t* hashtable = hashtable_new(5);
    hashtable_insert(hashtable, seedURL, "");

    bag_t* bag = bag_new();
    webpage_t* initPage = webpage_new(seedURL, 0, NULL);
    bag_insert(bag, initPage);

    int docID = 1;
    webpage_t* webpage = bag_extract(bag);
    while (webpage != NULL) {
        if (webpage_fetch(webpage)) {
            pagedir_save(webpage, pageDirectory, docID);
            docID++;
            if (webpage_getDepth(webpage) < maxDepth) {
                pageScan(webpage, bag, hashtable);
            }
        }
        webpage_delete(webpage);
        webpage = bag_extract(bag);
    }
    hashtable_delete(hashtable, NULL);
    bag_delete(bag, webpage_delete);
}

// main function
int main(int argc, char *argv[] ) {

    if (argc != 4) {
        fprintf(stderr, "error: improper number of arguments, exiting non-zero\n");
        exit(1);
    }

    char* seedURL = malloc(strlen(argv[1]) + 1);
    if (seedURL == NULL) {
            fprintf(stderr, "error: couldn't allocate memory for URL, exiting non-zero");
            exit(1);
        }
    strcpy(seedURL, argv[1]);

    char* pageDirectory = argv[2];
    int maxDepthInt = atoi(argv[3]);
    int* maxDepth = &maxDepthInt;
    parseArgs(argc, argv, &seedURL, &pageDirectory, maxDepth);
    crawl(seedURL, pageDirectory, *maxDepth);
    
    return 0;
}