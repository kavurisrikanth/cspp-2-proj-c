/*
 * file_handling.h
 *
 *  Created on: Aug 30, 2017
 *      Author: msit ksr
 */

#include <stdio.h>

#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

FILE* create_log_file(char *path);
char* get_string_from_file(char* path);

#endif /* FILE_HANDLING_H_ */
