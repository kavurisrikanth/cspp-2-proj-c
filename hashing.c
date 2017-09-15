/*
  All (?) the operations required for hashing.
*/

#include "hashing.h"

// Arbitrary
int mod = 10007;

unsigned long long apply_hash_to_word(char *word, int mod) {
  /*
    Applies a hash function to word.
    Specifically, this hash function.
    Given a word, we scan each character, and the hash is:
    
    hash = ascii(word[n - 1]) * (10 ^ (0)) +
           ascii(word[n - 2]) * (10 ^ (1)) +
           .
           .
           .
           ascii(word[0]) * (10 ^ (n - 1))
           
           where n = strlen(word)
  */

  int i = 0, len = strlen(word), power = 0;
  char c;

  // To make sure huge words are covered
  unsigned long long ans = 0;

  // Applying the hash to the word
  for(i = 0; i < len; i++) {
    c = *(word + i);
    power = (int)pow(10, len - 1 - i);
    ans += ((int)c) * (power);
  }

  // Return
  return ans % mod;
}

int* apply_hash_to_word_list(char **word_list, int words) {
  /*
    Applies a hash function to a string, one word at a time.
  */

  // Validation
  if(words == 0)
    return NULL;

  int i = 0;
  unsigned long long pos = 0;
  int *hash = (int*)allocate(mod * sizeof(int));

  // Populate the hash array
  for(i = 0; i < words; i++) {
    pos = apply_hash_to_word(*(word_list + i), mod);
    *(hash + pos) += 1;
  }

  // Return
  return hash;
}
