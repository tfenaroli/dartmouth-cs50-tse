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
 5. *validateQuery*, which validates query arguments after they have been parsed
 6. *getURL*, which gets URL from a docID file
 7. *printResults*, which takes a counters object representing query results and scores, and prints them out in ranked order
 8. *intersectionQuery*, which makes a 'running product' (a counters object that represents the intersection of everything seen so far in the sequence)
 9. *unionQuery*, which makes a 'running sum' of andsequences
 10. *updateUnion*, which updates union
 11. *updateIntersection*, which updates intersection
 12. *updateMaxNode*, which updates maxNode
 13. *isOperator*, which returns true if input is an operator
 14. *getMin*, which returns minimum of two integers

And some helper modules that provide data structures:

 1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 2. *counters*, a module providing the data structure to map docID to score;

 note: iterate through the counters

### Pseudo code for logic/algorithmic flow

The querier will run as follows:

    main calls query, query loads index from indexFile into queryIndex index data structure, query calls parseArgs with argc and argv[] and returns bool, query takes stdin and calls parseQuery on query string and returns array of char* (clean query), query calls validateQuery with clean query and returns bool, query performs query with clean query on queryIndex using helper functions

### Major data structures

The key data structure is the *index*, mapping from *word* to *(docID, #occurrences)* pairs.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID. 

### Testing plan


1. Test *querier* with various invalid arguments and various invalid queries.
2. Run *querier* on a variety of pageDirectories and indexFileNames.
3. Run *valgrind* on  *querier* to ensure no memory leaks or errors.