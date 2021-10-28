# CS50 TSE Querier
## Implementation Spec

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions.
The knowledge unit noted that an [implementation spec](https://github.com/CS50Dartmouth21FS1/home/blob/fall21s1/knowledge/units/design.md#implementation-spec) may include many topics; not all are relevant to the TSE or the Crawler.

## Data structures 

Counters: to map docID to count
Index: to store index from indexFileName

## Control flow

The querier is implemented in one file `querier.c`, with 9 functions.

### main

The `main` function simply calls `query` and returns 0

### parseArgs

Given arguments from the command line; return true only if successful. Ensure...
pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be read;

Pseudocode:

    if (file open for reading pageDirectory + crawler is NULL)
        error and exit non-zero
    if (file open for reading indexFilename is NULL)
        error and exit non-zero
    return true

### parseQuery

Given not-clean query as a string and index; return counters_t* only if successful. This function will parse the query, print out a clean query, validate the query, then generate the results counters_t*

Pseudocode:

    For every char in char* query
        if char is not isalpha() or isspace()
            error and ask for next query
    int wordCount = tokenizeQuery with char* query
    for every word in words
        print word and space
    if (first or last word is an and or or)
        error and ask for next query
    if (two operators are adjacent)
        error and ask for next query
    make a new counters with name countersUnion
    make an int index = 0
    while (index in char* words[] is not a NULL pointer)
        if (index in char* words[] is an operator)
            increment index
            continue (jump back to the beginning of the loop)
        make a new counters with name countersIntersection and set equal to current word's counters
        while (index + 1 in char* words[] is an and or a non-operator word)
            call intersectionQuery on countersIntersection and next non-operator word's counters
            increment index
        call unionQuery on countersUnion and countersIntersection
        delete countersIntersection
        increment index
    return countersUnion

### printResults

Given final counters_t* representing results of query, print them in decreasing order. Return void.

Pseudocode:

    if (result is empty)
        print that no documents match
    initialize struct maxNodePointer to zero and zero
    call counters_iterate on result, maxNodePointer, and updateMaxNode
    while (maxNodePointer's count is not equal to zero)
        call counters_iterate on result, maxNodePointer, and updateMaxNode
        print out that docID
        set maxNodePointer's count to zero

### updateMaxNode

Given maxNodePointer, key, and count for a docID, updates maxNodePointer. Returns void.

Pseudocode:

    (need struct countersNode that contains key and count ints)
    
    if (arg isn't null)
        set struct countersNode* maxNode = arg
        if (count > maxNode->count)
            set maxNode count to count and maxNode key to key

### tokenizeQuery

Given char* queryLine and char* words[], normalize words and generate an array of char* to each word (delimited with space). Returns int i (wordCount)

Pseudocode:

    initialize an array words of char* with size length of string / 2
    initialize char* word to char* line, and char* rest
    initialize int i to zero
    while (word is not a null character)
        while (word is not a letter)
            increment word
        set char* rest = char* word
        while (rest is a letter)
            increment rest
        set rest equal to null character
        normalize word
        insert word into array words
        increment rest
        set word equal to rest
        increment int i
    return i


### query

Do the real work of query, given command-line arguments, return void

Pseudocode:

	if (parseArgs with argc and argv[]) is false
        error and exit non-zero
    load index into queryIndex from indexFilename
    take stdin queries
        counters_t* resultCounters set to parseQuery with stdin line
        call printResults with resultCounters

### isOperator

Given a word, return true if that word is an operator

Pseudocode:

    call strcmp on that word and "and" and "or"
    if (either evaluates to zero)
        return true
    return false

### unionQuery

Given two counters, alter first one to represent union of both

Pseudocode:

    call counters_iterate on second counters, first counter, and updateUnion

### intersectionQuery

Given two counters, alter first one to represent intersection of both

Pseudocode:

    call counters_iterate on second counters, first counters, and updateIntersection

### updateUnion

Given first counters, second counters key, secound counters count, alter first one to update union of both

Pseudocode:

    initialize int firstcount to counters_get(first counters, key)
    if (firstcount is zero)
        counters_set(first counters, key, count)
    else
        counters_set(first counters, key, firstcount + count)

### updateIntersection

Given first counters, second counters key, secound counters count, alter first one to update intersection of both

Pseudocode:

    initialize int firstcount to counters_get(first counters, key)
    if (firstcount is not zero)
        initialize int min to firstcount
        if (count is less than firstcount)
            set min to count
        counters_set(first counters, key, count)

### updateCount

Given itemCount, key, count, increment count of items

Pseudocode:

    int* itemCount equal to arg
    if (key isn't zero && item isn't zero)
        increment itemCount

### getURL

Given docID and pageDirectory, getURL for that docID. Return URL.

Pseudocode:

    open file with that docID in pageDirectory
    return first line

### getMin

Given two integers, return smaller value.

Pseudocode:

    if (int1 is less than int2)
        return int1
    else if (int1 is greater than int2)
        return int2
    else
        return int1

## Function prototypes

### query

```c
void unionQuery(counters_t* firstCounters, counters_t* secondCounters);
void intersectionQuery(counters_t* firstCounters, counters_t* secondCounters);
void updateUnion(void* arg, const int key, const int count);
void updateIntersection(void* arg, const int key, const int count);
void updateMaxNode(void* arg, const int key, const int count);
char* getURL(int docID, char* pageDirectory);
void query(char* pageDirectory, char* indexFilename);
bool parseArgs(char* pageDirectory, char* indexFilename);
void printResults(counters_t* result, char* pageDirectory);
int tokenizeQuery(char* queryLine, char* words[]);
counters_t* parseQuery(char* queryLine, index_t* queryIndex);
bool isOperator(char* word);
int getMin(int int1, int int2);
int main(const int argc, char* argv[]);
```

## Error handling and recovery

Print errors to standard error and exit non-zero. For query errors, wait for next query.

## Testing plan

1. Test *querier* with various invalid arguments and various invalid queries.
2. Run *querier* on a variety of pageDirectories and indexFileNames.
3. Run *valgrind* on  *querier* to ensure no memory leaks or errors.