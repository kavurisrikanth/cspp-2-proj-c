/*
Source code for fingerprinting.
*/

#include "fingerprint.h"

void construct_fingerprint(struct file_data *file) {
    /*
    To construct a fingerprint for a file, we do the following:
    1. Smoosh the file string, meaning remove spaces
    2. Construct k-grams
    3. Apply hash to every k-gram
    4. Pick the hashes that are 0 mod p
    5. The picked hashes are the fingerprint of the file
    */
    
    int k = 5, p = k + 1, i = 0, j = 0;
    char *str = smoosh(file->string);
    unsigned long long *kgram = make_kgrams(str, k);
    file->kgram_len = strlen(str) - k + 1;
    
    unsigned long long *fp = (unsigned long long*)allocate((1 + file->kgram_len/p) * sizeof(unsigned long long));
    
    for(i = 0; i < file->kgram_len; i++) {
        if(i % p == 0) {
            *(fp + j) = *(kgram + i);
            j++;
        }
    }
    
    file->fp = fp;
    file->fp_len = 1 + file->kgram_len/p;

    deallocate(kgram);
    deallocate(str);
}

unsigned long long* make_kgrams(char *str, int k) {
    /*
    Creates k-grams for a (smooshed) string.
    */
    int i = 0, len = strlen(str), mod = 10007;
    unsigned long long *ans = (unsigned long long*)allocate((len - k + 1) * sizeof(unsigned long long));
    char *gram = (char*)allocate((1 + k) * sizeof(char));
    
    for(i = 0; i <= len - k; i++) {
        memset(gram, 0, (1 + k) * sizeof(char));
        memcpy(gram, str + i, (k) * sizeof(char));
        // printf("gram: %s\n", gram);
        *(ans + i) = apply_hash_to_word(gram, mod);
    }
    
    deallocate(gram);
    // deallocate(str);
    return ans;
}

char* smoosh(char *str) {
    /*
    Removes all spaces from str and returns the new string
    */
    
    int i = 0, j = 0, len = strlen(str);
    char *ans = (char*)allocate((1 + len) * sizeof(char)),
         c;
    
    for(i = 0; i < len; i++) {
        c = *(str + i);
        if(c != ' ') {
            *(ans + j) = c;
            j++;
        }
    }
    *(ans + j) = '\0';
    
    return ans;
}

float compare_fingerprints(struct file_data *file_one, struct file_data *file_two) {
    float ans = 0;
    unsigned long long *fp_one = file_one->fp,
                        *fp_two = file_two->fp;
        
    int i = 0, j = 0, num_matches = 0;
    
    // Check for matching fingerprints
    for(i = 0; i < file_one->fp_len; i++) {
        for(j = 0; j < file_two->fp_len; j++) {
            if(*(fp_one + i) == *(fp_two + j))
                num_matches++;
        }
    }
    
    ans = (float)(2 * num_matches)/(file_one->kgram_len + file_two->kgram_len);
    
    return ans;
}

float** fingerprint_driver(struct file_data *files, int num_files) {
    /*
    "Drives" the fingerprinting algorithm
  */
  
  // Allocate an array of arrays of floats
  int i = 0, j = 0;
  float **fingers = (float**)allocate(num_files * sizeof(float*));

    // Construct fingerprints for files
    for(i = 0; i < num_files; i++) {
        if((files + i)->string != NULL)
            construct_fingerprint(files + i);
    }

    // Compare fingerprints
  for(i = 0; i < num_files; i++) {
    
    // Allocate array of floats
    *(fingers + i) = (float*)allocate(num_files * sizeof(float));
    for(j = 0; j < num_files; j++) {
      
      // Setting the value to -1 if either it's the same file
      // or an empty file
      if((i == j) ||
         ((files + i)->string == NULL || (files + j)->string == NULL))
        *(*(fingers + i) + j) = -1;
      else
        *(*(fingers + i) + j) = 100 * compare_fingerprints((files + i), (files + j));
    }
  }

  return fingers;
}