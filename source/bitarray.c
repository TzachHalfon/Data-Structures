/*============================LIBRARYS && MACROS =============================*/
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include "../include/bitarray.h"

#define ARR_SIZE 64

/*========================== FUNCTION DECLARATION ============================*/
bitarray_t BitArraySetAll(bitarray_t arr);
bitarray_t BitArraySetOn(bitarray_t arr, size_t index);
int BitArrayGetVal(bitarray_t arr, size_t index);
bitarray_t BitArrayRotR(bitarray_t arr, size_t num_of_rotations);
size_t BitArrayCountOn(bitarray_t arr);
bitarray_t BitArrayResetAll(bitarray_t arr);
bitarray_t BitArraySetOff(bitarray_t arr, size_t index);
bitarray_t BitArrayFlip(bitarray_t arr, size_t index);
bitarray_t BitArrayRotL(bitarray_t arr, size_t num_of_rotations);
size_t BitArrayCountOff(bitarray_t arr);
char *BitArrayToString(bitarray_t arr, char *to_write_into);
bitarray_t BitArraySetBit(bitarray_t arr, size_t index, int value);
bitarray_t BitArrayMirror(bitarray_t arr);

/*========================== LUT-FUNCTION DEFINITION =========================*/
bitarray_t BitArrayMirrorLUT(bitarray_t arr);
size_t BitArrayCountOnLUT(bitarray_t arr);
void InitCountLUT();
void InitMirrorLUT();
bitarray_t CharMirror(unsigned char ch);

/*approved by viki*/
/*=========================== FUNCTION DECLARATIONS ==========================*/

bitarray_t BitArraySetAll(bitarray_t arr)
{
	(void)arr;
	return (bitarray_t)ULONG_MAX;
}

bitarray_t BitArrayResetAll(bitarray_t arr)
{
	(void)arr;
	return (bitarray_t)(0);
}

bitarray_t BitArraySetOff(bitarray_t arr, size_t index)
{
	return BitArraySetBit(arr, index, 0);
}

bitarray_t BitArraySetOn(bitarray_t arr, size_t index)
{
	return BitArraySetBit(arr, index, 1);
}

bitarray_t BitArraySetBit(bitarray_t arr, size_t index, int value)
{
	bitarray_t tmp = 1;
	tmp <<= (index);
	value %= 2;
	if (0 == value)
	{
		return (arr & ~tmp);
	}

	return (arr | tmp);
}

bitarray_t BitArrayFlip(bitarray_t arr, size_t index)
{
	int value_in_index = BitArrayGetVal(arr, index);
	return BitArraySetBit(arr, index, !value_in_index);
}

int BitArrayGetVal(bitarray_t arr, size_t index)
{
	(void)arr;
	return ((arr >> (index)) & 1);
}

size_t BitArrayCountOn(bitarray_t arr)
{
	int check_bit = 1;
	int count = 0;
	while (check_bit != 0)
	{
		if (arr & check_bit)
		{
			count++;
		}

		check_bit <<= 1;
	}
	return count;
}

size_t BitArrayCountOff(bitarray_t arr)
{
	return ARR_SIZE - BitArrayCountOn(arr);
}

char *BitArrayToString(bitarray_t arr, char *to_write_into)
{
	char *start = to_write_into;
	int i = 0;

	for (i = ARR_SIZE - 1; i >= 0; --i)
	{
		*to_write_into = '0' + BitArrayGetVal(arr, i + 1);
		++to_write_into;
	}
	*to_write_into = '\0';

	return start;
}

bitarray_t BitArrayMirror(bitarray_t arr)
{
	bitarray_t mirror = 0;
	bitarray_t i = 0;

	for (i = 0; i < ARR_SIZE; i++)
	{
		mirror <<= 1;
		mirror = mirror | (arr & 1);
		arr >>= 1;
	}

	return mirror;
}

bitarray_t BitArrayRotR(bitarray_t arr, size_t num_of_rotations)
{
	size_t i = 0;
	int value = 0;
	num_of_rotations %= ARR_SIZE;

	for (i = 0; i < num_of_rotations; ++i)
	{
		value = BitArrayGetVal(arr, 1);
		arr >>= 1;
		arr = BitArraySetBit(arr, ARR_SIZE, value);
	}
	return arr;
}

bitarray_t BitArrayRotL(bitarray_t arr, size_t num_of_rotations)
{
	size_t real_num_of_rotations = num_of_rotations % ARR_SIZE;
	return BitArrayRotR(arr, ARR_SIZE - real_num_of_rotations);
}

/******************************************************************************/
static size_t count_LUT[256] = {0};
static size_t mirror_LUT[256] = {0};

void InitCountLUT()
{
	int i = 0;
	if (count_LUT[1] == 1)
	{
		return;
	}

	for (i = 0; i < 256; ++i)
	{
		count_LUT[i] = BitArrayCountOn((bitarray_t)i);
	}
}
size_t BitArrayCountOnLUT(bitarray_t arr)
{
	int i = 0;
	size_t count = 0;

	InitCountLUT();

	for (i = 0; i < 8; ++i)
	{
		count += count_LUT[((arr >> (i * 8)) & 0xff)];
	}
	return count;
}

void InitMirrorLUT()
{
	int i = 0;

	if (mirror_LUT[1] != 0)
	{
		return;
	}

	for (i = 0; i < 256; ++i)
	{
		mirror_LUT[i] = CharMirror((unsigned char)i);
	}
}

bitarray_t CharMirror(unsigned char ch)
{
	int i = 0;
	unsigned char mirror = 0;

	for (i = 0; i < 8; i++)
	{
		mirror <<= 1;
		mirror = mirror | (ch & 1);
		ch >>= 1;
	}
	return mirror;
}

bitarray_t BitArrayMirrorLUT(bitarray_t arr)
{
	bitarray_t mirror = 0;
	int i = 0;
	unsigned char *ptr = (unsigned char *)&arr;

	InitMirrorLUT();

	for (i = 0; i < 8; ++i)
	{
		mirror += CharMirror(*ptr) << (56 - (i * 8));
		++ptr;
	}

	return mirror;
}

size_t BitArrayCountOnNoLoop(bitarray_t arr)
{
    bitarray_t left_temp = 0;
    bitarray_t right_temp = 0;
    bitarray_t combined = 0;

    left_temp = arr & 0x5555555555555555;
    right_temp = (arr >> 1) & 0x5555555555555555;
    combined = left_temp + right_temp;
    left_temp = combined & 0x3333333333333333;
    right_temp = (combined >> 2) & 0x3333333333333333;
    combined = left_temp + right_temp;
    left_temp = combined & 0x0F0F0F0F0F0F0F0F;
    right_temp = (combined >> 4) & 0x0F0F0F0F0F0F0F0F;
    combined = left_temp + right_temp;
    left_temp = combined & 0x00FF00FF00FF00FF;
    right_temp = (combined >> 8) & 0x00FF00FF00FF00FF;
    combined = left_temp + right_temp;
    left_temp = combined & 0x0000FFFF0000FFFF;
    right_temp = (combined >> 16) & 0x0000FFFF0000FFFF;
    combined = left_temp + right_temp;
    left_temp = combined & 0x00000000FFFFFFFF;
    right_temp = (combined >> 32) & 0x00000000FFFFFFFF;
    combined = left_temp + right_temp;

    return ((size_t)combined);
}