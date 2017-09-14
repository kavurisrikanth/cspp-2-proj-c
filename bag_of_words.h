#include <stdio.h>
#include <math.h>
#include "memory.h"
#include "file_struct.h"

// extern struct file_data;

float get_dot_product(int *hash_one, int *hash_two);
float** bag_driver(struct file_data *files, int num_files);
