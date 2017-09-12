/*
 * file_handling.c
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include <stdio.h>
// #include <conio.h>
#include "memory.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

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

	char *ans = NULL, *temp = NULL;
	int init_temp = 129, space_left = 1024,
		init_ans = space_left;

	ans = (char*)allocate(init_ans);
	temp = (char*)allocate(init_temp);

	printf("Opening file...\n");
	FILE *fd = fopen(path, "r");

	if(fd == NULL)
		return ans;

	// printf("File opened!\n");
	// fscanf(fd, "%s", ans);
	while(fgets(temp, init_temp, fd) != NULL) {
		// printf("temp: %s\n", temp);

		temp[strlen(temp) - 1] = ' ';
		strcat(ans, (const char *)temp);
		space_left -= strlen(temp);
		// printf("space left: %d\n", space_left);
		if(space_left <= init_temp) {
			ans = resize(ans, init_ans, 2 * init_ans);
			init_ans *= 2;
			space_left = init_ans - strlen(ans);
		}

	}

	printf("Finally, ans: %d\n", init_ans);
	deallocate(temp);
	fclose(fd);
	return ans;
}
