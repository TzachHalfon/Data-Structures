#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char push_test = 'z';
	stack_ptr_t stack = StackCreate(5,1);
	printf("%d\n",StackIsEmpty(stack));
	StackPush(stack,&push_test);
	StackPush(stack,&push_test);
	printf("%d\n",StackIsEmpty(stack));
	printf("%ld\n",StackGetSize(stack));
	printf("%c\n",*(char*)StackPeek(stack));
	StackPop(stack);
	StackPop(stack);
	printf("%ld\n",StackGetCapacity(stack));
	StackDestroy(stack);
	
	return 0;
}