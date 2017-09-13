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

void print_vector(int *arr, int len) {
  int i = 0;
  printf("\nCount vector:\n");
  for(i = 0; i < len; i++) {
    if(*(arr + i) > 0) {
      printf("%d -> %d\n", i, *(arr + i));
    }
  }
  printf("\n");
}
