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

int get_lcs_length(char *one, char* two) {
  /*
    Returns the length of the longest common subsequence between two strings.
  */

  if(strlen(one) == 0 || strlen(two) == 0)
    return 0;

  int i = 0, j = 0, ans = 0,
      len_one = strlen(one), len_two = strlen(two),
      words_one = num_words(one), words_two = num_words(two);
  char **hash_one, **hash_two;

  // hash_one = apply_hash_to_string(one, words_one);
  // hash_two = apply_hash_to_string(two, words_two);

  char *temp = (char*)calloc(1, (1 + len_one) * sizeof(char));
  strcpy(temp, one);
  hash_one = split_into_words(temp, words_one);
  free(temp);

  temp = (char*)calloc(1, (1 + len_two) * sizeof(char));
  strcpy(temp, two);
  hash_two = split_into_words(temp, words_two);
  free(temp);
  // ans = get_lcs_length(hash_one, words_one, hash_two, words_two);

  // print_array(hash_one, words_one);
  // print_array(hash_two, words_two);

  for(i = 0; i < words_one; i++)
    free(*(hash_one + i));
  free(hash_one);

  for(i = 0; i < words_two; i++)
    free(*(hash_two + i));
  free(hash_two);

  return ans;
}
