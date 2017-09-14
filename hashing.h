#include <stdio.h>
#include <string.h>
#include <math.h>
#include "memory.h"

unsigned long long apply_hash_to_word(char *word, int mod);
int* apply_hash_to_word_list(char **word_list, int words);
