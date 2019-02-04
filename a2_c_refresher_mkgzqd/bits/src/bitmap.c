#include "../include/bitmap.h"

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits)
{
	if(n_bits==0) //error check for valid number of bits
		return NULL;
	struct bitmap *newBitmap=malloc(sizeof(struct bitmap)); //malloc a new bitmap

	newBitmap->bit_count = n_bits; //assign the bit count
	if(n_bits%8==0) 
		newBitmap->byte_count=n_bits/8; //assign the byte count if there is a divisible number by 8
	else
		newBitmap->byte_count=(n_bits/8)+1; //if # bits not divisible by 8, add another byte to ensure there's enough bytes for # of bits

	newBitmap->data=calloc(newBitmap->byte_count, sizeof(uint8_t)); //alloc space for the data array and calloc so initialized to 0
	return newBitmap;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap==NULL) //error check for null pointer
		return false;
	if(bit > bitmap->bit_count) //error check that there aren't more bits sent than in bitmap
		return false;
	bitmap->data[bit/8] |= 1 << (bit%8); // Set the bit at the k-th position in data[bit/8]
	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap==NULL) //error check for null pointer
		return false;
	if(bit>bitmap->bit_count) //error check that there aren't more bits sent than in bitmap
		return false;
	bitmap->data[bit/8] &= ~(1 << (bit%8)); //<< shift the flag, flip bits in flag, and clear at [bit/8] position
	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap==NULL) //error check for null pointer
		return false;
	if(bit > bitmap->bit_count) // check there aren't more bits sent than in bitmap
		return false;
	if ( (bitmap->data[bit/8] & (1 << (bit%8) )) != 0 ) //shift flag (bit%8) positions, test bit at bit/8 position
		return true; //kth bit is 1
	else
		return false; //kth bit is 0
}

size_t bitmap_ffs(const bitmap_t *const bitmap)
{
	if(bitmap==NULL) //error check for null pointer
		return SIZE_MAX;
	int i;
	for(i=0; i < bitmap->bit_count; i++){ //iterate through number of bits
		if(bitmap_test(bitmap, i)==true) //send index i to bitmap_test and if it is 1, return index
			return i;
	}
	return SIZE_MAX;
}

size_t bitmap_ffz(const bitmap_t *const bitmap)
{
	if(bitmap==NULL) //error check for null pointer
		return SIZE_MAX;
	int i;
	for(i=0; i < bitmap->bit_count; i++){ //iterate through number of bits
		if(bitmap_test(bitmap, i)==false) //send index i to bitmap_test and if it is 0, return index
			return i;
	}
	return SIZE_MAX;
}

bool bitmap_destroy(bitmap_t *bitmap)
{
	if(bitmap==NULL) //error check for null pointer
		return false;
	free(bitmap->data); //free data array
	free(bitmap); //free bitmap
	return true;
}
