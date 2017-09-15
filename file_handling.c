/*
 * file_handling.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */


#include "memory.h"
#include "file_handling.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

char** get_all_files_in_dir(char *path, int *files_count) {
	/*
		Scans the given directory, and returns the names of all
		the text files in the directory.
	*/

	DIR *dir;
	struct dirent *d;
	char *extn, **files = NULL;
	int i = 0, buffer = 10, capacity = 10;

	// To keep track of the number, since we're returning
	// an array of strings.
	*files_count = 0;

	dir = opendir(path);
	if(dir) {
		// Valid directory.
		files = (char**)allocate(capacity * sizeof(char*));
		while((d = readdir(dir)) != NULL) {
			// Check file extension
			extn = strchr(d->d_name, '.');
			if(extn) {
				// If there is an extension, check if it is .txt
				if(strcmp(extn, ".txt") == 0) {
					// Text file, so include it.
					// strdup means the memory will need to be
					// deallocated.
					*(files + i) = strdup(d->d_name);
					i++;
					(*files_count)++;
					buffer--;
					if(buffer <= 2) {
						// A bit of memory resizing
						files = resize(files, capacity, capacity * 2);
						capacity *= 2;
						buffer = capacity - *files_count;
					}
				}
			}
		}
		closedir(dir);
	} else {
		fprintf(stderr, "Invalid directory: %s\n", path);
	}

	return files;
}

FILE* create_log_file(char *path) {
	/*
	 * Creates a log file at path, and returns the file
	 * descriptor.
	 */
	 
	FILE *fd = NULL;
	fd = fopen(strcat(path, "/logfile.log"), "w");
	
	// Printing current time in the log file.
	time_t cur_time;
    char* time_str;

    cur_time = time(NULL);
    time_str = ctime(&cur_time);
    fprintf(fd, "Logfile creation time: %s", time_str);

	return fd;
}

char* get_string_from_file(char* path) {
	/*
	 * Opens a file, reads all the text in that file,
	 * arranges the text into a single string, and returns
	 * that string.
	 * If the file doesn't exist, then returns NULL.
	 */

	char *ans = NULL, *temp = NULL, *test = NULL;
	
	// Slightly arbitrary numbers to read line from file
	int init_temp = 255, space_left = 1024,
			init_ans = space_left;

	// Allocate memory
	ans = (char*)allocate(init_ans);
	temp = (char*)allocate(init_temp);

	// Open file
	FILE *fd = fopen(path, "r");

	if(fd == NULL)
		return ans;

	// Read each line
	while(fgets(temp, init_temp, fd) != NULL) {
		
		// Removing the \n at the end and replacing it
		// with a space, since we need the whole text in one
		// string.
		temp[strlen(temp)] = ' ';
		temp[strlen(temp) + 1] = '\0';

		// Add to the single string
		strcat(ans, (const char *)temp);

		// Keep track of space left in ans and adjust
		// accordingly. ans does NOT shrink automatically.
		space_left -= strlen(temp);
		if(space_left <= init_temp) {
			ans = resize(ans, init_ans, 2 * init_ans);
			init_ans *= 2;
			space_left = init_ans - strlen(ans);
		}
		
		// Reset temp.
		memset(temp, 0, init_temp * sizeof(char));
	}

	// Take care of stray spaces.
	if((test = strrchr(ans, ' ')) != NULL) {
		*test = '\0';
	}
	// printf("Finally, ans: %d\n", init_ans);
	// printf("returning string: %s\n", ans);

	if(strlen(ans) == 0) {
		deallocate(ans);
		ans = NULL;
	}

	deallocate(temp);
	fclose(fd);
	return ans;
}
