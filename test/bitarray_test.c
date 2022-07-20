#include "../include/bitarray.h"
#include <stdio.h>

int main()
{
	bitarray_t bitarray = 7;
	char str[65];
	/*
	bitarray = BitArraySetAll(bitarray);
	bitarray_t bitarray2 = 0;
	bitarray = BitArrayResetAll(bitarray);
	BitArrayToString(bitarray, str);
	printf("%s\n",str);
	*/
	/*
	bitarray2 = BitArraySetOn(bitarray2,6);
	bitarray2 = BitArraySetOff(bitarray2,6);
	bitarray2 = BitArrayFlip(bitarray2,6);
	printf("%ld\n",bitarray2);
	printf("%d\n",BitArrayGetVal(bitarray2,5));
	printf("%ld\n",BitArrayCountOff(bitarray2));
	BitArrayToString(bitarray2, str);
	BitArrayToString(bitarray, str);
	printf("%s\n",str);
	bitarray = BitArrayMirror(bitarray);
	BitArrayToString(bitarray, str);
	printf("%s\n",str);
	*/

	printf("%ld\n",BitArrayCountOnLUT(bitarray));
	
	BitArrayToString(bitarray, str);
	printf("%s\n",str);
	bitarray = BitArrayMirrorLUT(bitarray);
	BitArrayToString(bitarray, str);
	printf("%s\n",str);


	return 0;
}

