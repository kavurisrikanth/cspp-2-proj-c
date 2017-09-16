/*
    Header file for Hashing.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "memory.h"

#ifndef HASHING_H_
#define HASHING_H_

unsigned long long apply_hash_to_word(char *word, int mod);
int* apply_hash_to_word_list(char **word_list, int words);

#endif