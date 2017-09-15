/*
 * file_handling.h
 *
 *  Created on: Aug 30, 2017
 *      Author: msit ksr
 */

#include <stdio.h>
#include <time.h>
#include <dirent.h>

#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

FILE* create_log_file(char *path);
char* get_string_from_file(char* path);
char** get_all_files_in_dir(char *path, int *files_count);

#endif /* FILE_HANDLING_H_ */
