/*
  All (?) the operations required for hashing.
*/

#include "hashing.h"

int mod = 10007;

unsigned long long apply_hash_to_word(char *word, int mod) {
  /*
    Applies a hash function to word.
  */
  // printf("Applying hash to: %s\n", word);
  int i = 0, len = strlen(word), power = 0;
  unsigned long long ans = 0;
  char c;


  for(i = 0; i < len; i++) {
    c = *(word + i);
    power = (int)pow(10, len - 1 - i);
    // printf("%c -> %d * %d -> %d\n", c, (int)c, power, (int)c * power);
    ans += ((int)c) * (power);
  }

  // printf("word: %s -> %d\n", word, ans % mod);

  return ans % mod;
}

int* apply_hash_to_word_list(char **word_list, int words) {
  /*
    Applies a hash function to a string, one word at a time.
  */

  int i = 0;
  unsigned long long pos = 0;//, mod = 10007;
  int *hash = (int*)allocate(mod * sizeof(int));
  // char **word_list;

  for(i = 0; i < words; i++) {
    pos = apply_hash_to_word(*(word_list + i), mod);
    *(hash + pos) += 1;
  }
  // printf("\n");

  #if 0
  word = strtok(str, " \0");

  while(word != NULL) {
    *(hash + apply_hash_to_word(word, mod)) += 1;
    word = strtok(NULL, " \0");
    i++;
  }
  // print_array()
  #endif



  // deallocate(str);
  return hash;
}
