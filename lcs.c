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

#if 0
// Unused code
  char *one = file_one->string,
       *two = file_two->string;
       
  if(one == NULL || two == NULL)
    return -1;

  if(strlen(one) == 0 || strlen(two) == 0)
    return -1;
#endif

  int i = 0, j = 0, ans = 0, iter_one = 0, iter_two = 0,
      len_one = 0, len_two = 0;

#if 0      
  // Unused code
  int words_one = file_one->num_words,
      words_two = file_two->num_words;
  char **hash_one, **hash_two, *temp;

  hash_one = apply_hash_to_string(one, words_one);
  hash_two = apply_hash_to_string(two, words_two);


  if(file_one->words == NULL) {
    temp = (char*)allocate((1 + len_one) * sizeof(char));
    strcpy(temp, one);
    hash_one = split_into_words(strdup(temp), words_one);
    deallocate(temp);
    file_one->words = hash_one;
  }

  if(file_two->words == NULL) {
    temp = (char*)allocate((1 + len_two) * sizeof(char));
    strcpy(temp, two);
    hash_two = split_into_words(strdup(temp), words_two);
    deallocate(temp);
    file_two->words = hash_two;
  }
#endif

  // Calculate lengths of the file, meaning the sum of the
  // lengths of each word
  i = 0;
  while(i < file_one->num_words) {
    len_one += strlen((file_one)->words[i]);
    i++;
  }
  // Including spaces, since there's one space between
  // two words
  len_one += (file_one->num_words - 1);

  i = 0;
  while(i < file_two->num_words) {
    len_two += strlen((file_two)->words[i]);
    i++;
  }
  len_two += (file_two->num_words - 1);


  int matches = 0, spaces = 0, total_len = 0;

  i = 0;
  // look at each word in the first file
  while(i < file_one->num_words) {
    // for each word in the second file
    j = 0;

    while(j < file_two->num_words) {
      // if there is a match, then check the next words until there isn't
      // a match

      if(strcmp((*file_one).words[i], (*file_two).words[j]) == 0) {
        matches = 1; // since one word has matched

        total_len += strlen((*file_two).words[j]);
        iter_one = i + 1;
        iter_two = j + 1;
        
        // Keep going until either the chain of consecutive
        // matches is broken, or until we reach the end of
        // one of the arrays
        while(iter_one < file_one->num_words &&
              iter_two < file_two->num_words &&
              (strcmp((*file_one).words[iter_one],
                     (*file_two).words[iter_two]) == 0)) {

          matches++;
          total_len += strlen((*file_two).words[iter_two]);
          iter_one++;
          iter_two++;
        }

        // record changes
        spaces = matches - 1;
        total_len += spaces;
        if(total_len > ans)
          ans = total_len;
        matches = 0;
        total_len = 0;
        spaces = 0;

      }

      // record changes
      spaces = matches - 1;
      total_len += spaces;
      if(total_len > ans)
        ans = total_len;
      matches = 0;
      total_len = 0;
      spaces = 0;

      j++;
    }

    // record changes
    spaces = matches - 1;
    total_len += spaces;
    if(total_len > ans)
      ans = total_len;
    matches = 0;
    total_len = 0;
    spaces = 0;

    i++;
  }

#if 0
  // Unused code
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
  for(i = 0; i < words_one; i++)
    free(*(hash_one + i));
  free(hash_one);

  for(i = 0; i < words_two; i++)
    free(*(hash_two + i));
  free(hash_two);
#endif

  // Return
  return (float)(ans * 2)/(len_one + len_two);
}

float** lcs_driver(struct file_data *files, int num_files) {
  /*
    "Drives" the LCS algorithm
  */
  
  // Allocate an array of arrays of floats
  int i = 0, j = 0;
  float **lcs = (float**)allocate(num_files * sizeof(float*));

  for(i = 0; i < num_files; i++) {
    
    // Allocate array of floats
    *(lcs + i) = (float*)allocate(num_files * sizeof(float));
    for(j = 0; j < num_files; j++) {
      
      // Setting the value to -1 if either it's the same file
      // or an empty file
      if((i == j) ||
         ((files + i)->string == NULL || (files + j)->string == NULL))
        *(*(lcs + i) + j) = -1;
      else
        *(*(lcs + i) + j) = 100 * get_lcs_length((files + i), (files + j));
    }
  }

  return lcs;
}
