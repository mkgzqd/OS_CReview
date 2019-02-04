#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length){
	if(length==0) //check to make sure there is a valid length
		return false;
	if(str==NULL) //check for null string
		return false;
	int i;
	for(i=0; i<=length; i++){ //iterate through string until null terminator to test valid string
		if(str[i] == '\0')
			return true;
	}

	return false;
}

char *string_duplicate(const char *str, const size_t length){
	if(str==NULL) //check for no null string
		return false;
	if(length==0) //check for a valid length
		return false;
	char* hold=malloc(sizeof(char)*length); //alloc string to be duplicated into
	int i;
	for(i=0; i<length; i++){ //iterate through length of string
		hold[i]=str[i]; //assign str index to hold
	}

	return hold;
}

bool string_equal(const char *str_a, const char *str_b, const size_t length){
	if(str_a ==NULL || str_b==NULL) //error check for null strings
		return false;
	if(length==0) //ensure a valid length
		return false;
	int i;
	for(i=0; i<length; i++){ //iterate through length of strings
		if(str_a[i]!=str_b[i]) //compare values of string indices to check for valid
			return false;
	}
	return true;
}

int string_length(const char *str, const size_t length){
	if(length==0) //error check for valid length
		return -1;
	if(str==NULL) //error check string to ensure it's not null
		return -1;
	int count=strlen(str);
	return count;
}

int string_tokenize(const char *str, const char *delims, const size_t str_length, char **tokens, const size_t max_token_length, const size_t requested_tokens){
	if(str==NULL || delims==NULL || tokens==NULL) //error check that pointers aren't null
		return 0;
	if(str_length==0 || max_token_length==0 || requested_tokens==0) //error check to ensure valid lengths and tokens requested
		return 0;
	int i, count=0;
	for(i=0; i<requested_tokens; i++){ //loop through the number of requested tokens
		if(tokens[i]==NULL) //error check for pointer at tokens[i] to not be null
			return -1;
	}
	i=0;
	char* hold=string_duplicate(str, str_length); //duplicate str into char* hold because strtok doesn't take const
	tokens[i]=strtok(hold, delims); //tokenize the first token
	//i++;
	//count++;
	while(tokens[i]!=NULL){ //iterate until null pointer at tokens[i]
		tokens[i]=strtok(NULL, delims); //tokenize the next token from null pointer
		i++; //iterate i
		count++; //iterate count
	}
	return count; //return number of tokens
}

bool string_to_int(const char *str, int *converted_value){
	if(str==NULL || converted_value==NULL) //error check for null pointers
		return false;
	int i;
	for(i=0; i<strlen(str); i++){ //iterate until end of string
		if(str[i]-'0'<0 || str[i]-'0' >9) //error check to make sure that str[i] is actually an integer
			break;
		if(*converted_value > 32767 || *converted_value < -32767){ //ensure that the converted value does not exceed the int range
			*converted_value=0;
			return false;
		}
		*converted_value *=10; //multiple the converted value by 10 for number of place values
		*converted_value+=( str[i] -'0'); //add the newly read integer from str[i] to the other numbers
	}
	//converted_value[i]=hold;

	return true;
}
