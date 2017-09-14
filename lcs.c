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

  int i = 0, j = 0, ans = 0, iter_one = 0, iter_two = 0,
      len_one = strlen(one), len_two = strlen(two),
      words_one = file_one->num_words, words_two = file_two->num_words;
  char **hash_one, **hash_two, *temp;

  // hash_one = apply_hash_to_string(one, words_one);
  // hash_two = apply_hash_to_string(two, words_two);

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
  // ans = get_lcs_length(hash_one, words_one, hash_two, words_two);

  // print first array of strings.
  // for(i = 0; i < words_one; i++)
  //   printf("%sbla ", *(hash_one + i));
  // printf("\n");

  // print second array of strings.
  // for(i = 0; i < words_two; i++)
  //   printf("%s ", *(hash_two + i));
  // printf("\n");

  int matches = 0, spaces = 0, total_len = 0;

  // look at each word in the first file
  while(i < file_one->num_words) {
    // for each word in the second file
    j = 0;
    while(j < file_two->num_words) {
      // if there is a match, then check the next words until there isn't
      // a match
      // printf("comparing: \"%s\" at %d with \"%s\" at %d\n",
      //              (*file_one).words[i], i,
      //              (*file_two).words[j], j);
      if(strcmp((*file_one).words[i], (*file_two).words[j]) == 0) {
        matches = 1; // since one word has matched
        total_len += strlen((*file_two).words[j]);
        iter_one = i + 1;
        iter_two = j + 1;
        while(iter_one < file_one->num_words &&
              iter_two < file_two->num_words &&
              (strcmp((*file_one).words[iter_one],
                     (*file_two).words[iter_two]) == 0)) {

                // printf("matched: \"%s\" and \"%s\"\n", (*file_one).words[iter_one],
                //              (*file_two).words[iter_two]);

          // spaces++;
          matches++;
          // printf("length of \"%s\": %lu\n", (*file_two).words[iter_two],
          //                                strlen((*file_two).words[iter_two]));
          total_len += strlen((*file_two).words[iter_two]);
          iter_one++;
          iter_two++;
          // printf("iters: %d, %d; limits: %d, %d\n", iter_one,
          //         iter_two, file_one->num_words, file_two->num_words);
        }
        // printf("Exited compare loop\n");

        // record changes
        spaces = matches - 1;
        total_len += spaces;
        if(total_len > ans)
          ans = total_len;
        matches = 0;
        total_len = 0;
        spaces = 0;

        // printf("after recording, ans = %d\n", ans);
      }

      // record changes
      spaces = matches - 1;
      total_len += spaces;
      if(total_len > ans)
        ans = total_len;
      matches = 0;
      total_len = 0;
      spaces = 0;

      // printf("after recording 2, ans = %d\n", ans);
      j++;
    }

    // printf("j loop done\n");
    // record changes
    spaces = matches - 1;
    total_len += spaces;
    if(total_len > ans)
      ans = total_len;
    matches = 0;
    total_len = 0;
    spaces = 0;

    // printf("after recording 3, ans = %d\n", ans);
    i++;
  }
  // printf("i loop done\n");

#if 0
  for(i = 0; i < file_one->num_words; i++) {
    for(j = 0; j < file_two->num_words; j++) {

      // printf("words: %s, %s\n", (*file_one).words[i], (*file_two).words[j]);
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
#endif
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
    *(lcs + i) = (float*)allocate(num_files * sizeof(float));
    for(j = 0; j < num_files; j++) {
      if(i == j)
        *(*(lcs + i) + j) = -1;
      else
        *(*(lcs + i) + j) = get_lcs_length((files + i), (files + j));
    }
  }

  return lcs;
}
