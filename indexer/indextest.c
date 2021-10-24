/* 
Thomas Fenaroli
CS50
indextest.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "../common/index.h"

// main function
int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "error: invalid number of arguments, exiting non-zero\n");
        exit(1);
    }

    char* oldIndexFilename = argv[1];
    char* newIndexFilename = argv[2];

    index_t* index = index_load(oldIndexFilename);

    index_save(index, newIndexFilename);

    index_delete(index);

    return 0;
}