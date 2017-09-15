/*
  File structure used throughout the project.
*/

#ifndef _FILE_STRUCT_H
#define _FILE_STRUCT_H

typedef struct file_data {
  char *f_name;
  char *string;
  int *hash;
  int num_words;
  char **words;
  unsigned long long *fp;
  int fp_len;
  int kgram_len;
} file_data;
extern file_data *files;

#endif