/*
 * memory.c
 *
 * Handles all of the memory operations for the project.
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include "memory.h"

void* allocate(size_t size) {
	/*
	Wrapper function for memory allocation.
	*/
	
	void* ptr = NULL;
//	printf("size: %d\n", sizeof(ptr));
	ptr = calloc(1, size * sizeof(ptr));
	return ptr;
}

void* resize(void* ptr, size_t old_size, size_t new_size) {
	/*
	Wrapper function for memory reallocation.
	Rather than use realloc, which leaves newly allocated memory
	as is, this function uses calloc and memcpy.
	*/
	
	void *new_ptr = calloc(1, new_size * sizeof(ptr));
	memcpy(new_ptr, ptr, old_size * sizeof(ptr));
	free(ptr);
	return new_ptr;
}

void deallocate(void *ptr) {
	/*
	Wrapper function to free memory.
	*/
	
	if(ptr != NULL) {
		free(ptr);
		ptr = NULL;
	}
}
