/*
 * file_handling.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include <stdio.h>
// #include <conio.h>
// #include <types.h>
#include <dirent.h>
#include "memory.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

char** get_all_files_in_dir(char *path, int *files_count) {
	/*
		For now, prints all the files in a given directory.
	*/

	DIR *dir;
	struct dirent *d;
	char *extn, **files = NULL;
	int i = 0;

	// To keep track of the number, since we're returning an array.
	*files_count = 0;

	dir = opendir(path);
	if(dir) {
		files = (char**)allocate(10 * sizeof(char*));
		while((d = readdir(dir)) != NULL) {
			// printf("%s\n", d->d_name);
			extn = strchr(d->d_name, '.');
			if(extn) {
				// printf("extn: %s\n", extn);
				if(strcmp(extn, ".txt") == 0) {
					// printf("%s is a text file!\n", d->d_name);
					// *(files + i) = (char*)allocate((1 + d->d_name) * sizeof(char));
					*(files + i) = strdup(d->d_name);
					i++;
					(*files_count)++;
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
	fd = fopen(path, "w");

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
	int init_temp = 255, space_left = 1024,
			init_ans = space_left;

	ans = (char*)allocate(init_ans);
	temp = (char*)allocate(init_temp);

	// printf("Opening file %s...\n", path);
	FILE *fd = fopen(path, "r");

	if(fd == NULL)
		return ans;

	// printf("File opened!\n");
	// fscanf(fd, "%s", ans);
	while(fgets(temp, init_temp, fd) != NULL) {
		// printf("temp: %s\n", temp);

		temp[strlen(temp)] = ' ';
		temp[strlen(temp) + 1] = '\0';
		// printf("adding \"%s\" to \"%s\"\n", temp, ans);
		strcat(ans, (const char *)temp);
		// printf("result is \"%s\"\n", ans);
		space_left -= strlen(temp);
		// printf("space left: %d\n", space_left);
		if(space_left <= init_temp) {
			ans = resize(ans, init_ans, 2 * init_ans);
			init_ans *= 2;
			space_left = init_ans - strlen(ans);
		}

	}

	// printf("returning string before fuckery: %s\n", ans);
	if((test = strrchr(ans, ' ')) != NULL) {
		*test = '\0';
		// printf("%li\n", test - ans);
	}
	// printf("Finally, ans: %d\n", init_ans);
	// printf("returning string: %sbla\n", ans);

	if(strlen(ans) == 0) {
		deallocate(ans);
		ans = NULL;
	}

	deallocate(temp);
	fclose(fd);
	return ans;
}
