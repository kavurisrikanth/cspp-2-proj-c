#include "common.h"

void print_array(int *arr, int len) {
  int i = 0;
  printf("Array: ");
  for(i = 0; i < len; i++)
    printf("%d ", *(arr + i));
  printf("\n");
}

void print_string(char *str) {
  int i = 0;
  char c;

  while((c = *(str + i)) != '\0') {
    putchar(c);
    i++;
  }
}
