/*
String operations for the plagiarism project.
*/

#include "string_ops.h"
#include "memory.h"

char* degrammarify(char *str) {
    // Removes all the punctuation from str, converts it to lowercase
    // and returns the new string.

    char *new_str = allocate(strlen(str));
    int i = 0, j = 0, l = strlen(str);

    // printf("string len: %d\n", l);

    for(i = 0; i < l; i++) {
        if((str[i] >= 'a' && str[i] <= 'z') ||
           (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ') {
               if(str[i] != ' ') {
                   new_str[j] = (char)(((int)str[i]) | 32);
                //   printf("%c ", new_str[j]);
               }
               else
                   new_str[j] = str[i];
                j++;
           }
    }

    return new_str;
}

char** split_into_words(char *str, int words) {
  /*
    Splits a string into an array of words
  */
  char *temp,
       **ans = (char**)calloc(1, words * sizeof(char*));
  temp = strtok(str, " \0");
  while(temp != NULL) {
    *ans = (char*)calloc(1, (1 + strlen(temp)) * sizeof(char));
    strcpy(*(ans), temp);
    temp = strtok(NULL, " \0");
  }

  return ans;
}

int num_words(char *str) {
  /*
    Returns the number of words in the string.
  */

  int ans = 0, i = 0, len = strlen(str);
  for(i = 0; i <= len; i++) {

    // The final \0
    if(*(str + i) == '\0' || *(str + i) == ' ')
      ans++;
  }

  return ans;
}
