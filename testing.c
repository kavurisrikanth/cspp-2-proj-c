/*
 * testing.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include "testing.h"

extern int mod;



int main(int argc, char const *argv[]) {
  /* code */

  // Validation
  if(argc != 2) {
    fprintf(stderr, "Wrong number of args!\n");
    fprintf(stderr, "Usage: ./testing <directory>\n");
    return 1;
  }

  char *temp,
       *abs_path = realpath((char*)argv[1], NULL),
       *str;

  // printf("path: %s\n", (char*)argv[1]);
  // printf("absolute path: %s\n", abs_path);

  int num_files = 0, i = 0, j = 0;
  char **file_names = get_all_files_in_dir((char*)argv[1], &num_files);
  // char **strings = (char**)allocate((num_files) * sizeof(char*));

  // Validation
  if(num_files == 0) {
    printf("No text files found at location: %s\n", abs_path);
    deallocate(abs_path);
    deallocate(file_names);
    return 0;
  }
  
  struct file_data *files = (struct file_data *)allocate(num_files * sizeof(struct file_data));

  // Open the file, read its contents, degrammarify them, and arrange them
  // into a single string.
  for(i = 0; i < num_files; i++) {
    
    // Get the absolute path of the directory
    str = (char*)allocate((1 + strlen(abs_path)) * sizeof(char));
    strcpy(str, abs_path);
    temp = (char*)allocate((2 + strlen(str) + strlen(*(file_names + i))) * sizeof(char));
    strcpy(temp, strcat(strcat(str, "/"), *(file_names + i)));

    // Record the name
    (files + i)->f_name = (char*)allocate((1 + strlen(temp)) * sizeof(char));
    strcpy((files + i)->f_name, temp);

    // and the degrammarified string
    (files + i)->string = degrammarify(get_string_from_file(temp));
    
    // and the words array
    (files + i)->num_words = num_words((files + i)->string);
    (files + i)->words = split_into_words(duplicate_string((files + i)->string), (files + i)->num_words);

    // convert the words into a hash.
    // required for Bag of Words.
    (files + i)->hash = apply_hash_to_word_list((files + i)->words, (files + i)->num_words);

    // Deallocate to avoid memory leaks
    deallocate(temp);
    deallocate(str);
  }

  
#if 0
  // For each file, print out its details.
  // For debugging.
  printf("\n");
  for(i = 0; i < num_files; i++) {
    printf("File details:\n");
    printf("File name: %s\n", (files + i)->f_name);
    printf("String: %s\n", (files + i)->string);

    printf("Number of words: %d\n", (files + i)->num_words);
    printf("\n");
  }

#endif

  FILE *logfile = create_log_file(abs_path);

  // Print out file IDs and names for the user
  printf("\n\nFYI.\nfile # -> file name\n");
  for(i = 0; i < num_files; i++) {
    printf("%d -> %s\n", i, (files + i)->f_name);
  }

  fprintf(logfile, "\n\nFYI.\nfile # -> file name\n");
  for(i = 0; i < num_files; i++) {
    fprintf(logfile, "%d -> %s\n", i, (files + i)->f_name);
  }

  // Bag of Words
  float **bag = bag_driver(files, num_files);

  printf("\nBag of words:\n");
  printf(" files ");
  for(i = 0; i < num_files; i++)
    printf("%7d", i);
  printf("\n");

  fprintf(logfile, "\nBag of words:\n");
  fprintf(logfile, " files ");
  for(i = 0; i < num_files; i++)
    fprintf(logfile, "%7d", i);
  fprintf(logfile, "\n");


  for(i = 0; i < num_files; i++) {
    printf("% 6d    ", i);
    for(j = 0; j < num_files; j++)
      printf("%6.3f ", bag[i][j]);
    printf("\n");
  }

  for(i = 0; i < num_files; i++) {
    fprintf(logfile, "% 6d    ", i);
    for(j = 0; j < num_files; j++)
      fprintf(logfile, "%6.3f ", bag[i][j]);
    fprintf(logfile, "\n");
  }

  // LCS
  float **lcs = lcs_driver(files, num_files);

  printf("\nLongest Common Subsequence:\n");
  printf(" files ");
  for(i = 0; i < num_files; i++)
    printf("%7d", i);
  printf("\n");

  fprintf(logfile, "\nLongest Common Subsequence:\n");
  fprintf(logfile, " files ");
  for(i = 0; i < num_files; i++)
    fprintf(logfile, "%7d", i);
  fprintf(logfile, "\n");
  

  for(i = 0; i < num_files; i++) {
    printf("% 6d    ", i);
    for(j = 0; j < num_files; j++)
      printf("%6.3f ", lcs[i][j]);
    printf("\n");
  }

  for(i = 0; i < num_files; i++) {
    fprintf(logfile, "% 6d    ", i);
    for(j = 0; j < num_files; j++)
      fprintf(logfile, "%6.3f ", lcs[i][j]);
    fprintf(logfile, "\n");
  }

  // Deallocate and return
  for(i = 0; i < num_files; i++) {
    deallocate(*(bag + i));
    deallocate(*(lcs + i));
    
    deallocate((files + i)->f_name);
    deallocate((files + i)->string);
    deallocate((files + i)->hash);
    
    deallocate(*(file_names + i));

    for(j = 0; j < ((files + i)->num_words); j++) {
      deallocate((*(files+i)).words[j]);
    }
    deallocate((files+i)->words);
  }
  deallocate(bag);
  deallocate(lcs);
  deallocate(files);
  deallocate(file_names);
  deallocate(abs_path);

  fclose(logfile);

  return 0;
}