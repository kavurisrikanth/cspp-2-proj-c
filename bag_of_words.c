/*
  Implements the Bag of Words algorithm.
*/

#include "bag_of_words.h"

extern int mod;

float get_dot_product(int *hash_one, int *hash_two) {
  /*
    Calculates the dot product of two vectors, essentially.
    Inputs: hash_one, int array
            hash_two, int array
    Returns: ans, float, result of dot product
  */
  
  int i = 0;
  float ans = 0, len_one = 0, len_two = 0;

  for(i = 0; i < mod; i++) {
    // For each member of the hash,

    // Calculate the hash lengths.
    // Avoids an unnecessary extra iteration
    if(*(hash_one + i) != 0) {
      len_one += pow(*(hash_one + i), 2);
    }
    if(*(hash_two + i) != 0) {
      len_two += pow(*(hash_two + i), 2);
    }

    // If both hashes are not zero, meaning the same word
    // is present in both files, multiply their counts
    // and add the result to the dot product.
    if((*(hash_one + i) != 0) && (*(hash_two + i) != 0)) {
      ans += ((*(hash_one + i)) * (*(hash_two + i)));
    }
  }

  
  len_one = pow(len_one, 0.5);
  len_two = pow(len_two, 0.5);

  // Return
  return ans/(len_one * len_two);
}

float** bag_driver(struct file_data *files, int num_files) {
  /*
    "Drives" the Bag of words algorithm.
  */
  
  // Allocate an array of arrays of floats
  float **bag = (float**)allocate(num_files * sizeof(float*));
  int i = 0, j = 0;
  
  for(i = 0; i < num_files; i++) {
    // Allocate each array
    *(bag + i) = (float*)allocate(num_files * sizeof(float));
    for(j = 0; j < num_files; j++) {
      
      // Set the number to -1 if it's the same file, or if it's
      // an empty file
      if((i == j) ||
         ((files + i)->num_words == 0 || (files + j)->num_words == 0))
        *(*(bag + i) + j) = -1;
      else {
        // Calculate dot product and store the result
        // as a percentage
        *(*(bag + i) + j) = 100 * get_dot_product((files + i)->hash, (files + j)->hash);
      }
      
    }
  }

  return bag;
}
