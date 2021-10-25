# CS50 TSE Querier
## Design Spec

The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

### User interface

The indexer's only interface with the user is on the command-line; it must always have two arguments.

```
querier pageDirectory indexFilename
```

### Inputs and outputs

**Input**:
the querier takes two command-line arguments (pageDirectory indexFilename), and uses both the generated index and the pageDirectory to respond to a query

**Output**:
if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
print the 'clean' query for user to see.
use the index to identify the set of documents that satisfy the query, as described below.
if the query is empty (no words), print nothing.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules;
 2. *query*, which calls other functions and performs query
 3. *parseArgs*, which validates command-line arguments;
 4. *parseQuery*, which parses and validates query arguments
 5. *generateScore*, which generates score for each word.
 6. *getURL*, which gets URL from a docID file.

And some helper modules that provide data structures:

 1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 2. *counters*, a module providing the data structure to map docID to score;

 iterate through the counters

### Pseudo code for logic/algorithmic flow

The indexer will run as follows:

    parse the command line, validate parameters, initialize other modules
    call indexBuild, with pageDirectory

where *indexBuild:*

      creates a new 'index' object
      loops over document ID numbers, counting from 1
        loads a webpage from the document file 'pageDirectory/id'
        if successful, 
          passes the webpage and docID to indexPage

where *indexPage:*

     steps through each word of the webpage,
       skips trivial words (less than length 3),
       normalizes the word (converts to lower case),
       looks up the word in the index,
         adding the word to the index if needed
       increments the count of occurrences of this word in this docID

### Major data structures

The key data structure is the *index*, mapping from *word* to *(docID, #occurrences)* pairs.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID. 

### Testing plan

*Unit testing*.  A program *indextest* will serve as a unit test for the *index* module; it reads an index file into the internal *index* data structure, then writes the index out to a new index file.

*Integration testing*.  The *indexer*, as a complete program, will be tested by building an index from a pageDirectory, and then the resulting index will be validated by running it through the *indextest* to ensure it can be loaded.

1. Test `indexer` with various invalid arguments.
	2. no arguments
	3. one argument
	4. three or more arguments
	5. invalid `pageDirectory` (non-existent path)
	5. invalid `pageDirectory` (not a crawler directory)
	6. invalid `indexFile` (non-existent path)
	7. invalid `indexFile` (read-only directory)
	7. invalid `indexFile` (existing, read-only file)
0. Run *indexer* on a variety of pageDirectories and use *indextest* as one means of validating the resulting index.
0. Run *valgrind* on both *indexer* and *indextest* to ensure no memory leaks or errors.