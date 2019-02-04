#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count){
	if(src==NULL || dst==NULL) //error check for null pointers
		return false;
	if(elem_size==0 || elem_count==0) //error check to ensure elements have values
		return false;
		
	memcpy(dst, src, (elem_count*elem_size)); //copy (# of elements by element size)from array src into dst
	
	return true;
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count){
	if(data_one==NULL || data_two==NULL) //error check for null pointers
		return false;
	if(elem_size==0 || elem_count==0) //error check for null pointers
		return false;
	int hold=memcmp(data_one, data_two,(elem_count*elem_size)); //compare data_one array to data_two array for size(elem_count*elem_size)
	if(hold==0) //if two arrays are equal, a 0 will be returned 
		return true;
	else
		return false;
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count){
	if(data==NULL || target==NULL) //error check for null pointers
		return -1;
	if(elem_count==0 || elem_size==0) //error check for valid # of elements and size
		return -1;
	int i;
	int hold;
	for(i=0; i<elem_count; i++){ //iterate through # of elements 
		hold=memcmp(data+(i*elem_size), target, elem_size); //increment through data array with +(i*elem_size) and compare that to target array
		if(hold==0) //when the values ar eequal, hold is 0 and the array has been located
			return i;
	}
	return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count){
	if(src_data==NULL || dst_file==NULL) //error check for null pointers
		return false;
	if(elem_size==0 || elem_count==0) //error check to ensure elements
		return false;

	if(*dst_file=='\n') //error check to ensure a valid destination file
		return false;
	
	FILE* filePointer=NULL; //initialize file pointer
	if((filePointer=fopen(dst_file, "w"))==NULL) //open file to write
		return false;

	int hold=fwrite(src_data, elem_size, elem_count, filePointer); //use the filepointer to write from source data to destination file
	fclose(filePointer); //close the file pointer
	if(hold==elem_count) //ensure that all of the data is written
		return true;
	else
		return false;
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count){
	if(src_file==NULL || dst_data==NULL) //error check for null pointers
		return false;
	if(elem_size==0 || elem_count==0) //error check for valid elements
		return false;
	if(*src_file=='\n') //error check for valid source file
		return false;
	FILE* filePointer=NULL; //initialize file pointer
	if((filePointer=fopen(src_file, "r"))==NULL) //open file pointer for reading
		return false;

	int hold=fread(dst_data, elem_size, elem_count, filePointer); //use the filepointer to read from source file to destination data
	fclose(filePointer); //close file pointer
	if(hold==elem_count) //ensure that all data is read
		return true;
	else
		return false;
}

