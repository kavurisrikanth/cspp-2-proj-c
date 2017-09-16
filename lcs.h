/*
  Header file for LCS
*/
#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#include <math.h>
#include "string_ops.h"
#include "file_struct.h"
#include "memory.h"

#ifndef LCS_H
#define LCS_H

float get_lcs_length(struct file_data *one, struct file_data *two);
float** lcs_driver(struct file_data *files, int num_files);


// Unused code.
#if 0
int get_lcs_length(int* one, int len_one, int* two, int len_two);
#endif

// Unused code.
// This code returns the NUMBER of consecutive common words, not the
// length of them
#if 0
int get_lcs_length(int* one, int len_one, int* two, int len_two) {
  int i = 0, j = 0, ans = 0, match = 0;

  for(i = 0; i < len_one; i++) {
    for(j = 0; j < len_two; j++) {
      if(*(one + i) == *(two + j)) {
        match++;
      } else {
        if(match > ans) {
          ans = match;
        }
        match = 0;
      }
    }
  }

  return ans;
}
#endif

#endif