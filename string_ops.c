/*
String operations for the plagiarism project.
*/

#include "string_ops.h"
#include "memory.h"
#include <stdio.h>

char* degrammarify(char *str) {
    // Removes all the punctuation from str, converts it to lowercase
    // and returns the new string.

    char *new_str = NULL;

    if(str == NULL)
      return new_str;

    new_str = allocate(strlen(str));
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

    deallocate(str);
    return new_str;
}

char** split_into_words(char *str, int words) {
  /*
    Splits a string into an array of words
  */
  // printf("\nreceived string: %s\n", str);

  if(words == 0)
    return NULL;

  char **ans = (char**)allocate(words * sizeof(char*)), c;
  int i = 0, len = strlen(str), from = 0, j = 0;


  for(i = 0; i <= len; i++) {
    c = *(str + i);
    // printf("c = %c\n", c);
    if(c == '\0') {
      // printf("string terminating char\n");
      // printf("i = %d, j = %d, from = %d\n", i, j, from);
      *(ans + j) = (char*)allocate((i - from + 1) * sizeof(char));
      memcpy(*(ans + j), str + from, (i - from) * sizeof(char));
      *(*(ans + j) + i - from) = '\0';
      j++;
    }

    if(c == ' ') {
      *(ans + j) = (char*)allocate((i - from) * sizeof(char));
      memcpy(*(ans + j), str + from, (i - from) * sizeof(char));
      *(*(ans + j) + i - from) = '\0';
      from = i + 1;
      j++;
    }
  }

  // printf("String: %s\n", str);
  // printf("Word list: \n");
  // for(i = 0; i < words; i++)
  //   printf(" ^%s^ ", *(ans + i));
  // printf("\n");

  #if 0
  temp = strtok(str, " \0");
  while(temp != NULL) {
    *(ans + i) = (char*)calloc(1, (1 + strlen(temp)) * sizeof(char));
    strcpy(*(ans + i), temp);
    i++;
    temp = strtok(NULL, " \0");
  }
  #endif

  deallocate(str);
  return ans;
}

int num_words(char *str) {
  /*
    Returns the number of words in the string.
  */

  int ans = 0;

  if(str == NULL)
    return ans;

  int i = 0, len = strlen(str);
  char c;
  
  for(i = 0; i <= len; i++) {
    c = *(str + i);
    
    // The final \0
    if(c == '\0' || c == ' ')
      ans++;
  }

  return ans;
}

char* duplicate_string(char *str) {
  if(str == NULL)
    return NULL;
    
  return strdup(str);
}