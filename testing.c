/*
 * testing.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include "testing.h"

int main(int argc, char const *argv[]) {
  /* code */

  if(argc != 2) {
    fprintf(stderr, "Wrong number of args!\n");
    fprintf(stderr, "Usage: ./testing <file name>\n");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if(!fp) {
    fprintf(stderr, "Couldn't open file: %s\n", argv[1]);
    return 1;
  }

  char *str_one = (char*)allocate(1024),
       *str_two = (char*)calloc(1, 1024 * sizeof(char)),
       *temp;

  fgets(str_one, 1024, fp);
  fgets(str_two, 1024, fp);

  if((temp = strchr(str_one, '\n')) != NULL)
    *temp = '\0';

  printf("str one: %s, str two: %s\n\n\n", str_one, str_two);

  get_lcs_length(str_one, str_two);

  printf("\n\nword: %d, apple: %d, word: %d\n", apply_hash_to_word("word", 10007),
                                            apply_hash_to_word("apple", 10007),
                                            apply_hash_to_word("word", 10007));

  free(str_one);
  free(str_two);

  return 0;
}


#if 0
int main(void) {

	//int i = 0, size = 10, size_2 = 20;

	int size = 10;
	char *arr = (char*)allocate(size);

	printf("File path...");
	char* str = (char*)allocate(100);

	str = strcpy(str, "/home/ubuntu/workspace/msit/cspp2/proj_c/abc.txt");

	/*
	for(i = 0; i < size; i++)
		*(arr + i) = 10;

	for(i = 0; i < size; i++)
		printf("%d ", *(arr + i));
	printf("\n");


	arr = resize(arr, size, size_2);
	for(i = 0; i < size_2; i++)
		printf("%d ", *(arr + i));
	printf("\n");
	*/
	printf("path: %s\n", str);
	char* temp = get_string_from_file(str);
	printf("string: %s\n", temp);

	char* new_str = degrammarify(temp);
	printf("modified string: %s\n", new_str);

	deallocate(temp);
	deallocate(new_str);
	deallocate(str);
	deallocate(arr);

	return 0;
}
#endif
