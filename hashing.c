/*
  All (?) the operations required for hashing.
*/

#include "hashing.h"

int apply_hash_to_word(char *word, int mod) {
  /*
    Applies a hash function to word.
  */
  printf("Applying hash to: %s\n", word);
  int i = 0, len = strlen(word), ans = 0;

  for(i = 0; i < len; i++) {
    ans += ((int)*(word + i)) * ((int)pow(10, len - 1));
  }

  return ans % mod;
}

int* apply_hash_to_string(char *str, int words) {
  /*
    Applies a hash function to a string, one word at a time.
  */

  int i = 0, mod = 10007;
  int *hash = (int*)calloc(1, (words) * sizeof(int));
  char *word, *temp;

  word = strtok(str, " \0");

  while(word != NULL) {

    *(hash + i) = apply_hash_to_word(word, mod);
    word = strtok(NULL, " \0");
    i++;
  }
  // print_array()

  return hash;
}
