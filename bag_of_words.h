/*
Header file for Bag of Words
*/

#include <stdio.h>
#include <math.h>
#include "memory.h"
#include "file_struct.h"

#ifndef BAG_OF_WORDS_H
#define BAG_OF_WORDS_H

// FUNCTION DECLARATIONS
float get_dot_product(int *hash_one, int *hash_two);
float** bag_driver(struct file_data *files, int num_files);

#endif