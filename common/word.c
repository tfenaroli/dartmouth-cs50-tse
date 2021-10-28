/* 
Thomas Fenaroli
CS50
word.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// caller must free result (see word.h for description)
char* normalizeWord(char* word) {
    size_t len = strlen(word);
    char* result = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)word[i]);
    }
    return result;
}