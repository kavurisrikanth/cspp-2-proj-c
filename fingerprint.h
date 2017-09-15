#include "memory.h"
#include "file_struct.h"
#include "hashing.h"

float** fingerprint_driver(struct file_data *files, int num_files);
float compare_fingerprints(struct file_data *file_one, struct file_data *file_two);
void construct_fingerprint(struct file_data *file);
unsigned long long* make_kgrams(char *str, int k);
char* smoosh(char *str);