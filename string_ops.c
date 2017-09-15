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

  // Validation
  if(str == NULL)
    return new_str;

  // Make a new string.
  new_str = allocate(strlen(str));
  int i = 0, j = 0, l = strlen(str);
  char c;

  for(i = 0; i < l; i++) {
    
    c = str[i];
    
    // If the character is a letter, a digit or a space,
    // then consider it. Otherwise, ignore.
    
    if((c >= 'a' && c <= 'z') ||
       (c >= 'A' && c <= 'Z') ||
       (c >= '0' && c <= '9') ||
       c == ' ' || c == '_') {
         if(c >= 'A' && c <= 'Z') {
           // Convert uppercase letters to lowercase
           new_str[j] = (char)(((int)c) | 32);
         }
         else {
           // Leave everything else as is
          new_str[j] = c;
         }
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

  // If there are no words, return NULL
  if(words == 0)
    return NULL;

  char **ans = (char**)allocate(words * sizeof(char*));
  
#if 0
  // Unused code.

  char c;
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
#endif


#if 1
  // Split the string into pieces using strtok. This destroys
  // the string, so send a duplicate of the string here.
  
  char *temp;
  int i = 0;
  
  temp = strtok(str, " \0");
  while(temp != NULL) {
    *(ans + i) = (char*)calloc(1, (1 + strlen(temp)) * sizeof(char));
    strcpy(*(ans + i), temp);
    i++;
    temp = strtok(NULL, " \0");
  }
#endif

  // Since the string is basically unusable, free it and return.
  deallocate(str);
  return ans;
}

int num_words(char *str) {
  /*
    Returns the number of words in the string.
  */

  int ans = 0;

  // Validation
  if(str == NULL)
    return ans;

  int i = 0, len = strlen(str);
  char c, d;
  
  for(i = 0; i <= len; i++) {
    
    // For every character
    c = *(str + i);
    
    // Check if it is a space or the \0 at the end.
    // If it is, then check the character JUST before it.
    // If that char is part of a valid word, then we just
    // crossed a word. So count it.
    if(c == '\0' || c == ' ') {
      if(i > 0) {
        d = *(str + i - 1);
        if((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z') ||
           (d >= '0' && d <= '9') || d == '_')
          ans++;
      }
    }

#if 0
    if(c == ' ') {
      if(i > 0) {
        d = *(str + i - 1);
        if((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z') ||
           (d >= '0' && d <= '9') || d == '_')
          ans++;
      }
    }
#endif
    
  }

  return ans;
}

char* duplicate_string(char *str) {
  /*
  Wrapper function to duplicate string.
  */
  if(str == NULL)
    return NULL;
    
  return strdup(str);
}