/*
    Header file for String operations
*/

#include <string.h>

#ifndef STRING_OPS_H
#define STRING_OPS_H

char* degrammarify(char *str);
char** split_into_words(char *str, int words);
int num_words(char *str);
char* duplicate_string(char *str);

#endif