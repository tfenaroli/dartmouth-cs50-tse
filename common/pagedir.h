/* 
Thomas Fenaroli
CS50
pagedir.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"

/* initializes pageDirectory
takes argument: pageDirectory
returns boolean indiciating success or failure
*/
bool pagedir_init(const char* pageDirectory);

/* saves file to pageDirectory
takes arguments: page, pageDirectory, docID
returns void
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/* validates pageDirectory
takes argument: pageDirectory
returns true if validates
*/
bool pagedir_validatedir(const char* pageDirectory);

/* loads page from file
takes argument: file
returns webpage_t*
*/
webpage_t* pagedir_load(FILE* fp);