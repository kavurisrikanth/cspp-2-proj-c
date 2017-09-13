/*
 * testing.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include "testing.h"
#include "common.h"

struct file_data {
  char *f_name;
  char *string;
  int *hash;
  int num_words;
};

int main(int argc, char const *argv[]) {
  /* code */

  if(argc != 2) {
    fprintf(stderr, "Wrong number of args!\n");
    fprintf(stderr, "Usage: ./testing <directory>\n");
    return 1;
  }

  char *temp,
       *abs_path = realpath((char*)argv[1], NULL),
       *str;

  printf("path: %s\n", (char*)argv[1]);
  printf("absolute path: %s\n", abs_path);

  int num_files = 0, i = 0;
  char **file_names = get_all_files_in_dir((char*)argv[1], &num_files);
  // char **strings = (char**)allocate((num_files) * sizeof(char*));

  struct file_data *files = (struct file_data *)allocate(num_files * sizeof(struct file_data));

  // Open the file, read its contents, degrammarify them, and arrange them
  // into a single string.
  for(i = 0; i < num_files; i++) {
    str = strdup(abs_path);

    temp = (char*)allocate((2 + strlen(str) + strlen(*(file_names + i))) * sizeof(char));
    strcpy(temp, strcat(strcat(str, "/"), *(file_names + i)));
    printf("\n%s is a text file!\n", temp);

    (files + i)->f_name = (char*)allocate((1 + strlen(temp)) * sizeof(char));
    strcpy((files + i)->f_name, temp);

    (files + i)->string = degrammarify(get_string_from_file(temp));
    printf("\nstrings: %s *** %s\n", (files + i)->string, degrammarify(get_string_from_file(temp)));

    (files + i)->num_words = num_words((files + i)->string);
    (files + i)->hash = apply_hash_to_string(strdup((files + i)->string), (files + i)->num_words);
    printf("\n--------------strings: %s\n", (files + i)->string);
    deallocate(temp);
    deallocate(str);
    printf("Dealloacted!\n");
  }

  // For each string, do bag of words, LCS, and fingerprinting
  printf("\n");
  for(i = 0; i < num_files; i++) {
    printf("File details:\n");
    printf("File name: %s\n", (files + i)->f_name);
    printf("String: %s\n", (files + i)->string);

    // print_string((files + i)->string);
    printf("Number of words: %d\n", (files + i)->num_words);
    printf("Hash: ");
    print_array((files + i)->hash, (files + i)-> num_words);
    printf("\n");
    // printf("string for file %d: %s\n", i, *(strings + i));
  }

  printf("\n\nword: %d, apple: %d, word: %d\n", apply_hash_to_word("word", 10007),
                                            apply_hash_to_word("apple", 10007),
                                            apply_hash_to_word("word", 10007));

  for(i = 0; i < num_files; i++) {
    deallocate((files + i)->f_name);
    deallocate((files + i)->string);
    deallocate((files + i)->hash);
  }
  deallocate(files);
  // deallocate(strings);
  // deallocate(str_one);
  // deallocate(str_two);

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
