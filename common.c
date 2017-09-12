#include "common.h"

void print_array(int *arr, int len) {
  int i = 0;
  printf("Array: ");
  for(i = 0; i < len; i++)
    printf("%d ", *(arr + i));
  printf("\n");
}
