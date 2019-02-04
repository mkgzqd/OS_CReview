#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size)
{
	int fileDescriptor = open(input_filename, O_RDONLY); //open file for read only
	if(fileDescriptor == -1){ //-1 is returned from open if error
		close(fileDescriptor);
		return false;
	}

	lseek(fileDescriptor, offset, SEEK_SET); //use lseek to offset the file descriptor

	int readLength=read(fileDescriptor, dst, dst_size); //read from file descriptor
	int closeFile = close(fileDescriptor); //close file
	if(readLength == -1) //error checkthe read
		return false;
	if(closeFile== 0){
		return true;
	}
	else{
		return false;
	}
}
 
bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size)
{
	int fileDescriptor = open(output_filename, O_WRONLY); //open file for write only
	if(fileDescriptor == -1){ //-1 is returned from open if error
		close(fileDescriptor);
		return false;
	}

	lseek(fileDescriptor, offset, SEEK_SET); //use lseek to offset the file descriptor

	int writeLength=write(fileDescriptor, src, src_size); //write to file descriptor from source
	int closeFile = close(fileDescriptor); //close file
	if(writeLength == -1) //error check the write
		return false;
	if(closeFile== 0){
		return true;
	}
	else{
		return false;
	}
}


bool file_stat(const char *query_filename, struct stat *metadata)
{
	int fileDescriptor = open(query_filename, O_RDONLY); //open file
	int statCheck=fstat(fileDescriptor, metadata); //receive meta data from file
	int closeFile = close(fileDescriptor); //close file
	if(statCheck == -1) 
		return false;
	if(closeFile== 0){
		return true;
	}
	else{
		return false;
	}
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count)
{
	int i;
	uint32_t b0, b1, b2, b3; //bits 0,1,2,3
	if(src_count == 0) //error check # from source
		return false;
	if(src_data==NULL) //error check for null pointer
		return false;
	if (dst_data==NULL) //error check for null pointer
		return false;

	for(i=0; i<src_count; i++){
		b0 = (*(src_data+i) & 0x000000ff) << 24u; //bit shift
		b1 = (*(src_data+i) & 0x0000ff00) << 8u;
		b2 = (*(src_data+i) & 0x00ff0000) >> 8u;
		b3 = (*(src_data+i) & 0xff000000) >> 24u;
		*(dst_data+i)=b0 | b1 | b2 | b3;
	}

	return true;
}

