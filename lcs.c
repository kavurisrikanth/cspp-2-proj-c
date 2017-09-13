/*
  Find the longest common (contiguous) subsequence between two given strings.
  This means, since the strings are sentences, which are made of words, we find
  the longest set of words that appears in both sentences.

  Python algorithm:
  1. For each word in string one,   O(n)
    1. Check if the word is present in string two. O(n)
    2. If it is, then remember its index in both strings.
  2. For each remembered index, we have one matched word. So, check how many
  words AFTER that index match in both strings.
  3. The largest number of matched words is the LCS.

  C algorithm:
  This algo needs to split a single sentence into an array of words, and then
  apply the Python algo on that array.
*/

#include "lcs.h"

/* FUNCTION DECLARATIONS */

float get_lcs_length(struct file_data *file_one, struct file_data *file_two) {
  /*
    Returns the length of the longest common subsequence between two strings.
  */

  char *one = file_one->string,
       *two = file_two->string;

  if(strlen(one) == 0 || strlen(two) == 0)
    return 0;

  int i = 0, j = 0, ans = 0,
      len_one = strlen(one), len_two = strlen(two),
      words_one = file_one->num_words, words_two = file_two->num_words;
  char **hash_one, **hash_two;

  // hash_one = apply_hash_to_string(one, words_one);
  // hash_two = apply_hash_to_string(two, words_two);

  char *temp = (char*)allocate((1 + len_one) * sizeof(char));
  strcpy(temp, one);
  hash_one = split_into_words(temp, words_one);
  deallocate(temp);

  temp = (char*)allocate((1 + len_two) * sizeof(char));
  strcpy(temp, two);
  hash_two = split_into_words(temp, words_two);
  deallocate(temp);
  // ans = get_lcs_length(hash_one, words_one, hash_two, words_two);

  // print first array of strings.
  for(i = 0; i < words_one; i++)
    printf("%s ", *(hash_one + i));
  printf("\n");

  // print second array of strings.
  for(i = 0; i < words_two; i++)
    printf("%s ", *(hash_two + i));
  printf("\n");

  file_one->words = hash_one;
  file_two->words = hash_two;

  int matches = 0, spaces = 0, total_len = 0;

  for(i = 0; i < file_one->num_words; i++) {
    for(j = 0; j < file_two->num_words; j++) {

      // Compare word at i to each word in second list
      if(strcmp((*file_one).words[i], (*file_two).words[j]) == 0) {
        matches++;
        total_len += strlen((*file_two).words[j]);
        // spaces++;
      } else {
        spaces = matches - 1;
        total_len += spaces;
        if(total_len > ans)
          ans = total_len;
        matches = 0;
        total_len = 0;
        spaces = 0;
      }

    }
  }

  #if 0
  for(i = 0; i < words_one; i++)
    free(*(hash_one + i));
  free(hash_one);

  for(i = 0; i < words_two; i++)
    free(*(hash_two + i));
  free(hash_two);
  #endif

  return (float)(ans * 2)/(len_one + len_two);
}

float** lcs_driver(struct file_data *files, int num_files) {
  int i = 0, j = 0;
  float **lcs = (float**)allocate(num_files * sizeof(float*));

  for(i = 0; i < num_files; i++) {
    for(j = 0; j < num_files; j++) {
      if(i == j)
        *(*(lcs + i) + j) = -1;
      else
        *(*(lcs + i) + j) = get_lcs_length((files + i), (files + j));
    }
  }

  return lcs;
}
